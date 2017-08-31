#include "CGPMessageMission.h"

#define MISSION_MESSAGE_NULL		0
#define MISSION_MESSAGE_LIST		1
#define MISSION_MESSAGE_AWARD		2

CGPMessageMission::CGPMessageMission(const std::string& url, int port)
: CSocketMission(url, port)
{
	mIGPMessageMissionSink = 0;
	mMissionType = MISSION_MESSAGE_NULL;
}

// 设置回调接口
void CGPMessageMission::setMissionSink(IGPMessageMissionSink* pIGPMessageMissionSink)
{
	mIGPMessageMissionSink = pIGPMessageMissionSink;
}

void CGPMessageMission::getMessageList()
{
	mMissionType = MISSION_MESSAGE_LIST;
	start();
}

// 领取排行榜奖励
void CGPMessageMission::getRankAward(int iRankNumber)
{
	mRankNumber = iRankNumber;
	mMissionType = MISSION_MESSAGE_AWARD;
	start();
}

void CGPMessageMission::onEventTCPSocketLink()
{
	PLAZZ_PRINTF("CGPMessageMission::onEventTCPSocketLink\n");

	//变量定义
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	switch (mMissionType)
	{
	case MISSION_MESSAGE_LIST:
		{
			//变量定义
			PACKET_AIDE_SIZE(64);
			packet.write4Byte(pGlobalUserData->dwUserID);

			//发送数据
			send(MDM_GP_USER_SERVICE,SUB_GP_MESSAGE_LIST, packet.getBuffer(), packet.getPosition());
		}
		break;
	case MISSION_MESSAGE_AWARD:
		{
			//变量定义
			PACKET_AIDE_SIZE(64);
			packet.write4Byte(pGlobalUserData->dwUserID);
			packet.write4Byte(mRankNumber);
			//发送数据
			send(MDM_GP_USER_SERVICE,SUB_GP_MESSAGE_AWARD, packet.getBuffer(), packet.getPosition());
		}
		break;
	default:
		stop();
		break;
	}
	
}

void CGPMessageMission::onEventTCPSocketShut()
{
	PLAZZ_PRINTF("CGPMessageMission::onEventTCPSocketShut\n");
}

void CGPMessageMission::onEventTCPSocketError(int errorCode)
{
	PLAZZ_PRINTF("CGPMessageMission::onEventTCPSocketError code[%d]\n", errorCode);
}

bool CGPMessageMission::onEventTCPSocketRead(int main, int sub, void* data, int size) 
{
	PLAZZ_PRINTF("CGPMessageMission::onEventTCPSocketRead main:%d sub:%d size:%d\n", main, sub, size);
	if (main != MDM_GP_USER_SERVICE)
	{
		return false;
	}

	switch (sub)
	{
		//邮件列表
	case SUB_GP_MESSAGE_LIST_RESULT:	return onSubMessageList(data, size);
		//获取邮件奖励结果
	case SUB_GP_MESSAGE_AWARD_RESULT:	return onSubMessageAwardResult(data, size);
	}

	return false;
}

// 兑换结果
bool CGPMessageMission::onSubMessageList(void* data, int size)
{
	if (data == 0 || size == 0)
	{
		stop();
		if (mIGPMessageMissionSink)
		{
			systemtime datetime;
			mIGPMessageMissionSink->onGPMessageListItem(-1, 0, 0, 0, datetime);
		}
		return true;
	}

	if (mIGPMessageMissionSink == 0)
		return true;

	PACKET_AIDE_DATA(data);
	int itemSize = 4+4+4+4+16;
	int count = size / itemSize;

	for (int i = 0; i < count; ++i)
	{
		uint32 index = packet.read4Byte();
		uint32 top   = packet.read4Byte();
		uint32 rank  = packet.read4Byte();
		uint32 score = packet.read4Byte();
		systemtime datetime;
		datetime.wYear			= packet.read2Byte();
		datetime.wMonth			= packet.read2Byte();
		datetime.wDayOfWeek		= packet.read2Byte();
		datetime.wDay			= packet.read2Byte();
		datetime.wHour			= packet.read2Byte();
		datetime.wMinute		= packet.read2Byte();
		datetime.wSecond		= packet.read2Byte();
		datetime.wMilliseconds	= packet.read2Byte();
	
		mIGPMessageMissionSink->onGPMessageListItem(index, top, rank, score, datetime);
	}

	return true;
}


//获取邮件排行榜奖励结果
bool CGPMessageMission::onSubMessageAwardResult(void* data, int size)
{
	if (size < 4)
		return true;

	PACKET_AIDE_DATA(data);

	uint32 lResultCode		= packet.read4Byte();
	std::string sDescripe	= packet.readString((size-4)/2);
	mIGPMessageMissionSink->onGPMessageAwardResult(sDescripe.c_str());
	return true;
}