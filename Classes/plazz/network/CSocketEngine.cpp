#include <sstream>
#include "QPCipher.h"
#include "CSocketEngine.h"

using namespace std;
//////////////////////////////////////////////////////////////////////////

ISocketEngine* ISocketEngine::create()
{
	return new CSocketEngine();
}

void ISocketEngine::destory(ISocketEngine* pISocketEngine)
{
	if (pISocketEngine)
	{
		delete pISocketEngine;
	}
}

//////////////////////////////////////////////////////////////////////////
CSocketEngine::CSocketEngine()
{
	mISocketEngineSink = 0;
	mIsSendTCPValidate = false;
	mSocket.setSocketSink(this);
}

CSocketEngine::~CSocketEngine()
{
	mISocketEngineSink=0;
	mSocket.setSocketSink(0);
	disconnect();
}

//////////////////////////////////////////////////////////////////////////
// ISocketEngine 接口实现

/** 设置Socket接收器 */
void CSocketEngine::setSocketEngineSink(ISocketEngineSink* pISocketEngineSink)
{
	mISocketEngineSink = pISocketEngineSink;
}

/** 链接网络 **/
bool CSocketEngine::connect(const char* url, int port)
{
	if (mSocket.connect(url, port) != 0)
		return false;
	// 接收长度
	mBufRevLength=0;
	sendTCPValidate();
	return isAlive();
}

/** 关闭网络 **/
bool CSocketEngine::disconnect()
{
	//// 接收长度
	//mBufRevLength=0;
	mSocket.disconnect();
	return true;
}

/** 发送数据 **/
bool CSocketEngine::send(int main, int sub, void* data, int dataSize)
{
	if (!isAlive())
		return false;
	// 打包数据
	const byte* dataSend = pack(main, sub, (byte*)data, dataSize);
	mSocket.send((const char*)dataSend, SIZE_PACK_HEAD+dataSize);
	return true;
}

/** 状态判断 **/
bool CSocketEngine::isAlive()
{
	return mSocket.isAlive();
}

/** 发送校验 **/
void CSocketEngine::setTCPValidate(bool send)
{
	mIsSendTCPValidate = send;
}

//////////////////////////////////////////////////////////////////////////
// 接口ISocketSink
void CSocketEngine::onSocketLink()
{
	//PLAZZ_PRINTF("CSocketEngine::onSocketLink\n");
	if (mISocketEngineSink != 0)
		mISocketEngineSink->onEventTCPSocketLink();
}

void CSocketEngine::onSocketShut()
{
		mISocketEngineSink->onEventTCPSocketShut();
}

void CSocketEngine::onSocketError(int errorCode)
{
	if (mISocketEngineSink != 0)
		mISocketEngineSink->onEventTCPSocketError(errorCode);

}

void CSocketEngine::onSocketData(void* data, int dataSize)
{
	memcpy(&mBufRecieve[mBufRevLength], data, dataSize);
	// 接收长度增加
	mBufRevLength += dataSize;
	
	// 尝试解包
	int iUnpackIndex = 0;
	bool isReaded = false;
	int iDstLength = SIZE_PACK_INFO;

	//PLAZZ_PRINTF("mBufRevLength:%d %d\n", mBufRevLength, dataSize);

	// 开始解密了
	
	// 接收长度 - 已经解包的数据长度 
	while ((mBufRevLength - iUnpackIndex) >= iDstLength)
	{
		if (isReaded == false)
		{
			isReaded   = true;
			iDstLength = QPCipher::getPackSize((unsigned char*)mBufRecieve, iUnpackIndex);

			//PLAZZ_PRINTF("DstLength:%d\n", iDstLength);
			if (iDstLength > /*SIZE_TCP_BUFFER - */mBufRevLength && SOCKET_CHECK)
			{
				//PLAZZ_PRINTF("onSocketData 错误数据包长度，长度:%d\n", iDstLength);
				//disconnect();
				break;
			}
		} 
		else
		{
			// 解包数据并通知调用
			if (!unpack(mBufRecieve, iUnpackIndex, iDstLength))
			{
				// 应该是等待，并显示 
				disconnect();
				return;
			}

			// 解包数据游标移动
			iUnpackIndex += iDstLength;
			// 重置接收长度为包信息头长度
			iDstLength = SIZE_PACK_INFO;
			// 重置接收为未读取包信息头状态
			isReaded = false;
		}
	}
	
	//PLAZZ_PRINTF("mBufRevLength:%d UnpackIndex:%d\n", mBufRevLength, iUnpackIndex);
	// 剩余数据长度
	mBufRevLength = mBufRevLength - iUnpackIndex;
	//PLAZZ_PRINTF("剩余数据长度:%d \n", mBufRevLength);
	// 移动剩余数据
	if (mBufRevLength > 0)
	{
		memmove(mBufRecieve, &mBufRecieve[iUnpackIndex], mBufRevLength);
	}
}

//////////////////////////////////////////////////////////////////////////
// 辅助函数

void CSocketEngine::sendTCPValidate()
{
	if (mIsSendTCPValidate == false)
		return;
	// 获取验证信息
	QPCipher::tcpValidate(&mBufPack[0], 0);

	// 发送验证
	ostringstream ss;
	ss.str("");
	for (int i = 0; i < SIZE_VALIDATE; i++)
	{
		ss << mBufPack[i] << ",";
	}
	mSocket.send(ss.str().c_str(), (int)ss.str().size());
}

const byte* CSocketEngine::pack(int main, int sub, byte* data, int size)
{
	mBufPack[0]=0;
	int packsize = SIZE_PACK_HEAD + size;
	QPCipher::setPackInfo(mBufPack, packsize, main, sub);

	// 赋值
	if (size > 0) {
		memcpy(&mBufPack[SIZE_PACK_HEAD], data, size);
	}
	// 加密数据
	QPCipher::encryptBuffer(mBufPack, packsize);
	return mBufPack;
}

bool CSocketEngine::unpack(byte* data, int start, int length)
{
	// 解密
	if ((data[start] & QPCipher::getCipherMode()) > 0)
	{
		QPCipher::decryptBuffer(data, start, length);
	}
	// 主命令码
	int main = QPCipher::getMainCommand(data, start);
	// 次命令码
	int sub = QPCipher::getSubConmmand(data, start);
	
	// 附加数据
	if (length > 8) 
	{
		memcpy(mBufUnPack, &data[start+8], length - 8);
	}
	
	length -= 8;

	//if (SOCKET_CHECK)
	//	PLAZZ_PRINTF("Main:%d Sub:%d Size:%d\n", main, sub, length);
	
	if (main == 0 && sub == 1)
	{
		//PLAZZ_PRINTF("REV-HEART\n");
	}
	else
	{
		if (mISocketEngineSink != 0)
		{
			bool bHandle = mISocketEngineSink->onEventTCPSocketRead(main, sub, mBufUnPack, length);

			/*if (!bHandle)
				PLAZZ_PRINTF("no match: main:%d sub:%d size:%d \n", main, sub, length);*/
			return bHandle;
		}
	}
	
	return true;
}