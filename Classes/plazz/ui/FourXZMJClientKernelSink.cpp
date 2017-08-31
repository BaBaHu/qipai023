#include "FourXZMJClientKernelSink.h"
#include "MTNotification.h"
#include "MECallBackListenerHelper.h"
#include "../utils/Timer.h"
#include "cocos2d.h"
#include "../kernel/game/CClientKernel.h"
#include "../msg/CMD_FourXZMJ.h"
#include "MELog.h"

USING_NS_CC;
using namespace rapidjson;

//构造函数
FourXZMJClientKernelSink::FourXZMJClientKernelSink()
{
	
}

//析构函数
FourXZMJClientKernelSink::~FourXZMJClientKernelSink()
{

}

//////////////////////////////////////////////////////////////////////////
//游戏事件

//旁观消息
bool FourXZMJClientKernelSink::OnEventLookonMode(void* data, int dataSize)
{
	return true;
}

//场景消息
bool FourXZMJClientKernelSink::OnEventSceneMessage(byte cbGameStatus, bool bLookonUser, void* data, int dataSize)
{
	switch (cbGameStatus)
	{
	case GS_MJ_FREE:
		{
			IClientKernel* kernel = IClientKernel::get();
			for (word i = 0; i<DF::shared()->GetGamePlayer(); i++){
				IClientUserItem* m_UserItem = kernel->GetTableUserItem(i);
				if(m_UserItem != NULL){
					OnEventUserEnter(m_UserItem,bLookonUser);
				}
			}
			
			//TODO
			if (sizeof(CMD_S_StatusFree) != dataSize) return false;
			CMD_S_StatusFree* pCsc = (CMD_S_StatusFree*)data;

			LuaValueDict dict;
			dict["lCellScore"] = LuaValue::intValue((int)pCsc->lCellScore);
			dict["wBankerUser"] = LuaValue::intValue((int)pCsc->wBankerUser);
			dict["bAvertCheatMode"] = LuaValue::booleanValue(pCsc->bAvertCheatMode);

			LuaValueDict dict1;
			for (size_t i = 0; i < DF::shared()->GetGamePlayer(); i++)
			{
				dict1[StringUtils::format("%d", i + 1).c_str()] = LuaValue::booleanValue(pCsc->bTrustee[i]);
			}
			dict["bTrustee"] = LuaValue::dictValue(dict1);

			bool bShowReady = false;
			if (!IClientKernel::get()->IsLookonMode() &&
				IClientKernel::get()->GetMeUserItem()->GetUserStatus() != US_READY && IClientKernel::get()->GetMeUserItem()->GetCustomTableInfo()->dwCreateUser == 0)
			{
				bShowReady = true;
				StartGameClock(IClientKernel::get()->GetMeChairID(), IDI_START_GAME, TIME_START_GAME);
			}
			dict["bShowReady"] = LuaValue::booleanValue(bShowReady);

			int ret = 0;
			do
			{
				LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameStateOkBack");
				CC_BREAK_IF(0 == nLuaHandler);
				LuaEngine* pEngine = LuaEngine::getInstance();
				LuaStack* pStack = pEngine->getLuaStack();
				lua_State *tolua_s = pStack->getLuaState();
				lua_settop(tolua_s, 0);
				pStack->pushLuaValueDict(dict);
				ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
			} while (0);
			UpdateCustomTableInfo();
			return true;
		}
	case GS_MJ_PLAY:
		{
			IClientKernel* kernel = IClientKernel::get();
			for (word i = 0; i<DF::shared()->GetGamePlayer(); i++){
				IClientUserItem* m_UserItem = kernel->GetTableUserItem(i);
				if(m_UserItem != NULL){
					OnEventUserEnter(m_UserItem,bLookonUser);
				}
			}

			if (sizeof(CMD_S_StatusPlay) != dataSize) return false;
			CMD_S_StatusPlay* pCsc = (CMD_S_StatusPlay*)data;

			LuaValueDict dict;
			
			dict["lCellScore"] = LuaValue::intValue((int)pCsc->lCellScore);
			dict["wBankerUser"] = LuaValue::intValue((int)pCsc->wBankerUser);
			dict["wCurrentUser"] = LuaValue::intValue((int)pCsc->wCurrentUser);
			
			dict["cbActionCard"] = LuaValue::intValue((int)pCsc->cbActionCard);
			dict["cbActionMask"] = LuaValue::intValue((int)pCsc->cbActionMask);
			dict["cbLeftCardCount"] = LuaValue::intValue((int)pCsc->cbLeftCardCount);
			dict["wOutCardUser"] = LuaValue::intValue((int)pCsc->wOutCardUser);
			dict["cbOutCardData"] = LuaValue::intValue((int)pCsc->cbOutCardData);
			dict["wHeapHead"] = LuaValue::intValue((int)pCsc->wHeapHand);
			dict["wHeapTail"] = LuaValue::intValue((int)pCsc->wHeapTail);
			dict["cbCardCount"] = LuaValue::intValue((int)pCsc->cbCardCount);
			dict["cbSendCardData"] = LuaValue::intValue((int)pCsc->cbSendCardData);
			dict["bSelectColor"] = LuaValue::booleanValue(pCsc->bSelectColor);
			dict["bChanged"] = LuaValue::booleanValue(pCsc->bChanged);

			int myChairId = IClientKernel::get()->GetMeChairID();
			if (pCsc->wBankerUser == myChairId)
			{
				dict["isBankerUser"] = LuaValue::booleanValue(true);
			}
			else
			{
				dict["isBankerUser"] = LuaValue::booleanValue(false);
			}

			LuaValueDict dict0;
			for (size_t i = 0; i < MAX_COUNT; i++)
			{
				dict0[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->cbCardData[i]);
			}
			dict["cbCardData"] = LuaValue::dictValue(dict0);

			LuaValueDict dict1;
			LuaValueDict dict2;
			LuaValueDict dict3;
			LuaValueDict dict4;
			LuaValueDict dict5;
			LuaValueDict dict6;
			LuaValueDict dict7;
			LuaValueDict dict8;
			LuaValueDict dict9;
			LuaValueDict dict10;
			LuaValueDict dict11;
			for (size_t i = 0; i < DF::shared()->GetGamePlayer(); i++)
			{
				dict11[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->llChiHuScore[i]);
				dict10[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->cbProvideCard[i]);
				dict9[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->wProvider[i]);
				dict8[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->cbSelectCard[i]);
				dict7[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->wWinOrder[i]);
				dict1[StringUtils::format("%d", i + 1).c_str()] = LuaValue::booleanValue(pCsc->bTrustee[i]);
				dict2[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->cbDiscardCount[i]);

				LuaValueDict dict31;
				for (size_t j = 0; j < pCsc->cbDiscardCount[i]; j++)
				{
					dict31[StringUtils::format("%d", j + 1).c_str()] = LuaValue::intValue((int)pCsc->cbDiscardCard[i][j]);
				}
				dict3[StringUtils::format("%d", i + 1).c_str()] = LuaValue::dictValue(dict31);

				dict4[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->cbWeaveCount[i]);

				LuaValueDict dict51;
				for (size_t j = 0; j < 2; j++)
				{
					dict51[StringUtils::format("%d", j + 1).c_str()] = LuaValue::intValue((int)pCsc->cbHeapCardInfo[i][j]);
				}
				dict5[StringUtils::format("%d", i + 1).c_str()] = LuaValue::dictValue(dict51);

				
				LuaValueDict dict63;
				for (size_t j = 0; j < pCsc->cbWeaveCount[i]; j++)
				{
					LuaValueDict dict61;
					dict61["cbWeaveKind"] = LuaValue::intValue((int)pCsc->WeaveItemArray[i][j].cbWeaveKind);
					dict61["cbCenterCard"] = LuaValue::intValue((int)pCsc->WeaveItemArray[i][j].cbCenterCard);
					dict61["cbPublicCard"] = LuaValue::intValue((int)pCsc->WeaveItemArray[i][j].cbPublicCard);
					dict61["wProvideUser"] = LuaValue::intValue((int)pCsc->WeaveItemArray[i][j].wProvideUser);
					dict63[StringUtils::format("%d", j + 1).c_str()] = LuaValue::dictValue(dict61);
				}
				dict6[StringUtils::format("%d", i + 1).c_str()] = LuaValue::dictValue(dict63);
			}
			dict["llChiHuScore"] = LuaValue::dictValue(dict11);
			dict["cbProvideCard"] = LuaValue::dictValue(dict10);
			dict["wProvider"] = LuaValue::dictValue(dict9);
			dict["cbSelectCard"] = LuaValue::dictValue(dict8);
			dict["wWinOrder"] = LuaValue::dictValue(dict7);
			dict["bTrustee"] = LuaValue::dictValue(dict1);
			dict["cbDiscardCount"] = LuaValue::dictValue(dict2);
			dict["cbDiscardCard"] = LuaValue::dictValue(dict3);
			dict["cbWeaveCount"] = LuaValue::dictValue(dict4);
			dict["cbHeapCardInfo"] = LuaValue::dictValue(dict5);
			dict["WeaveItemArray"] = LuaValue::dictValue(dict6);

			int ret = 0;
			do
			{
				LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameRecoveryBack");
				CC_BREAK_IF(0 == nLuaHandler);
				LuaEngine* pEngine = LuaEngine::getInstance();
				LuaStack* pStack = pEngine->getLuaStack();
				lua_State *tolua_s = pStack->getLuaState();
				lua_settop(tolua_s, 0);
				pStack->pushLuaValueDict(dict);
				ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
			} while (0);
			UpdateCustomTableInfo();
			return true;
		}
	}

	return false;
}

