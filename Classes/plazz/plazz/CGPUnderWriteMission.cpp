#include "CGPUnderWriteMission.h"

CGPUnderWriteMission::CGPUnderWriteMission(const std::string& url, int port)
: CSocketMission(url, port)
{
	mIGPUnderWriteMissionSink = 0;
}

// 设置回调接口
void CGPUnderWriteMission::setMissionSink(IGPUnderWriteMissionSink* pIGPUnderWriteMissionSink)
{
	mIGPUnderWriteMissionSink = pIGPUnderWriteMissionSink;
}

// 个性签名
void CGPUnderWriteMission::modifyUnderWrite(char szUnderWrite[LEN_UNDER_WRITE])
{
	memcpy(mUnderWrite, szUnderWrite, sizeof(mUnderWrite));
	start();
}

void CGPUnderWriteMission::onEventTCPSocketLink()
{
	PLAZZ_PRINTF("CGPUnderWriteMission::onEventTCPSocketLink\n");

	//用户信息
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//变量定义
	PACKET_AIDE_SIZE(512);
	packet.write4Byte(pGlobalUserData->dwUserID);
	packet.writeString(pGlobalUserData->szPassword, LEN_PASSWORD);
	packet.writeString(mUnderWrite, LEN_UNDER_WRITE);
	
	//发送数据
	send(MDM_GP_USER_SERVICE,SUB_GP_MODIFY_UNDER_WRITE, packet.getBuffer(),packet.getPosition());
}

void CGPUnderWriteMission::onEventTCPSocketShut()
{
	PLAZZ_PRINTF("CGPUnderWriteMission::onEventTCPSocketShut\n");
}

void CGPUnderWriteMission::onEventTCPSocketError(int errorCode)
{
	PLAZZ_PRINTF("CGPUnderWriteMission::onEventTCPSocketError code[%d]\n", errorCode);
}

bool CGPUnderWriteMission::onEventTCPSocketRead(int main, int sub, void* data, int size) 
{
	PLAZZ_PRINTF("CGPUnderWriteMission::onEventTCPSocketRead main:%d sub:%d size:%d\n", main, sub, size);
	if (main != MDM_GP_USER_SERVICE)
	{
		return false;
	}

	switch (sub)
	{
		//操作成功
	case SUB_GP_OPERATE_SUCCESS:	return onSubOperateSuccess(data, size);
		//操作失败
	case SUB_GP_OPERATE_FAILURE:	return onSubOperateFailure(data, size);
	}

	return false;
}

// 操作成功
bool CGPUnderWriteMission::onSubOperateSuccess(void* data, int size)
{
	int baseSize = 4;
	//效验参数
	ASSERT(size>=baseSize);
	if (size<baseSize) return false;

	PACKET_AIDE_DATA(data);
	int lResultCode	= packet.read4Byte();
	std::string str	= packet.readString((size-baseSize)/2);

	//关闭连接
	stop();

	//变量定义
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//设置信息
	strncpy(pGlobalUserData->szUnderWrite,mUnderWrite,countarray(pGlobalUserData->szUnderWrite));

	//通知
	if (mIGPUnderWriteMissionSink)
		mIGPUnderWriteMissionSink->onGPUnderWriteSuccess(str.c_str());
	return true;
}

// 操作失败
bool CGPUnderWriteMission::onSubOperateFailure(void* data, int size)
{
	int baseSize = 4;
	//效验参数
	ASSERT(size>=baseSize);
	if (size<baseSize) return false;

	PACKET_AIDE_DATA(data);
	int lResultCode	= packet.read4Byte();
	std::string str	= packet.readString((size-baseSize)/2);

	//关闭连接
	stop();

	//通知
	if (mIGPUnderWriteMissionSink)
		mIGPUnderWriteMissionSink->onGPUnderWriteFailure(str.c_str());
	return true;
}