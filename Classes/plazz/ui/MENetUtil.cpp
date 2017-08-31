#include "MENetUtil.h"
#include "../Plazz.h"
#include "cocos2d.h"
#include "ClientKernelSink.h"
#include "MELog.h"

USING_NS_CC;

bool MENetUtil::init(int iKindID, int iPlayers, int iClientVersion, const char* sGameName)
{
	DF::shared()->init(iKindID, iPlayers, iClientVersion, sGameName);
	return true;
}

const char* MENetUtil::getNickName()
{
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();

	return pGlobalUserData->szNickName;
}

const char* MENetUtil::getPassword()
{
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();

	return pGlobalUserData->szPassword;
}

const char* MENetUtil::getBankPassword()
{
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();

	return pGlobalUserData->szPassword;
}

const char* MENetUtil::getEncryptPassword(const char* pwd)
{
	return DF::MD5Encrypt(pwd);
}

int MENetUtil::getSex()
{
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();

	return pGlobalUserData->cbGender;
}

int MENetUtil::getFaceID()
{
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();

	return pGlobalUserData->wFaceID;
}

int  MENetUtil::getGameID()
{
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();

	return pGlobalUserData->dwGameID;
}

int MENetUtil::getUserID()
{
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();

	return pGlobalUserData->dwUserID;
}

int MENetUtil::getUserDailiOrder()
{
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();

	return pGlobalUserData->cbDailiOrder;
}

int MENetUtil::getUserType()
{
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();

	return pGlobalUserData->cbUserType;
}

const char* MENetUtil::getUserIconUrl()
{
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();

	return pGlobalUserData->szIconUrl;
}

int MENetUtil::getUserGold()
{
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagUserInsureInfo * pUserInsureInfo = pGlobalUserInfo->GetUserInsureInfo();


	return pUserInsureInfo->lUserScore;
}

int MENetUtil::getBankGold()
{
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagUserInsureInfo * pUserInsureInfo = pGlobalUserInfo->GetUserInsureInfo();

	return pUserInsureInfo->lUserInsure;
}

int MENetUtil::getRoomGold()
{
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();
	
	return pGlobalUserData->lRoomCard;
}

int MENetUtil::setUserGoldOrRoomCard(int nType, long long nValue)
{
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();
	tagUserInsureInfo * pUserInsureInfo = pGlobalUserInfo->GetUserInsureInfo();

	if (nType == 1)
	{
		pUserInsureInfo->lUserScore = pUserInsureInfo->lUserScore + nValue;
	}
	else if (nType == 2)
	{
		pGlobalUserData->lRoomCard = pGlobalUserData->lRoomCard + nValue;
	}
	return 0;
}

int MENetUtil::getChairID()
{
	IClientKernel* lpClientKerner = IClientKernel::get();
	if (lpClientKerner != NULL)
	{
		return lpClientKerner->GetMeChairID();
	}
	else
	{
		return 0;
	}

	
}

int MENetUtil::getTableGold(int iKindID, int iServerID)
{
	CGameServerItemMap::iterator it = CServerListData::shared()->GetServerItemMapBegin();
	CGameServerItem* pGameServerItem = 0;
	while ((pGameServerItem = CServerListData::shared()->EmunGameServerItem(it)))
	{
		if (iKindID == pGameServerItem->m_GameServer.wKindID && iServerID == pGameServerItem->m_GameServer.wServerID)
		{
			return pGameServerItem->m_GameServer.lMinTableScore;
		}
	}
	return 0;
}

bool MENetUtil::checkNetWork()
{
	if (IServerItem::get())
		return IServerItem::get()->SendSocketData(MDM_KN_COMMAND, SUB_KN_DETECT_SOCKET);
	return false;
}

bool MENetUtil::exitGameRoom()
{
	MELOG(MELOG_INFO, "MENetUtil::exitGameRoom().......................... \n");
	if (IServerItem::get())
	{
		IServerItem::get()->SendSocketData(MDM_GR_LOGON, SUB_GR_MOBILE_CLOSE);
		IServerItem::get()->IntermitConnect(true, true);
		IServerItem::destory();
	}
	ClientKernelSink::GetInstance()->Release();
	return true;
}