//游戏消息
bool FourXZMJClientKernelSink::OnEventGameMessage(int sub, void* data, int wSize)
{
	if (!m_bRunning)
		return true;
	MELOG(MELOG_INFO, "FourMJClientKernelSink OnEventGameMessage msg code: %d\n", sub);
 	switch(sub)
 	{
	case SUB_S_GAME_START:
		return OnGameStart(data, wSize);
	case SUB_S_SELECT:
		return OnGameSelectPai(data, wSize);
	case SUB_S_OUT_CARD:
		return OnGameChuPai(data, wSize);
	case SUB_S_SEND_CARD:
		return OnGameSendPai(data, wSize);
	case SUB_S_OPERATE_NOTIFY:
		return OnGameOperateNotify(data, wSize);
	case SUB_S_OPERATE_RESULT:
		return OnGameOperateResult(data, wSize);
	case SUB_S_CHI_HU:
		return OnGameChiHu(data, wSize);
	case SUB_S_GANG_SCORE:
		return OnGameGangScore(data, wSize);
	case SUB_S_GAME_END:
		return OnGameOver(data, wSize);
	case SUB_S_TRUSTEE:
 		return OnGameTrustee(data, wSize);
	case SUB_S_CHANGE_CARD:
		return OnGameChangeCard(data, wSize);
 	}

	////错误断言
	//ASSERT(false);

	return true;
}

