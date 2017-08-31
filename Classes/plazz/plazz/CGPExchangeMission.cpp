#include "CGPExchangeMission.h"

#define MISSION_EXCHANGE_ITEM		1
#define MISSION_EXCHANGE_PAY		2
#define MISSION_EXCHANGE_SHARE		3
#define MISSION_EXCHANGE_PAYCARD	4

CGPExchangeMission::CGPExchangeMission(const std::string& url, int port)
: CSocketMission(url, port)
{
	mMissionType = 0;
	mIGPExchangeMissionSink = 0;
}

// 设置回调接口
void CGPExchangeMission::setMissionSink(IGPExchangeMissionSink* pIGPExchangeMissionSink)
{
	mIGPExchangeMissionSink = pIGPExchangeMissionSink;
}

void CGPExchangeMission::exchange(uint16 item)
{
	mItem = item;
	mMissionType = MISSION_EXCHANGE_ITEM;
	start();
}

void CGPExchangeMission::pay(const tagPay& Pay)
{
	memcpy(&mPay, &Pay, sizeof(mPay));
	mMissionType = MISSION_EXCHANGE_PAY;
	start();
}

// 
void CGPExchangeMission::share()
{
	mMissionType = MISSION_EXCHANGE_SHARE;
	start();
}

void CGPExchangeMission::payCard(const char* card, const char* pwd)
{
	mMissionType = MISSION_EXCHANGE_PAYCARD;
	mStrMBCard = card;
	mStrMBPassword = pwd;
	start();
}

bool CGPExchangeMission::sendExchangeItem()
{
	//变量定义
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();

	//变量定义
	PACKET_AIDE_SIZE(512);
	packet.write4Byte(pGlobalUserData->dwUserID);
	packet.write2Byte(mItem);
	packet.writeString(pGlobalUserData->szNickName, LEN_NICKNAME);

	//发送数据
	send(MDM_GP_USER_SERVICE, SUB_GP_EXCHANGE, packet.getBuffer(), packet.getPosition());
	return true;
}

bool CGPExchangeMission::sendPay(const tagPay& Pay)
{
	//变量定义
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();

	//变量定义
	PACKET_AIDE_SIZE(512);
	packet.write4Byte(pGlobalUserData->dwUserID);
	packet.writeByte(Pay.mBuyType);
	packet.write8Byte(Pay.mBuyCount);
	packet.write8Byte(Pay.mPayRMB);
	packet.writeByte(Pay.mPayType);

	//发送数据
	send(MDM_GP_USER_SERVICE, SUB_MB_PAY_INFO, packet.getBuffer(), packet.getPosition());
	return true;
}

bool CGPExchangeMission::sendPayCard(const char* card, const char* pwd)
{
	//变量定义
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();

	//变量定义
	PACKET_AIDE_SIZE(512);
	packet.write4Byte(pGlobalUserData->dwUserID);
	packet.writeString(card, 16);
	packet.writeString(DF::MD5Encrypt(pwd), 33);

	//发送数据
	send(MDM_GP_USER_SERVICE, SUB_MB_PAY_CARD, packet.getBuffer(), packet.getPosition());
	return true;
}

bool CGPExchangeMission::sendShare()
{
	//变量定义
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();

	//变量定义
	PACKET_AIDE_SIZE(512);
	packet.write4Byte(pGlobalUserData->dwUserID);

	//发送数据
	send(MDM_GP_USER_SERVICE, SUB_MB_SHARE_INFO, packet.getBuffer(), packet.getPosition());
	return true;
}

void CGPExchangeMission::onEventTCPSocketLink()
{
	PLAZZ_PRINTF("CGPExchangeMission::onEventTCPSocketLink\n");

	switch (mMissionType)
	{
	case MISSION_EXCHANGE_ITEM:
		sendExchangeItem();
		break;
	case MISSION_EXCHANGE_PAY:
		sendPay(mPay);
		break;
	case MISSION_EXCHANGE_SHARE:
		sendShare();
		break;
	case MISSION_EXCHANGE_PAYCARD:
		sendPayCard(mStrMBCard.c_str(), mStrMBPassword.c_str() );
		break;
	}
}

void CGPExchangeMission::onEventTCPSocketShut()
{
	PLAZZ_PRINTF("CGPExchangeMission::onEventTCPSocketShut\n");
}

void CGPExchangeMission::onEventTCPSocketError(int errorCode)
{
	PLAZZ_PRINTF("CGPExchangeMission::onEventTCPSocketError code[%d]\n", errorCode);
}

bool CGPExchangeMission::onEventTCPSocketRead(int main, int sub, void* data, int size) 
{
	PLAZZ_PRINTF("CGPExchangeMission::onEventTCPSocketRead main:%d sub:%d size:%d\n", main, sub, size);
	if (main != MDM_GP_USER_SERVICE)
	{
		return false;
	}

	switch (sub)
	{
		case SUB_GP_EXCHANGE_RESULT: return onSubExchangeSuccess(data, size);
		case SUB_MB_PAY_RESULT:	return onSubPayResult(data, size);
		case SUB_MB_SHARE_RESULT: return onSubShareResult(data, size);
		case SUB_MB_PAY_CARD_RESULT: return onSubPayCardResult(data, size);
	}

	return false;
}

// 兑换结果
bool CGPExchangeMission::onSubExchangeSuccess(void* data, int size)
{
	//效验数据
	ASSERT(size>=10);
	if (size<10) return false;

	PACKET_AIDE_DATA(data);
	uint32 dwUserID = packet.read4Byte();
	int wItemID = packet.read2Byte();
	int lResultCode = packet.read4Byte();
	int len = (size-10)/2;
	std::string str = packet.readString(len);

	//关闭连接
	stop();

	//显示消息
	if (mIGPExchangeMissionSink)
		mIGPExchangeMissionSink->onGPExchangeResult(lResultCode, str.c_str());
	return true;
}

bool CGPExchangeMission::onSubPayResult(void* data, int size)
{
	//关闭连接
	stop();
	return true;
}

bool CGPExchangeMission::onSubShareResult(void* data, int size)
{
	//效验数据
	ASSERT(size >= 16);
	if (size<16) return false;

	PACKET_AIDE_DATA(data);
	uint32 dwUserID = packet.read4Byte();

	//变量定义
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagUserInsureInfo * pInsureInfo = pGlobalUserInfo->GetUserInsureInfo();
	pInsureInfo->lUserInsure += packet.read8Byte();

	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();
	pGlobalUserData->lRoomCard += packet.read4Byte();

	int len = (size - 16) / 2;
	std::string str = packet.readString(len);

	//显示消息
	if (mIGPExchangeMissionSink)
		mIGPExchangeMissionSink->onGPShaerResult(str.c_str());

	//关闭连接
	stop();
	return true;
}

bool CGPExchangeMission::onSubPayCardResult(void* data, int size)
{
	//效验数据
	ASSERT(size >= 12);
	if (size<12) return false;

	PACKET_AIDE_DATA(data);
	uint32 dwUserID = packet.read4Byte();

	//变量定义
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagUserInsureInfo * pInsureInfo = pGlobalUserInfo->GetUserInsureInfo();
	pInsureInfo->lUserScore += packet.read8Byte();

	int len = (size - 4) / 2;
	std::string str = packet.readString(len);

	//显示消息
	if (mIGPExchangeMissionSink)
		mIGPExchangeMissionSink->onGPPayCardResult(str.c_str());

	//关闭连接
	stop();
	return true;
}