bool MENetUtil::isGamePlaying()
{
	if (IServerItem::get())
	{
		if (IServerItem::get()->IsPlayingMySelf())
		{
			return IServerItem::get()->OnRecoveryGame();
		}
	}
	return false;
}

void MENetUtil::autoJoin()
{
	if (IServerItem::get())
		IServerItem::get()->PerformQuickSitDown();
}

//获取当前游戏状态
int  MENetUtil::GetGameCurState()
{
	return IClientKernel::get()->GetGameStatus();
}

bool MENetUtil::isCustomServer()
{
	if (IServerItem::get())
		return IServerItem::get()->isCustomServer();
	return false;
}

int MENetUtil::getCustomRoomID()
{
	if (IServerItem::get())
	{
		dword dwUUID = IServerItem::get()->getCustTUUID();
		char sz7[7] = { 0 };
		sprintf(sz7, "%06d", dwUUID);
		DF::shared()->encryptRoomID(sz7);
		return atoi(sz7);
	}
	return 0;
}

void MENetUtil::dismisCustomServer(bool bRoomCreater)
{
	PLAZZ_PRINTF("dismisCustomServer..........................\n");

	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();
	pGlobalUserData->dwRoomExtData = 0;

	if (bRoomCreater)
	{
		IClientKernel::get()->SendSocketData(MDM_GR_MANAGE, SUB_GR_DISMISTABLE);
	}
}

void MENetUtil::dismisCustomServerStartVote()
{
	PLAZZ_PRINTF("dismisCustomServerStartVote..........................\n");
	IClientKernel::get()->SendSocketData(MDM_GR_MANAGE, SUB_GR_DISMISS_STARTVOTE);
}