bool FourXZMJClientKernelSink::OnGameStart(void* data, word wSize)
{
	if (sizeof(CMD_S_GameStart) != wSize) return false;
	CMD_S_GameStart* pCsc = (CMD_S_GameStart*)data;

	//设置状态
	IClientKernel::get()->SetGameStatus(GS_MJ_PLAY);
	
	LuaValueDict dict;
	dict["wGameMode"] = LuaValue::intValue(pCsc->wGameMode);
	dict["sice1Count"] = LuaValue::intValue((word)(pCsc->lSiceCount >> 16));
	dict["sice2Count"] = LuaValue::intValue((word)pCsc->lSiceCount);
	dict["bankerUser"]	= LuaValue::intValue((int)pCsc->wBankerUser);
	dict["currentUser"] = LuaValue::intValue((int)pCsc->wCurrentUser);
	dict["userAction"]	= LuaValue::intValue((int)pCsc->cbUserAction);
	dict["heapHead"] = LuaValue::intValue((int)pCsc->wHeapHand);
	dict["heapTail"]	= LuaValue::intValue((int)pCsc->wHeapTail);
	dict["cbLeftCardCount"] = LuaValue::intValue((int)pCsc->cbLeftCardCount);
	dict["bGameMatch"] = LuaValue::booleanValue(pCsc->bGameMatch);
	dict["lCellScore"] = LuaValue::intValue((int)pCsc->lCellScore);

	int myChairId = IClientKernel::get()->GetMeChairID();
	int nCardCount = MAX_COUNT;
	if (pCsc->wBankerUser == myChairId)
	{
		dict["isBankerUser"] = LuaValue::booleanValue(true);
		nCardCount = MAX_COUNT;
	}
	else
	{
		dict["isBankerUser"] = LuaValue::booleanValue(false);
		nCardCount = MAX_COUNT -1;
	}

	LuaValueDict dict1;
	for (size_t i = 0; i < nCardCount; i++)
	{
		dict1[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->cbCardData[i]);
	}
	dict["cardData"] = LuaValue::dictValue(dict1);

	LuaValueDict dict2;
	for (size_t i = 0; i < DF::shared()->GetGamePlayer(); i++)
	{
		LuaValueDict dict3;
		for (size_t j = 0; j < 2; j++)
		{
			dict3[StringUtils::format("%d", j + 1).c_str()] = LuaValue::intValue((int)pCsc->cbHeapCardInfo[i][j]);
		}
		dict2[StringUtils::format("%d", i + 1).c_str()] = LuaValue::dictValue(dict3);
	}
	dict["heapCardInfo"] = LuaValue::dictValue(dict2);

	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameStartBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		//pStack->pushString(StringUtils::format("%s", buffer.GetString()).c_str());
		pStack->pushLuaValueDict(dict);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
	} while (0);

	return true;
}

