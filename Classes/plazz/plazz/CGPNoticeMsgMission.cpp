#include "CGPNoticeMsgMission.h"
#include "cocos2d.h"
#include "MELog.h"
USING_NS_CC;

#define MISSION_LOGIN_MSG		1

CGPNoticeMsgMission::CGPNoticeMsgMission(const std::string& url, int port)
: CSocketMission(url, port)
{
	mMissionType = 0;
	mIGPMsgMissionSink = 0;
}


// 设置回调接口
void CGPNoticeMsgMission::setMissionSink(IGPMsgMissionSink* pIGPMsgMissionSink)
{
	mIGPMsgMissionSink = pIGPMsgMissionSink;
}

void CGPNoticeMsgMission::loginMsg()
{
	mMissionType = MISSION_LOGIN_MSG;
	start();
}

// 登陆
bool CGPNoticeMsgMission::sendLoginMsg()
{
	//获取对象
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();

	MELOG(MELOG_INFO, "sendLoginMsg.............................................. \n");
	//变量定义
	PACKET_AIDE_SIZE(SIZE_PACK_DATA);
	packet.write4Byte(pGlobalUserData->dwUserID);
	
	//发送数据
	send(MDM_GP_MSG_LOGON, SUB_GP_MSG_SEND_LOGON, packet.getBuffer(), packet.getPosition());
	return true;
}

void CGPNoticeMsgMission::onEventTCPSocketLink()
{
	switch (mMissionType)
	{
		// 登陆
	case MISSION_LOGIN_MSG:
		sendLoginMsg();
		break;
	}
}

void CGPNoticeMsgMission::onEventTCPSocketShut()
{
	MELOG(MELOG_INFO, "CGPNoticeMsgMission::onEventTCPSocketShut: close socket \n");
}

void CGPNoticeMsgMission::onEventTCPSocketError(int errorCode)
{
	MELOG(MELOG_INFO, "CGPNoticeMsgMission::onEventTCPSocketError: connect error code[%d] \n", errorCode);
	if (mIGPMsgMissionSink)
		mIGPMsgMissionSink->onGPMsgError(errorCode);
}

bool CGPNoticeMsgMission::onEventTCPSocketRead(int main, int sub, void* data, int size)
{
	MELOG(MELOG_INFO, "onEventTCPSocketRead main:%d sub:%d size:%d \n", main, sub, size);
	switch (main)
	{
	case MDM_GP_MSG_LOGON:	
		return onSocketMainLogon(sub, data, size);
	case MDM_GP_MSG_SYSTEM:	return onSocketMainMsg(sub, data, size);
	default:
		break;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
// 登陆信息
bool CGPNoticeMsgMission::onSocketMainLogon(int sub, void* data, int size)
{
	switch (sub)
	{
		//登录成功
	case SUB_GP_MSG_LOGON_FINISH: return onSocketSubLogonFinish(data, size);
	}
	return false;
}

//登录完成
bool CGPNoticeMsgMission::onSocketSubLogonFinish(void* data, int size)
{
	MELOG(MELOG_INFO, "CGPNoticeMsgMission::onSocketSubLogonFinish ....... \n");
	return true;
}

// 聊天信息
bool CGPNoticeMsgMission::onSocketMainMsg(int sub, void* data, int size)
{
	switch (sub)
	{
		case SUB_GP_S_BUGLE_MESSAGE: //喇叭消息
		{
			return onSocketSubBugle(data, size);
		}
		case SUB_GP_S_MESSAGE: //系统消息
		{
			return onSocketSubMessage(data, size);
		}
	}
	return true;
}

//喇叭消息
bool CGPNoticeMsgMission::onSocketSubBugle(void* data, int size)
{
	PACKET_AIDE_DATA(data);
	
	dword dwUserID = packet.read4Byte();
	byte  cbBugleType = packet.readByte();
	dword dwChatColor = packet.read4Byte();
	word  wChatLength = packet.read2Byte();
	std::string sNickname = packet.readString(LEN_NICKNAME);
	std::string sContext = packet.readString(wChatLength);

	if (mIGPMsgMissionSink)
		mIGPMsgMissionSink->onGPNotice(sContext.c_str());

	return true;
}

//系统消息
bool CGPNoticeMsgMission::onSocketSubMessage(void* data, int size)
{
	PACKET_AIDE_DATA(data);

	word  wType = packet.read2Byte();
	word  wLength = packet.read2Byte();
	std::string sContext = packet.readString(wLength);

	if (mIGPMsgMissionSink)
		mIGPMsgMissionSink->onGPNotice(sContext.c_str());

	return true;
}