void MENetUtil::dismisCustomServerVote(int nResult)
{
	PLAZZ_PRINTF("dismisCustomServerVote..........................%d\n", nResult);

	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();

	//变量定义
	PACKET_AIDE_SIZE(512);
	packet.write4Byte(pGlobalUserData->dwUserID);
	packet.writeByte(nResult);
	IClientKernel::get()->SendSocketData(MDM_GR_MANAGE, SUB_GR_DISMISSVOTE, packet.getBuffer(), packet.getPosition());
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

int MENetUtil::getUserTypeByChair(int nChair)
{
	return ClientKernelSink::GetInstance()->getUserTypeByChair(nChair);
}

const char* MENetUtil::getUserIconUrlByChair(int nChair)
{
	return ClientKernelSink::GetInstance()->getUserIconUrlByChair(nChair);
}

const char* MENetUtil::getUserNameByID(int nUserID)
{
	return ClientKernelSink::GetInstance()->getUserNameByID(nUserID);
}

void  MENetUtil::logoutGame()
{
	ClientKernelSink::GetInstance()->leaveGame();
	if (IServerItem::get())
	{
		IServerItem::get()->SendSocketData(MDM_GR_LOGON, SUB_GR_MOBILE_CLOSE);
		IServerItem::get()->IntermitConnect(true, false);
		IServerItem::destory();
	}

	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();
	pGlobalUserData->dwRoomExtData = 0;
	ClientKernelSink::GetInstance()->Release();
}

void MENetUtil::startTalk()
{
	ClientKernelSink::GetInstance()->startTalk();
}

void MENetUtil::endTalk(bool bSend)
{
	ClientKernelSink::GetInstance()->endTalk(bSend);
}

void MENetUtil::playTalk(int nChair, const char* url)
{
	ClientKernelSink::GetInstance()->playTalk(nChair, url);
}

void MENetUtil::playChat(int nChair, int nIdx, int nSex)
{
	ClientKernelSink::GetInstance()->playChat(nChair, nIdx, nSex);
}

void  MENetUtil::setGameOffline()
{
	if (IServerItem::get())
	{
		IServerItem::get()->IntermitConnect(true, false);
		IServerItem::destory();
	}
}

//发送进入场景消息
void MENetUtil::enterGame()
{
	ClientKernelSink::GetInstance()->enterGame();
}

//发送离开场景消息
void MENetUtil::leaveGame()
{
	ClientKernelSink::GetInstance()->leaveGame();
	int nKind = DF::shared()->GetGameKindID();
	if (IServerItem::get() && (IServerItem::get()->isCustomServer() || nKind == 122))
	{
		IServerItem::get()->SendSocketData(MDM_GR_LOGON, SUB_GR_MOBILE_CLOSE);
	}
	ClientKernelSink::GetInstance()->Release();
}

//发送准备消息
void MENetUtil::ready()
{
	ClientKernelSink::GetInstance()->ready();
}

void  MENetUtil::setGameEnterBackground(bool bEnterBackground)
{
	if (bEnterBackground)
	{

	}
}

//设置时钟
void MENetUtil::setGameClock(int wChairID, int nTimerID, int nTimer)
{
	ClientKernelSink::GetInstance()->setGameClock(wChairID, nTimerID, nTimer);
}

//清除时钟
void MENetUtil::clearGameClock(int wChairID)
{
	ClientKernelSink::GetInstance()->clearGameClock(wChairID);
}

//是否可启动时钟
void  MENetUtil::setEnableGameClock(bool bEnable)
{
	ClientKernelSink::GetInstance()->setEnableGameClock(bEnable);
}

//设置托管
void MENetUtil::setTrustee(bool Trustee)
{
	ClientKernelSink::GetInstance()->setTrustee(Trustee);
}

//出牌消息
void MENetUtil::chuPai(int idxPai)
{
	ClientKernelSink::GetInstance()->chuPai(idxPai);
}

//出牌操作消息
void MENetUtil::operatePai(int nOperateCode, int idxPai)
{
	ClientKernelSink::GetInstance()->operatePai(nOperateCode, idxPai);
}

//设置抵注消息
void MENetUtil::setDizhu(int nDizhu)
{
	ClientKernelSink::GetInstance()->setDizhu(nDizhu);
}

//认输消息
void MENetUtil::admitDefeat()
{
	ClientKernelSink::GetInstance()->admitDefeat();
}

//获取桌子玩家最小的金币数量
int MENetUtil::getTableMinGold()
{
	return ClientKernelSink::GetInstance()->getTableMinGold();
}

//选牌定缺消息
void MENetUtil::selectPai(int nType)
{
	ClientKernelSink::GetInstance()->selectPai(nType);
}

//换三张消息
void MENetUtil::changePai(int nCard1, int nCard2, int nCard3)
{
	ClientKernelSink::GetInstance()->changePai(nCard1, nCard2, nCard3);
}

//获取庄家用户
int MENetUtil::getCurBanker()
{
	return ClientKernelSink::GetInstance()->getCurBanker();
}

//用户下注消息
void MENetUtil::placeBet(int cbBetArea, int lBetScore)
{
	ClientKernelSink::GetInstance()->placeBet(cbBetArea, lBetScore);
}

//申请庄家消息
void MENetUtil::applyBanker()
{
	ClientKernelSink::GetInstance()->applyBanker();
}
//取消申请消息
void MENetUtil::cancelBanker()
{
    ClientKernelSink::GetInstance()->cancelBanker();
}

//管理员命令消息
void MENetUtil::adminCmd(int cbReqType)
{
	ClientKernelSink::GetInstance()->adminCmd(cbReqType);
}

//获取区域最大下注
unsigned int MENetUtil::GetMaxPlayerScore(int cbBetArea)
{
	return ClientKernelSink::GetInstance()->GetMaxPlayerScore(cbBetArea);
}

//获取总下注
unsigned int MENetUtil::GetAreaTotalScore(int cbBetArea)
{
	return ClientKernelSink::GetInstance()->GetAreaTotalScore(cbBetArea);
}

//获取自己总下注
unsigned int MENetUtil::GetAreaPlayerScore(int cbBetArea)
{
	return ClientKernelSink::GetInstance()->GetAreaPlayerScore(cbBetArea);
}

//获取玩家自由金币
unsigned int  MENetUtil::GetPlayerFreeScore()
{
	return ClientKernelSink::GetInstance()->GetPlayerFreeScore();
}

//获取牌点数
int MENetUtil::GetCardPip(int nCardID)
{
	return ClientKernelSink::GetInstance()->GetCardPip(nCardID);
}

//
void MENetUtil::getBet()
{
	ClientKernelSink::GetInstance()->getBet();
}