bool FourXZMJClientKernelSink::OnGameSelectPai(void* data, word wSize)
{
	if (sizeof(CMD_S_SelectCard) != wSize) return false;
	CMD_S_SelectCard* pCsc = (CMD_S_SelectCard*)data;

	if (pCsc->wCurrentUser == INVALID_CHAIR) return true;

	LuaValueDict dict;
	dict["wCurrentUser"] = LuaValue::intValue((int)pCsc->wCurrentUser);
	dict["wUserAction"] = LuaValue::intValue((int)pCsc->wUserAction);

	LuaValueDict dict1;
	for (size_t i = 0; i < DF::shared()->GetGamePlayer(); i++)
	{
		dict1[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->wSelectCard[i]);
	}
	dict["wSelectCard"] = LuaValue::dictValue(dict1);

	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameSelectPaiBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushLuaValueDict(dict);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
	} while (0);
	IClientKernel::get()->KillGameClock(IDI_SELECT_CARD);
	return true;
}

bool FourXZMJClientKernelSink::OnGameChuPai(void* data, word wSize)
{
	if (sizeof(CMD_S_OutCard) != wSize) return false;
	CMD_S_OutCard* pCsc = (CMD_S_OutCard*)data;

	LuaValueDict dict;
	dict["outCardUser"] = LuaValue::intValue((int)pCsc->wOutCardUser);
	dict["outCardData"] = LuaValue::intValue((int)pCsc->cbOutCardData);

	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameChuPaiBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushLuaValueDict(dict);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
	} while (0);

	//计时等待对方
	IClientKernel::get()->KillGameClock(IDI_OUT_CARD);
	IClientKernel::get()->KillGameClock(IDI_WAIT_CARD);
	IClientKernel::get()->KillGameClock(IDI_OPERATE_CARD);
	StartGameClock(pCsc->wOutCardUser, IDI_WAIT_CARD, TIME_OPERATE_CARD);
	return true;
}

bool FourXZMJClientKernelSink::OnGameSendPai(void* data, word wSize)
{
	if (sizeof(CMD_S_SendCard) != wSize) return false;
	CMD_S_SendCard* pCsc = (CMD_S_SendCard*)data;

	LuaValueDict dict;
	dict["cardData"] = LuaValue::intValue((int)pCsc->cbCardData);
	dict["cbGangCardData"] = LuaValue::intValue((int)pCsc->cbGangCardData);
	dict["actionMask"] = LuaValue::intValue((int)pCsc->cbActionMask);
	dict["crrentUser"] = LuaValue::intValue((int)pCsc->wCurrentUser);
	dict["tail"] = LuaValue::booleanValue(pCsc->bTail);

	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameSeedPaiBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushLuaValueDict(dict);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
	} while (0);

	IClientKernel::get()->KillGameClock(IDI_OUT_CARD);
	IClientKernel::get()->KillGameClock(IDI_WAIT_CARD);
	IClientKernel::get()->KillGameClock(IDI_OPERATE_CARD);
	StartGameClock(pCsc->wCurrentUser, IDI_OUT_CARD, TIME_OUT_CARD);
	return true;
}

