#ifndef _SocketEngine_H_
#define _SocketEngine_H_

#include "ISocketEngine.h"
#include "../socket/Socket.h"

typedef unsigned char byte;


class CSocketEngine
	: public ISocketEngine
	, public ISocketSink
{
public:
	CSocketEngine();
	virtual ~CSocketEngine();

	//////////////////////////////////////////////////////////////////////////
	// 接口ISocketEngine
public:
	/** 设置Socket接收器 */
	virtual void setSocketEngineSink(ISocketEngineSink* pISocketEngineSink);
	/** 链接网络 **/
	virtual bool connect(const char* url, int port);
	/** 关闭网络 **/
	virtual bool disconnect();
	/** 发送数据 **/
	virtual bool send(int main, int sub, void* data, int dataSize);
	/** 状态判断 **/
	virtual bool isAlive();
	/** 发送校验 **/
	virtual void setTCPValidate(bool send);

	//////////////////////////////////////////////////////////////////////////
	// 接口ISocketSink
public:
	virtual void onSocketLink();
	virtual void onSocketShut();
	virtual void onSocketError(int errorCode);
	virtual void onSocketData(void* data, int dataSize);

	//////////////////////////////////////////////////////////////////////////
	// 辅助函数
private:
	void sendTCPValidate();
	const byte* pack(int main, int sub, byte* data, int size);
	bool unpack(byte* data, int start, int length);

private:
	// 接收处理模块
	ISocketEngineSink* mISocketEngineSink;
	// 连接SOCKET
	CSocket mSocket;
	// 发送校验
	bool mIsSendTCPValidate;
	
	//////////////////////////////////////////////////////////////////////////
	// 数据缓冲
private:
	// 临时缓冲
	byte mBufPack[SIZE_TCP_BUFFER];
	byte mBufUnPack[SIZE_TCP_BUFFER];
	// 接收缓冲
	byte mBufRecieve[SIZE_TCP_BUFFER];
	// 接收长度
	int mBufRevLength;
};

#endif // _SocketEngine_H_