bool FourXZMJClientKernelSink::OnGameOperateNotify(void* data, word wSize)
{
	if (sizeof(CMD_S_OperateNotify) != wSize) return false;
	CMD_S_OperateNotify* pCsc = (CMD_S_OperateNotify*)data;

	LuaValueDict dict;
	dict["resumeUser"] = LuaValue::intValue((int)pCsc->wResumeUser);
	dict["actionMask"] = LuaValue::intValue((int)pCsc->cbActionMask);
	dict["actionCard"] = LuaValue::intValue((int)pCsc->cbActionCard);

	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameOperateNotifyBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushLuaValueDict(dict);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
	} while (0);

	IClientKernel::get()->KillGameClock(IDI_OUT_CARD);
	IClientKernel::get()->KillGameClock(IDI_WAIT_CARD);
	IClientKernel::get()->KillGameClock(IDI_OPERATE_CARD);
	StartGameClock(pCsc->wResumeUser, IDI_OPERATE_CARD, TIME_OPERATE_CARD);
	return true;
}

bool FourXZMJClientKernelSink::OnGameOperateResult(void* data, word wSize)
{
	if (sizeof(CMD_S_OperateResult) != wSize) return false;
	CMD_S_OperateResult* pCsc = (CMD_S_OperateResult*)data;

	LuaValueDict dict;
	dict["wOperateUser"] = LuaValue::intValue((int)pCsc->wOperateUser);
	dict["wProvideUser"] = LuaValue::intValue((int)pCsc->wProvideUser);
	dict["cbOperateCode"] = LuaValue::intValue((int)pCsc->cbOperateCode);
	dict["cbOperateCard"] = LuaValue::intValue((int)pCsc->cbOperateCard);

	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameOperateResultBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushLuaValueDict(dict);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
	} while (0);

	IClientKernel::get()->KillGameClock(IDI_OUT_CARD);
	IClientKernel::get()->KillGameClock(IDI_WAIT_CARD);
	IClientKernel::get()->KillGameClock(IDI_OPERATE_CARD);
	StartGameClock(pCsc->wOperateUser, IDI_OUT_CARD, TIME_OUT_CARD);
	return true;
}

bool FourXZMJClientKernelSink::OnGameChiHu(void* data, word wSize)
{
	if (sizeof(CMD_S_ChiHu) != wSize) return false;
	CMD_S_ChiHu* pCsc = (CMD_S_ChiHu*)data;

	LuaValueDict dict;
	dict["wChiHuUser"] = LuaValue::intValue((int)pCsc->wChiHuUser);
	dict["wProviderUser"] = LuaValue::intValue((int)pCsc->wProviderUser);
	dict["cbChiHuCard"] = LuaValue::intValue((int)pCsc->cbChiHuCard);
	dict["cbCardCount"] = LuaValue::intValue((int)pCsc->cbCardCount);
	dict["lGameScore"] = LuaValue::intValue((int)pCsc->lGameScore);
	dict["cbWinOrder"] = LuaValue::intValue((int)pCsc->cbWinOrder);

	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameChiHuBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushLuaValueDict(dict);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
	} while (0);

	return true;
}

bool FourXZMJClientKernelSink::OnGameGangScore(void* data, word wSize)
{
	if (sizeof(CMD_S_GangScore) != wSize) return false;
	CMD_S_GangScore* pCsc = (CMD_S_GangScore*)data;

	LuaValueDict dict;
	dict["wChairId"] = LuaValue::intValue((int)pCsc->wChairId);
	dict["cbXiaYu"] = LuaValue::intValue((int)pCsc->cbXiaYu);
	LuaValueDict dict1;
	for (size_t i = 0; i < DF::shared()->GetGamePlayer(); i++)
	{
		dict1[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->lGangScore[i]);
	}
	dict["lGangScore"] = LuaValue::dictValue(dict1);

	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameGangScoreBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushLuaValueDict(dict);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
	} while (0);

	return true;
}

bool FourXZMJClientKernelSink::OnGameOver(void* data, word wSize)
{
	if (sizeof(CMD_S_GameEnd) != wSize) return false;
	CMD_S_GameEnd* pCsc = (CMD_S_GameEnd*)data;

	IClientKernel::get()->KillGameClock(IDI_OUT_CARD);
	IClientKernel::get()->KillGameClock(IDI_OPERATE_CARD);
	IClientKernel::get()->KillGameClock(IDI_WAIT_CARD);

	//设置状态
	IClientKernel::get()->SetGameStatus(GS_MJ_FREE);

	LuaValueDict dict;
	dict["wLeftUser"] = LuaValue::intValue((int)pCsc->wLeftUser);
	dict["lChuShi"] = LuaValue::intValue((int)pCsc->lChuShi);
	dict["lDangQian"] = LuaValue::intValue((int)pCsc->lDangQian);
	
	LuaValueDict dict1;
	LuaValueDict dict2;
	LuaValueDict dict3;
	LuaValueDict dict4;
	LuaValueDict dict5;
	LuaValueDict dict6;
	LuaValueDict dict7;
	LuaValueDict dict8;
	LuaValueDict dict9;
	LuaValueDict dict10;
	for (size_t i = 0; i < DF::shared()->GetGamePlayer(); i++)
	{
		dict1[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->dwChiHuRight[i]);
		dict2[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->wWinOrder[i]);
		dict3[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->lGameScore[i]);
		dict4[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->lGangScore[i]);
		dict5[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->cbCardCount[i]);
		dict7[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->lGameTax[i]);
		dict8[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->wProvideUser[i]);
		dict9[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->cbGenCount[i]);
		dict10[StringUtils::format("%d", i + 1).c_str()]= LuaValue::intValue((int)pCsc->wWinFanShu[i]);

		LuaValueDict dict61;
		for (size_t j = 0; j < MAX_COUNT; j++)
		{
			dict61[StringUtils::format("%d", j + 1).c_str()] = LuaValue::intValue((int)pCsc->cbCardData[i][j]);
		}
		dict6[StringUtils::format("%d", i + 1).c_str()] = LuaValue::dictValue(dict61);
	}

	dict["dwChiHuRight"] = LuaValue::dictValue(dict1);
	dict["wWinOrder"] = LuaValue::dictValue(dict2);
	dict["lGameScore"] = LuaValue::dictValue(dict3);
	dict["lGangScore"] = LuaValue::dictValue(dict4);
	dict["cbGenCount"] = LuaValue::dictValue(dict9);
	dict["cbCardCount"] = LuaValue::dictValue(dict5);
	dict["cbCardData"] = LuaValue::dictValue(dict6);
	dict["lGameTax"] = LuaValue::dictValue(dict7);
	dict["wProvideUser"] = LuaValue::dictValue(dict8);
	dict["wWinFanShu"] = LuaValue::dictValue(dict10);

	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameOverBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushLuaValueDict(dict);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
	} while (0);

	if (!IClientKernel::get()->IsLookonMode() && IClientKernel::get()->GetMeUserItem()->GetCustomTableInfo()->dwCreateUser == 0)
	{
		StartGameClock(IClientKernel::get()->GetMeChairID(), IDI_START_GAME, TIME_START_GAME);
	}
	return true;
}

bool FourXZMJClientKernelSink::OnGameTrustee(void* data, word wSize)
{
	if (sizeof(CMD_S_Trustee) != wSize) return false;
	CMD_S_Trustee* pCsc = (CMD_S_Trustee*)data;

	LuaValueDict dict;
	dict["bTrustee"] = LuaValue::booleanValue(pCsc->bTrustee);
	dict["wChairID"] = LuaValue::intValue((int)pCsc->wChairID);

	int myChairId = IClientKernel::get()->GetMeChairID();
	if (pCsc->wChairID == myChairId)
	{
		dict["isSelf"] = LuaValue::booleanValue(true);
	}
	else
	{
		dict["isSelf"] = LuaValue::booleanValue(false);
	}

	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameTrusteeBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushLuaValueDict(dict);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
	} while (0);

	return true;
}

bool FourXZMJClientKernelSink::OnGameChangeCard(void* data, word wSize)
{
	if (sizeof(CMD_S_ChangeCard) != wSize) return false;
	CMD_S_ChangeCard* pCsc = (CMD_S_ChangeCard*)data;

	LuaValueDict dict;
	dict["wChangeDirection"] = LuaValue::intValue((int)pCsc->wChangeDirection);

	LuaValueDict dict1;
	for (size_t i = 0; i < MAX_COUNT; i++)
	{
		dict1[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->cbCardData[i]);
	}
	dict["cardData"] = LuaValue::dictValue(dict1);

	LuaValueDict dict2;
	for (size_t i = 0; i < DF::shared()->GetGamePlayer(); i++)
	{
		LuaValueDict dict3;
		for (size_t j = 0; j < 3; j++)
		{
			dict3[StringUtils::format("%d", j + 1).c_str()] = LuaValue::intValue((int)pCsc->cbChangeCard[i][j]);
		}
		dict2[StringUtils::format("%d", i + 1).c_str()] = LuaValue::dictValue(dict3);
	}
	dict["cbChangeCard"] = LuaValue::dictValue(dict2);

	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameChangeCardBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushLuaValueDict(dict);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
	} while (0);
	IClientKernel::get()->KillGameClock(IDI_CHANGE_CARD);
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//设置托管
void FourXZMJClientKernelSink::setTrustee(bool Trustee)
{
	PLAZZ_PRINTF("flow->setTrustee %d", Trustee);

	//变量定义
	PACKET_AIDE_SIZE(512);
	packet.writeByte(Trustee);
	//发送数据
	IClientKernel::get()->SendSocketData(SUB_S_MAIN_MSG, SUB_C_TRUSTEE, packet.getBuffer(), packet.getPosition());
}

//出牌消息
void FourXZMJClientKernelSink::chuPai(int idxPai)
{
	PLAZZ_PRINTF("flow->ClientKernelSink::chuPai %d", idxPai);

	//变量定义
	PACKET_AIDE_SIZE(512);
	packet.writeByte(idxPai);
	//发送数据
	IClientKernel::get()->SendSocketData(SUB_S_MAIN_MSG, SUB_C_OUT_CARD, packet.getBuffer(), packet.getPosition());
}

//出牌操作消息
void FourXZMJClientKernelSink::operatePai(int nOperateCode, int idxPai)
{
	PLAZZ_PRINTF("flow->ClientKernelSink::operatePai nOperateCode=%d, idxPai=%d", nOperateCode, idxPai);

	//变量定义
	PACKET_AIDE_SIZE(512);
	packet.writeByte(nOperateCode);
	packet.writeByte(idxPai);
	//发送数据
	IClientKernel::get()->SendSocketData(SUB_S_MAIN_MSG, SUB_C_OPERATE_CARD, packet.getBuffer(), packet.getPosition());
}

//选牌定缺消息
void FourXZMJClientKernelSink::selectPai(int nType)
{
	PLAZZ_PRINTF("flow->ClientKernelSink::selectPai %d", nType);
	IClientKernel::get()->KillGameClock(IDI_SELECT_CARD);
	//变量定义
	PACKET_AIDE_SIZE(512);
	packet.writeByte(nType);
	//发送数据
	IClientKernel::get()->SendSocketData(SUB_S_MAIN_MSG, SUB_C_SELECT, packet.getBuffer(), packet.getPosition());
}

//换三张消息
void FourXZMJClientKernelSink::changePai(int nCard1, int nCard2, int nCard3)
{
	PLAZZ_PRINTF("flow->ClientKernelSink::changePai %d, %d, %d", nCard1, nCard2, nCard3);
	IClientKernel::get()->KillGameClock(IDI_CHANGE_CARD);
	//变量定义
	PACKET_AIDE_SIZE(512);
	packet.writeByte(nCard1);
	packet.writeByte(nCard2);
	packet.writeByte(nCard3);

	//发送数据
	IClientKernel::get()->SendSocketData(SUB_S_MAIN_MSG, SUB_C_CHANGE, packet.getBuffer(), packet.getPosition());
}