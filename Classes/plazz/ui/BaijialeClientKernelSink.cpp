#include "BaijialeClientKernelSink.h"
#include "MTNotification.h"
#include "MECallBackListenerHelper.h"
#include "../utils/Timer.h"
#include "cocos2d.h"
#include "../kernel/game/CClientKernel.h"
#include "MELog.h"
#include "../msg/CMD_Baccarat.h"

USING_NS_CC;
using namespace rapidjson;

//构造函数
BaijialeClientKernelSink::BaijialeClientKernelSink()
{
	m_bEnableSysBanker = false;
	m_wBankerUser = INVALID_CHAIR;
	m_lBankerScore = 0;
	m_lMeMaxScore = 0;
	m_lAreaLimitScore = 0;
	m_lPlayFreeSocre = 0;
	memset(m_lAllBet, 0, sizeof(m_lAllBet));
	memset(m_lPlayBet, 0, sizeof(m_lPlayBet));

	memset(m_cbCardCount, 0, sizeof(m_cbCardCount));
	memset(m_cbTableCardArray, 0, sizeof(m_cbTableCardArray));

	m_vBet.clear();
}

//析构函数
BaijialeClientKernelSink::~BaijialeClientKernelSink()
{

}

//////////////////////////////////////////////////////////////////////////
//游戏事件

//旁观消息
bool BaijialeClientKernelSink::OnEventLookonMode(void* data, int dataSize)
{
	return true;
}

//场景消息
bool BaijialeClientKernelSink::OnEventSceneMessage(byte cbGameStatus, bool bLookonUser, void* data, int dataSize)
{
	PLAZZ_PRINTF("BaijialeClientKernelSink OnEventSceneMessage cbGameStatus: %d\n", cbGameStatus);
	switch (cbGameStatus)
	{
	case GAME_SCENE_FREE:			//空闲状态
		{
			/*IClientKernel* kernel = IClientKernel::get();
			for (word i = 0; i<DF::shared()->GetGamePlayer(); i++){
				IClientUserItem* m_UserItem = kernel->GetTableUserItem(i);
				if(m_UserItem != NULL){
					OnEventUserEnter(m_UserItem,bLookonUser);
				}
			}*/
			
			//TODO
			if (sizeof(CMD_S_StatusFree) != dataSize) return false;
			CMD_S_StatusFree* pCsc = (CMD_S_StatusFree*)data;

			//设置状态
			IClientKernel::get()->SetGameStatus(GAME_SCENE_FREE);
			StartGameClock(IClientKernel::get()->GetMeChairID(), IDI_FREE, pCsc->cbTimeLeave);

			//设置变量
			m_wBankerUser = pCsc->wBankerUser;
			m_lBankerScore = pCsc->lBankerScore;
			m_lAreaLimitScore = pCsc->lAreaLimitScore;
			m_bEnableSysBanker = pCsc->bEnableSysBanker;
			m_lPlayFreeSocre = pCsc->lPlayFreeSocre;

			LuaValueDict dict;
			dict["cbTimeLeave"] = LuaValue::intValue((int)pCsc->cbTimeLeave);
			dict["lPlayFreeSocre"] = LuaValue::intValue((int)pCsc->lPlayFreeSocre);
			dict["wBankerUser"] = LuaValue::intValue((int)pCsc->wBankerUser);
			dict["lBankerScore"] = LuaValue::intValue((int)pCsc->lBankerScore);
			dict["lBankerWinScore"] = LuaValue::intValue((int)pCsc->lBankerWinScore);
			dict["wBankerTime"] = LuaValue::intValue((int)pCsc->wBankerTime);
			dict["bEnableSysBanker"] = LuaValue::booleanValue(pCsc->bEnableSysBanker);
			dict["lApplyBankerCondition"] = LuaValue::intValue((int)pCsc->lApplyBankerCondition);
			dict["lAreaLimitScore"] = LuaValue::intValue((int)pCsc->lAreaLimitScore);
			dict["wFaceID"] = LuaValue::intValue((int)pCsc->wFaceID);

			if (pCsc->wBankerUser != INVALID_CHAIR && IClientKernel::get()->GetTableUserItem(pCsc->wBankerUser))
			{
				//玩家坐庄
				dict["isPlayerBanker"] = LuaValue::intValue(0);
				IClientUserItem* pUserItem = IClientKernel::get()->GetTableUserItem(pCsc->wBankerUser);
				dict["szName"] = LuaValue::stringValue(pUserItem->GetNickName());
				dict["nGold"] = LuaValue::intValue(pUserItem->GetUserScore());
			}
			else if (pCsc->bEnableSysBanker)
			{
				//系统坐庄
				dict["isPlayerBanker"] = LuaValue::intValue(1);
			}
			else
			{
				//无人坐庄
				dict["isPlayerBanker"] = LuaValue::intValue(2);
			}
			
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

			
			return true;
		}
	case GAME_SCENE_PLAY:		//游戏状态
	case GAME_SCENE_END:		//结束状态
		{
			/*IClientKernel* kernel = IClientKernel::get();
			for (word i = 0; i<DF::shared()->GetGamePlayer(); i++){
				IClientUserItem* m_UserItem = kernel->GetTableUserItem(i);
				if(m_UserItem != NULL){
					OnEventUserEnter(m_UserItem,bLookonUser);
				}
			}*/

			if (sizeof(CMD_S_StatusPlay) != dataSize) return false;
			CMD_S_StatusPlay* pCsc = (CMD_S_StatusPlay*)data;

			//设置状态
			IClientKernel::get()->SetGameStatus(pCsc->cbGameStatus);
			//设置时间
			if (pCsc->cbGameStatus == GAME_SCENE_END)
				StartGameClock(IClientKernel::get()->GetMeChairID(), IDI_DISPATCH_CARD, pCsc->cbTimeLeave);
			else
				StartGameClock(IClientKernel::get()->GetMeChairID(), IDI_PLACE_JETTON, pCsc->cbTimeLeave);

			//设置变量
			m_wBankerUser = pCsc->wBankerUser;
			m_lBankerScore = pCsc->lBankerScore;
			m_lAreaLimitScore = pCsc->lAreaLimitScore;
			m_lMeMaxScore = pCsc->lPlayBetScore;
			m_bEnableSysBanker = pCsc->bEnableSysBanker;
			m_lPlayFreeSocre = pCsc->lPlayFreeSocre;

			//下注信息
			memset(m_lAllBet, 0, sizeof(m_lAllBet));
			memset(m_lPlayBet, 0, sizeof(m_lPlayBet));

			memcpy(m_lAllBet, pCsc->lAllBet, sizeof(m_lAllBet));
			memcpy(m_lPlayBet, pCsc->lPlayBet, sizeof(m_lPlayBet));

			//扑克信息
			memset(m_cbCardCount, 0, sizeof(m_cbCardCount));
			memset(m_cbTableCardArray, 0, sizeof(m_cbTableCardArray));

			memcpy(m_cbCardCount, pCsc->cbCardCount, sizeof(m_cbCardCount));
			memcpy(m_cbTableCardArray, pCsc->cbTableCardArray, sizeof(m_cbTableCardArray));

			LuaValueDict dict;
			if (pCsc->wBankerUser != INVALID_CHAIR && IClientKernel::get()->GetTableUserItem(pCsc->wBankerUser))
			{
				//玩家坐庄
				dict["isPlayerBanker"] = LuaValue::intValue(0);
				IClientUserItem* pUserItem = IClientKernel::get()->GetTableUserItem(pCsc->wBankerUser);
				dict["szName"] = LuaValue::stringValue(pUserItem->GetNickName());
				dict["nGold"] = LuaValue::intValue(pUserItem->GetUserScore());
			}
			else if (pCsc->bEnableSysBanker)
			{
				//系统坐庄
				dict["isPlayerBanker"] = LuaValue::intValue(1);
			}
			else
			{
				//无人坐庄
				dict["isPlayerBanker"] = LuaValue::intValue(2);
			}

			dict["cbTimeLeave"] = LuaValue::intValue((int)pCsc->cbTimeLeave);
			dict["cbGameStatus"] = LuaValue::intValue((int)pCsc->cbGameStatus);
			
			dict["lPlayBetScore"] = LuaValue::intValue((int)pCsc->lPlayBetScore);
			dict["lPlayFreeSocre"] = LuaValue::intValue((int)pCsc->lPlayFreeSocre);

			dict["wBankerUser"] = LuaValue::intValue((int)pCsc->wBankerUser);
			dict["lBankerScore"] = LuaValue::intValue((int)pCsc->lBankerScore);
			dict["lBankerWinScore"] = LuaValue::intValue((int)pCsc->lBankerWinScore);
			dict["wBankerTime"] = LuaValue::intValue((int)pCsc->wBankerTime);

			dict["lPlayAllScore"] = LuaValue::floatValue(pCsc->lPlayAllScore);

			dict["bEnableSysBanker"] = LuaValue::booleanValue(pCsc->bEnableSysBanker);
			dict["lApplyBankerCondition"] = LuaValue::intValue((int)pCsc->lApplyBankerCondition);
			dict["lAreaLimitScore"] = LuaValue::intValue((int)pCsc->lAreaLimitScore);
			dict["wFaceID"] = LuaValue::intValue((int)pCsc->wFaceID);

			LuaValueDict dict0;
			LuaValueDict dict1;
			LuaValueDict dict2;
			for (size_t i = 0; i < AREA_MAX; i++)
			{
				dict0[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->lAllBet[i]);
				dict1[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->lPlayBet[i]);
				dict2[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->lPlayScore[i]);
			}
			dict["lAllBet"] = LuaValue::dictValue(dict0);
			dict["lPlayBet"] = LuaValue::dictValue(dict1);
			dict["lPlayScore"] = LuaValue::dictValue(dict2);
			
			LuaValueDict dict3;
			LuaValueDict dict4;
			for (size_t i = 0; i < 2; i++)
			{
				dict3[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->cbCardCount[i]);

				LuaValueDict dict31;
				for (size_t j = 0; j < 3; j++)
				{
					dict31[StringUtils::format("%d", j + 1).c_str()] = LuaValue::intValue((int)pCsc->cbTableCardArray[i][j]);
				}
				dict4[StringUtils::format("%d", i + 1).c_str()] = LuaValue::dictValue(dict31);
			}
			dict["cbCardCount"] = LuaValue::dictValue(dict3);
			dict["cbTableCardArray"] = LuaValue::dictValue(dict4);

			if (pCsc->cbGameStatus == GAME_SCENE_END)
			{
				//计算牌点
				byte cbPlayerCount = m_CardLogic.GetCardListPip(m_cbTableCardArray[INDEX_PLAYER], m_cbCardCount[INDEX_PLAYER]);
				byte cbBankerCount = m_CardLogic.GetCardListPip(m_cbTableCardArray[INDEX_BANKER], m_cbCardCount[INDEX_BANKER]);

				dict["cbPlayerCount"] = LuaValue::intValue((int)cbPlayerCount);
				dict["cbBankerCount"] = LuaValue::intValue((int)cbBankerCount);

				//推断玩家
				byte cbWinArea[AREA_MAX] = { FALSE };
				DeduceWinner(cbWinArea);

				LuaValueDict dict8;
				for (size_t i = 0; i < AREA_MAX; i++)
				{
					dict8[StringUtils::format("%d", i + 1).c_str()] = LuaValue::booleanValue(cbWinArea[i]);
				}
				dict["cbWinArea"] = LuaValue::dictValue(dict8);

				//操作类型
				enOperateResult OperateResult = enOperateResult_NULL;
				if (0.001 < pCsc->lPlayAllScore) OperateResult = enOperateResult_Win;
				else if (pCsc->lPlayAllScore < -0.001) OperateResult = enOperateResult_Lost;
				else OperateResult = enOperateResult_NULL;
				dict["nResult"] = LuaValue::intValue((int)OperateResult);

				//推断赢家
				byte cbWinner, cbKingWinner;
				bool bPlayerTwoPair, bBankerTwoPair;
				DeduceWinner(cbWinner, cbKingWinner, bPlayerTwoPair, bBankerTwoPair);
				dict["cbWinner"] = LuaValue::intValue((int)cbWinner);
				dict["cbKingWinner"] = LuaValue::intValue((int)cbKingWinner);
				dict["bPlayerTwoPair"] = LuaValue::booleanValue(bPlayerTwoPair);
				dict["bBankerTwoPair"] = LuaValue::booleanValue(bBankerTwoPair);
			}
			
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
			return true;
		}
	}

	return false;
}

//游戏消息
bool BaijialeClientKernelSink::OnEventGameMessage(int sub, void* data, int wSize)
{
	if (!m_bRunning)
		return true;
	MELOG(MELOG_INFO, "BaijialeClientKernelSink OnEventGameMessage msg code: %d\n", sub);
 	switch(sub)
 	{
	case SUB_S_GAME_FREE:
		return OnGameFree(data, wSize);
	case SUB_S_GAME_START:
		return OnGameStart(data, wSize);
	case SUB_S_PLACE_JETTON:
		return OnGamePlaceBet(data, wSize);
	case SUB_S_CANCEL_JETTON:
		return OnGameCancelBet(data, wSize);
	case SUB_S_PLACE_JETTON_FAIL:
		return OnGamePlaceBetFail(data, wSize);
	case SUB_S_APPLY_BANKER:
		return OnGameApplyBanker(data, wSize);
	case SUB_S_CANCEL_BANKER:
		return OnGameCancelBanker(data, wSize);
	case SUB_S_CHANGE_BANKER:
		return OnGameChangeBanker(data, wSize);
	case SUB_S_RESORT_BANKER:
		return OnGameReSortBanker(data, wSize);
	case SUB_S_SEND_RECORD:
		return OnGameSendRecord(data, wSize);
	case SUB_S_GAME_END:
		return OnGameOver(data, wSize);
	case SUB_S_AMDIN_COMMAND:
		return OnGameCommandResult(data, wSize);
	case SUB_S_TIP_INFO:
		return OnGameTipInfo(data, wSize);
 	}

	////错误断言
	//ASSERT(false);

	return true;
}

bool BaijialeClientKernelSink::OnGameFree(void* data, word wSize)
{
	if (sizeof(CMD_S_GameFree) != wSize) return false;
	CMD_S_GameFree* pCsc = (CMD_S_GameFree*)data;

	//清空下注
	memset(m_lAllBet, 0, sizeof(m_lAllBet));
	memset(m_lPlayBet, 0, sizeof(m_lPlayBet));

	s_Locker.lock();
	m_vBet.clear();
	s_Locker.unlock();

	LuaValueDict dict;
	dict["cbTimeLeave"] = LuaValue::intValue((int)pCsc->cbTimeLeave);
	StartGameClock(IClientKernel::get()->GetMeChairID(), IDI_FREE, pCsc->cbTimeLeave);

	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameFreeBack");
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

bool BaijialeClientKernelSink::OnGameStart(void* data, word wSize)
{
	if (sizeof(CMD_S_GameStart) != wSize) return false;
	CMD_S_GameStart* pCsc = (CMD_S_GameStart*)data;

	//设置状态
	IClientKernel::get()->SetGameStatus(GAME_SCENE_BET);
	StartGameClock(IClientKernel::get()->GetMeChairID(), IDI_PLACE_JETTON, pCsc->cbTimeLeave);

	//设置变量
	m_wBankerUser = pCsc->wBankerUser;
	m_lBankerScore = pCsc->lBankerScore;
	m_lMeMaxScore = pCsc->lPlayBetScore;
	m_lPlayFreeSocre = pCsc->lPlayFreeSocre;

	s_Locker.lock();
	m_vBet.clear();
	s_Locker.unlock();

	LuaValueDict dict;
	if (pCsc->wBankerUser != INVALID_CHAIR && IClientKernel::get()->GetTableUserItem(pCsc->wBankerUser))
	{
		//玩家坐庄
		dict["isPlayerBanker"] = LuaValue::intValue(0);
		IClientUserItem* pUserItem = IClientKernel::get()->GetTableUserItem(pCsc->wBankerUser);
		dict["szName"] = LuaValue::stringValue(pUserItem->GetNickName());
		dict["nGold"] = LuaValue::intValue(pUserItem->GetUserScore());
	}
	else if (m_bEnableSysBanker)
	{
		//系统坐庄
		dict["isPlayerBanker"] = LuaValue::intValue(1);
	}
	else
	{
		//无人坐庄
		dict["isPlayerBanker"] = LuaValue::intValue(2);
	}

	dict["cbTimeLeave"] = LuaValue::intValue(pCsc->cbTimeLeave);
	dict["wBankerUser"]	= LuaValue::intValue((int)pCsc->wBankerUser);
	dict["lBankerScore"] = LuaValue::intValue((int)pCsc->lBankerScore);
	dict["lPlayBetScore"] = LuaValue::intValue((int)pCsc->lPlayBetScore);
	dict["lPlayFreeSocre"] = LuaValue::intValue((int)pCsc->lPlayFreeSocre);
	dict["nChipRobotCount"] = LuaValue::intValue((int)pCsc->nChipRobotCount);
	
	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameStartBack");
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


bool BaijialeClientKernelSink::OnGamePlaceBet(void* data, word wSize)
{
	if (sizeof(CMD_S_PlaceBet) != wSize) return false;
	CMD_S_PlaceBet* pCsc = (CMD_S_PlaceBet*)data;

	if (pCsc->cbBetArea == AREA_XIAN_TIAN || pCsc->cbBetArea == AREA_ZHUANG_TIAN || pCsc->cbBetArea == AREA_TONG_DUI)
	{
		return true;
	}

	if (IClientKernel::get()->GetMeChairID() != pCsc->wChairID || IClientKernel::get()->IsLookonMode())
	{
		//加注界面
		m_lAllBet[pCsc->cbBetArea] += pCsc->lBetScore;
	}

	if (pCsc->cbAndroidUser)
	{
		s_Locker.lock();
		tagGPBet betInfo;
		betInfo.wChairID = pCsc->wChairID;
		betInfo.cbBetArea = pCsc->cbBetArea;
		betInfo.lBetScore = pCsc->lBetScore;
		m_vBet.push_back(betInfo);
		s_Locker.unlock();
	}
	else
	{
		LuaValueDict dict;
		dict["wChairID"] = LuaValue::intValue((int)pCsc->wChairID);
		dict["cbBetArea"] = LuaValue::intValue((int)pCsc->cbBetArea);
		dict["lBetScore"] = LuaValue::intValue((int)pCsc->lBetScore);
		dict["cbAndroidUser"] = LuaValue::intValue((int)pCsc->cbAndroidUser);

		int ret = 0;
		do
		{
			LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGamePlaceBetBack");
			CC_BREAK_IF(0 == nLuaHandler);
			LuaEngine* pEngine = LuaEngine::getInstance();
			LuaStack* pStack = pEngine->getLuaStack();
			lua_State *tolua_s = pStack->getLuaState();
			lua_settop(tolua_s, 0);
			pStack->pushLuaValueDict(dict);
			ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
		} while (0);
	}
	return true;
}

bool BaijialeClientKernelSink::OnGameCancelBet(void* data, word wSize)
{
	if (sizeof(CMD_S_CancelBet) != wSize) return false;
	CMD_S_CancelBet* pCsc = (CMD_S_CancelBet*)data;

	IClientKernel * kernel = IClientKernel::get();

	for (byte i = 0; i<AREA_MAX; i++)
	{
		if (pCsc->lPlayBet[i] == 0) continue;

		if (pCsc->wChairID == kernel->GetMeChairID() && !kernel->IsLookonMode())
		{
			m_lPlayBet[i] -= pCsc->lPlayBet[i];
		}

		m_lAllBet[i] -= pCsc->lPlayBet[i];
	}

	LuaValueDict dict;
	dict["wChairID"] = LuaValue::intValue((int)pCsc->wChairID);

	LuaValueDict dict0;
	for (size_t i = 0; i < AREA_MAX; i++)
	{
		dict0[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->lPlayBet[i]);
	}
	dict["lPlayBet"] = LuaValue::dictValue(dict0);

	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameCancelBetBack");
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

bool BaijialeClientKernelSink::OnGamePlaceBetFail(void* data, word wSize)
{
	if (sizeof(CMD_S_PlaceBetFail) != wSize) return false;
	CMD_S_PlaceBetFail* pCsc = (CMD_S_PlaceBetFail*)data;

	//效验参数
	byte cbViewIndex = pCsc->lBetArea;
	ASSERT(cbViewIndex < AREA_MAX);
	if (cbViewIndex >= AREA_MAX) return false;

	IClientKernel * kernel = IClientKernel::get();

	//自己判断
	if (kernel->GetMeChairID() == pCsc->wPlaceUser && !kernel->IsLookonMode())
	{
		//设置变量
		m_lPlayBet[cbViewIndex] -= pCsc->lPlaceScore;
		m_lAllBet[cbViewIndex] -= pCsc->lPlaceScore;

		//设置界面
		LuaValueDict dict;
		dict["wPlaceUser"] = LuaValue::intValue((int)pCsc->wPlaceUser);
		dict["lBetArea"] = LuaValue::intValue((int)pCsc->lBetArea);
		dict["lPlaceScore"] = LuaValue::intValue((int)pCsc->lPlaceScore);

		int ret = 0;
		do
		{
			LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGamePlaceBetFailBack");
			CC_BREAK_IF(0 == nLuaHandler);
			LuaEngine* pEngine = LuaEngine::getInstance();
			LuaStack* pStack = pEngine->getLuaStack();
			lua_State *tolua_s = pStack->getLuaState();
			lua_settop(tolua_s, 0);
			pStack->pushLuaValueDict(dict);
			ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
		} while (0);
	}
	return true;
}

bool BaijialeClientKernelSink::OnGameApplyBanker(void* data, word wSize)
{
	if (sizeof(CMD_S_ApplyBanker) != wSize) return false;
	CMD_S_ApplyBanker* pCsc = (CMD_S_ApplyBanker*)data;

	//插入玩家
	if (m_wBankerUser != pCsc->wApplyUser)
	{
		LuaValueDict dict;
		dict["wApplyUser"] = LuaValue::intValue((int)pCsc->wApplyUser);

		IClientUserItem* pUserItem = IClientKernel::get()->GetTableUserItem(pCsc->wApplyUser);
		if (!pUserItem)
			return true;

		dict["szName"] = LuaValue::stringValue(pUserItem->GetNickName() );
		dict["nGold"] = LuaValue::intValue(pUserItem->GetUserScore());

		int ret = 0;
		do
		{
			LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameApplyBankerBack");
			CC_BREAK_IF(0 == nLuaHandler);
			LuaEngine* pEngine = LuaEngine::getInstance();
			LuaStack* pStack = pEngine->getLuaStack();
			lua_State *tolua_s = pStack->getLuaState();
			lua_settop(tolua_s, 0);
			pStack->pushLuaValueDict(dict);
			ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
		} while (0);
	}
	return true;
}

bool BaijialeClientKernelSink::OnGameCancelBanker(void* data, word wSize)
{
	if (sizeof(CMD_S_CancelBanker) != wSize) return false;
	CMD_S_CancelBanker* pCsc = (CMD_S_CancelBanker*)data;

	LuaValueDict dict;
	dict["wCancelUser"] = LuaValue::intValue((int)pCsc->wCancelUser);

	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameCancelBankerBack");
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

bool BaijialeClientKernelSink::OnGameChangeBanker(void* data, word wSize)
{
	if (sizeof(CMD_S_ChangeBanker) != wSize) return false;
	CMD_S_ChangeBanker* pCsc = (CMD_S_ChangeBanker*)data;

	//设置变量
	m_wBankerUser = pCsc->wBankerUser;
	m_lBankerScore = pCsc->lBankerScore;

	LuaValueDict dict;
	dict["wBankerUser"] = LuaValue::intValue((int)pCsc->wBankerUser);
	dict["lBankerScore"] = LuaValue::intValue((int)pCsc->lBankerScore);
	dict["wFaceID"] = LuaValue::intValue((int)pCsc->wFaceID);

	if (pCsc->wBankerUser != INVALID_CHAIR && IClientKernel::get()->GetTableUserItem(pCsc->wBankerUser))
	{
		//玩家坐庄
		dict["isPlayerBanker"] = LuaValue::intValue(0);
		IClientUserItem* pUserItem = IClientKernel::get()->GetTableUserItem(pCsc->wBankerUser);
		dict["szName"] = LuaValue::stringValue(pUserItem->GetNickName());
		dict["nGold"] = LuaValue::intValue(pUserItem->GetUserScore());
	}
	else if (m_bEnableSysBanker)
	{
		//系统坐庄
		dict["isPlayerBanker"] = LuaValue::intValue(1);
	}
	else
	{
		//无人坐庄
		dict["isPlayerBanker"] = LuaValue::intValue(2);
	}

	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameChangeBankerBack");
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

bool BaijialeClientKernelSink::OnGameOver(void* data, word wSize)
{
	if (sizeof(CMD_S_GameEnd) != wSize) return false;
	CMD_S_GameEnd* pCsc = (CMD_S_GameEnd*)data;

	//设置状态
	IClientKernel::get()->SetGameStatus(GAME_SCENE_END);
	StartGameClock(IClientKernel::get()->GetMeChairID(), IDI_DISPATCH_CARD, pCsc->cbTimeLeave);
	
	//扑克信息
	memset(m_cbCardCount, 0, sizeof(m_cbCardCount));
	memset(m_cbTableCardArray, 0, sizeof(m_cbTableCardArray));

	memcpy(m_cbCardCount, pCsc->cbCardCount, sizeof(m_cbCardCount));
	memcpy(m_cbTableCardArray, pCsc->cbTableCardArray, sizeof(m_cbTableCardArray));

	LuaValueDict dict;
	dict["cbTimeLeave"] = LuaValue::intValue((int)pCsc->cbTimeLeave);
	dict["lRevenue"] = LuaValue::intValue((int)pCsc->lRevenue);
	dict["lPlayAllScore"] = LuaValue::intValue((int)pCsc->lPlayAllScore);
	dict["lBankerScore"] = LuaValue::intValue((int)pCsc->lBankerScore);
	dict["lBankerWinScore"] = LuaValue::intValue((int)pCsc->lBankerTotallScore);
	dict["wBankerTime"] = LuaValue::intValue((int)pCsc->nBankerTime);

	if (m_wBankerUser != INVALID_CHAIR)
	{
		IClientUserItem* pUserItem = IClientKernel::get()->GetTableUserItem(m_wBankerUser);
		if (pUserItem)
		{
			dict["wBankerUser"] = LuaValue::intValue(m_wBankerUser);
			dict["szName"] = LuaValue::stringValue(pUserItem->GetNickName());
			dict["nGold"] = LuaValue::intValue(pUserItem->GetUserScore());
		}
	}

	
	LuaValueDict dict0;
	for (size_t i = 0; i < AREA_MAX; i++)
	{
		dict0[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->lPlayScore[i]);
	}
	dict["lPlayScore"] = LuaValue::dictValue(dict0);

	LuaValueDict dict3;
	LuaValueDict dict4;
	for (size_t i = 0; i < 2; i++)
	{
		dict3[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->cbCardCount[i]);

		LuaValueDict dict31;
		for (size_t j = 0; j < 3; j++)
		{
			dict31[StringUtils::format("%d", j + 1).c_str()] = LuaValue::intValue((int)pCsc->cbTableCardArray[i][j]);
		}
		dict4[StringUtils::format("%d", i + 1).c_str()] = LuaValue::dictValue(dict31);
	}
	dict["cbCardCount"] = LuaValue::dictValue(dict3);
	dict["cbTableCardArray"] = LuaValue::dictValue(dict4);

	//计算牌点
	byte cbPlayerCount = m_CardLogic.GetCardListPip(m_cbTableCardArray[INDEX_PLAYER], m_cbCardCount[INDEX_PLAYER]);
	byte cbBankerCount = m_CardLogic.GetCardListPip(m_cbTableCardArray[INDEX_BANKER], m_cbCardCount[INDEX_BANKER]);
	
	dict["cbPlayerCount"] = LuaValue::intValue((int)cbPlayerCount);
	dict["cbBankerCount"] = LuaValue::intValue((int)cbBankerCount);

	//推断玩家
	byte cbWinArea[AREA_MAX] = { FALSE };
	DeduceWinner(cbWinArea);

	LuaValueDict dict8;
	for (size_t i = 0; i < AREA_MAX; i++)
	{
		dict8[StringUtils::format("%d", i + 1).c_str()] = LuaValue::booleanValue(cbWinArea[i]);
	}
	dict["cbWinArea"] = LuaValue::dictValue(dict8);

	//操作类型
	enOperateResult OperateResult = enOperateResult_NULL;
	if (0.001 < pCsc->lPlayAllScore) OperateResult = enOperateResult_Win;
	else if (pCsc->lPlayAllScore < -0.001) OperateResult = enOperateResult_Lost;
	else OperateResult = enOperateResult_NULL;
	dict["nResult"] = LuaValue::intValue((int)OperateResult);

	//推断赢家
	byte cbWinner, cbKingWinner;
	bool bPlayerTwoPair, bBankerTwoPair;
	DeduceWinner(cbWinner, cbKingWinner, bPlayerTwoPair, bBankerTwoPair);
	dict["cbWinner"] = LuaValue::intValue((int)cbWinner);
	dict["cbKingWinner"] = LuaValue::intValue((int)cbKingWinner);
	dict["bPlayerTwoPair"] = LuaValue::booleanValue(bPlayerTwoPair);
	dict["bBankerTwoPair"] = LuaValue::booleanValue(bBankerTwoPair);

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

	return true;
}

bool BaijialeClientKernelSink::OnGameReSortBanker(void* data, word wSize)
{
	if (sizeof(CMD_S_ReSortBanker) != wSize) return false;
	CMD_S_ReSortBanker* pCsc = (CMD_S_ReSortBanker*)data;

	if (IClientKernel::get()->GetGameStatus() != GAME_SCENE_END)
		return true;

	//设置变量
	m_wBankerUser = pCsc->wCurBanker;

	LuaValueDict dict;
	dict["wCurBanker"] = LuaValue::intValue((int)pCsc->wCurBanker);
	dict["wUserCount"] = LuaValue::intValue((int)pCsc->wUserCount);

	LuaValueDict dict1;
	for (size_t i = 0; i < pCsc->wUserCount; i++)
	{
		//排除庄家
		if (pCsc->wCurBanker == pCsc->wUserChairID[i]) continue;

		IClientUserItem* pUserItem = IClientKernel::get()->GetTableUserItem(pCsc->wUserChairID[i]);
		if (!pUserItem)
			continue;

		LuaValueDict dict0;
		dict0["wUserChairID"] = LuaValue::intValue(pCsc->wUserChairID[i]);
		dict0["szName"] = LuaValue::stringValue(pUserItem->GetNickName());
		dict0["nGold"] = LuaValue::intValue(pUserItem->GetUserScore());

		dict1[StringUtils::format("%d", i + 1).c_str()] = LuaValue::dictValue(dict0);
	}
	dict["wUserList"] = LuaValue::dictValue(dict1);

	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameReSortBankerBack");
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

bool BaijialeClientKernelSink::OnGameCommandResult(void* data, word wSize)
{
	if (sizeof(CMD_S_CommandResult) != wSize) return false;
	CMD_S_CommandResult* pCsc = (CMD_S_CommandResult*)data;

	LuaValueDict dict;
	dict["cbAckType"] = LuaValue::intValue((int)pCsc->cbAckType);
	dict["cbResult"] = LuaValue::intValue((int)pCsc->cbResult);

	LuaValueDict dict0;
	for (size_t i = 0; i < 20; i++)
	{
		dict0[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)pCsc->cbExtendData[i]);
	}
	dict["cbExtendData"] = LuaValue::dictValue(dict0);

	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameCommandResultBack");
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

bool BaijialeClientKernelSink::OnGameTipInfo(void* data, word wSize)
{
	if (sizeof(CMD_S_TipInfo) != wSize) return false;
	PACKET_AIDE_DATA(data);
	byte cbTimeLeave = packet.readByte();
	std::string szTipInfo = packet.readString(2 * 256);

	LuaValueDict dict;
	dict["cbTimeLeave"] = LuaValue::intValue(cbTimeLeave);
	dict["szTipInfo"] = LuaValue::stringValue(szTipInfo);

	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameTipInfoBack");
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

bool BaijialeClientKernelSink::OnGameSendRecord(void* data, word wSize)
{
	if (wSize%sizeof(tagServerGameRecord) != 0) return false;

	LuaValueDict dict;
	LuaValueDict dict1;
	//设置记录
	word wRecordCount = wSize / sizeof(tagServerGameRecord);
	for (word wIndex = 0; wIndex<wRecordCount; wIndex++)
	{
		tagServerGameRecord * pServerGameRecord = (((tagServerGameRecord *)data) + wIndex);

		LuaValueDict dict0;
		dict0["cbKingWinner"] = LuaValue::intValue((int)pServerGameRecord->cbKingWinner);
		dict0["bPlayerTwoPair"] = LuaValue::booleanValue(pServerGameRecord->bPlayerTwoPair);
		dict0["bBankerTwoPair"] = LuaValue::booleanValue(pServerGameRecord->bBankerTwoPair);
		dict0["cbPlayerCount"] = LuaValue::intValue((int)pServerGameRecord->cbPlayerCount);
		dict0["cbBankerCount"] = LuaValue::intValue((int)pServerGameRecord->cbBankerCount);

		dict1[StringUtils::format("%d", wIndex + 1).c_str()] = LuaValue::dictValue(dict0);
	}
	dict["RecordData"] = LuaValue::dictValue(dict1);

	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameSendRecordBack");
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

//推断赢家
void BaijialeClientKernelSink::DeduceWinner(byte* pWinArea)
{
	//计算牌点
	byte cbPlayerCount = m_CardLogic.GetCardListPip(m_cbTableCardArray[INDEX_PLAYER], m_cbCardCount[INDEX_PLAYER]);
	byte cbBankerCount = m_CardLogic.GetCardListPip(m_cbTableCardArray[INDEX_BANKER], m_cbCardCount[INDEX_BANKER]);

	//胜利区域--------------------------
	//平
	if (cbPlayerCount == cbBankerCount)
	{
		pWinArea[AREA_PING] = TRUE;

		// 同平点
		if (m_cbCardCount[INDEX_PLAYER] == m_cbCardCount[INDEX_BANKER])
		{
			word wCardIndex = 0;
			for (; wCardIndex < m_cbCardCount[INDEX_PLAYER]; ++wCardIndex)
			{
				byte cbBankerValue = m_CardLogic.GetCardValue(m_cbTableCardArray[INDEX_BANKER][wCardIndex]);
				byte cbPlayerValue = m_CardLogic.GetCardValue(m_cbTableCardArray[INDEX_PLAYER][wCardIndex]);
				if (cbBankerValue != cbPlayerValue) break;
			}

			if (wCardIndex == m_cbCardCount[INDEX_PLAYER])
			{
				pWinArea[AREA_TONG_DUI] = TRUE;
			}
		}
	}
	// 庄
	else if (cbPlayerCount < cbBankerCount)
	{
		pWinArea[AREA_ZHUANG] = TRUE;

		//天王判断
		if (cbBankerCount == 8 || cbBankerCount == 9)
		{
			pWinArea[AREA_ZHUANG_TIAN] = TRUE;
		}
	}
	// 闲
	else
	{
		pWinArea[AREA_XIAN] = TRUE;

		//天王判断
		if (cbPlayerCount == 8 || cbPlayerCount == 9)
		{
			pWinArea[AREA_XIAN_TIAN] = TRUE;
		}
	}


	//对子判断
	if (m_CardLogic.GetCardValue(m_cbTableCardArray[INDEX_PLAYER][0]) == m_CardLogic.GetCardValue(m_cbTableCardArray[INDEX_PLAYER][1]))
	{
		pWinArea[AREA_XIAN_DUI] = TRUE;
	}
	if (m_CardLogic.GetCardValue(m_cbTableCardArray[INDEX_BANKER][0]) == m_CardLogic.GetCardValue(m_cbTableCardArray[INDEX_BANKER][1]))
	{
		pWinArea[AREA_ZHUANG_DUI] = TRUE;
	}
}


//推断赢家
void BaijialeClientKernelSink::DeduceWinner(byte &cbWinner, byte &cbKingWinner, bool &bPlayerTwoPair, bool &bBankerTwoPair)
{
	cbWinner = 0;
	cbKingWinner = 0;

	//计算牌点
	byte cbPlayerCount = m_CardLogic.GetCardListPip(m_cbTableCardArray[INDEX_PLAYER], m_cbCardCount[INDEX_PLAYER]);
	byte cbBankerCount = m_CardLogic.GetCardListPip(m_cbTableCardArray[INDEX_BANKER], m_cbCardCount[INDEX_BANKER]);

	//胜利玩家
	if (cbPlayerCount == cbBankerCount)
	{
		cbWinner = AREA_PING;

		//同点平判断
		bool bAllPointSame = false;
		if (m_cbCardCount[INDEX_PLAYER] == m_cbCardCount[INDEX_BANKER])
		{
			word wCardIndex = 0;
			for (; wCardIndex < m_cbCardCount[INDEX_PLAYER]; ++wCardIndex)
			{
				byte cbBankerValue = m_CardLogic.GetCardValue(m_cbTableCardArray[INDEX_BANKER][wCardIndex]);
				byte cbPlayerValue = m_CardLogic.GetCardValue(m_cbTableCardArray[INDEX_PLAYER][wCardIndex]);
				if (cbBankerValue != cbPlayerValue) break;
			}
			if (wCardIndex == m_cbCardCount[INDEX_PLAYER]) bAllPointSame = true;
		}
		if (bAllPointSame) cbKingWinner = AREA_TONG_DUI;
	}
	else if (cbPlayerCount<cbBankerCount)
	{
		cbWinner = AREA_ZHUANG;

		//天王判断
		if (cbBankerCount == 8 || cbBankerCount == 9) cbKingWinner = AREA_ZHUANG_TIAN;
	}
	else
	{
		cbWinner = AREA_XIAN;

		//天王判断
		if (cbPlayerCount == 8 || cbPlayerCount == 9) cbKingWinner = AREA_XIAN_TIAN;
	}

	//对子判断
	bPlayerTwoPair = false;
	bBankerTwoPair = false;
	if (m_CardLogic.GetCardValue(m_cbTableCardArray[INDEX_PLAYER][0]) == m_CardLogic.GetCardValue(m_cbTableCardArray[INDEX_PLAYER][1]))
		bPlayerTwoPair = true;
	if (m_CardLogic.GetCardValue(m_cbTableCardArray[INDEX_BANKER][0]) == m_CardLogic.GetCardValue(m_cbTableCardArray[INDEX_BANKER][1]))
		bBankerTwoPair = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//用户下注消息
void BaijialeClientKernelSink::placeBet(int cbBetArea, int lBetScore)
{
	PLAZZ_PRINTF("flow->placeBet %d", cbBetArea, lBetScore);

	//设置变量
	m_lAllBet[cbBetArea] += lBetScore;
	m_lPlayBet[cbBetArea] += lBetScore;

	//变量定义
	PACKET_AIDE_SIZE(512);
	packet.writeByte(cbBetArea);
	packet.write8Byte(lBetScore);
	//发送数据
	IClientKernel::get()->SendSocketData(SUB_S_MAIN_MSG, SUB_C_PLACE_JETTON, packet.getBuffer(), packet.getPosition());
}

//申请庄家消息
void BaijialeClientKernelSink::applyBanker()
{
	PLAZZ_PRINTF("flow->ClientKernelSink::applyBanker...");

	//发送数据
	IClientKernel::get()->SendSocketData(SUB_S_MAIN_MSG, SUB_C_APPLY_BANKER, 0, 0);
}

//取消申请消息
void BaijialeClientKernelSink::cancelBanker()
{
	PLAZZ_PRINTF("flow->ClientKernelSink::cancelBanker...");
	if (!IClientKernel::get())
		return;
	//发送数据
	IClientKernel::get()->SendSocketData(SUB_S_MAIN_MSG, SUB_C_CANCEL_BANKER, 0, 0);
}

//管理员命令消息
void BaijialeClientKernelSink::adminCmd(int cbReqType)
{
	//PLAZZ_PRINTF("flow->ClientKernelSink::selectPai %d", nType);
	//IClientKernel::get()->KillGameClock(IDI_SELECT_CARD);
	////变量定义
	//PACKET_AIDE_SIZE(512);
	//packet.writeByte(nType);
	////发送数据
	//IClientKernel::get()->SendSocketData(SUB_S_MAIN_MSG, SUB_C_SELECT, packet.getBuffer(), packet.getPosition());
}

// 最大下注
unsigned int BaijialeClientKernelSink::GetMaxPlayerScore(int cbBetArea)
{
	if (!IClientKernel::get())
		return 0;
	word  wMeChairID = IClientKernel::get()->GetMeChairID();
	if (wMeChairID == INVALID_CHAIR)
		return 0;

	IClientUserItem* pMeUserItem = IClientKernel::get()->GetTableUserItem(wMeChairID);
	if (pMeUserItem == NULL || cbBetArea >= AREA_MAX)
		return 0;

	if (cbBetArea >= AREA_MAX)
		return 0;

	longlong lPlayBet[AREA_MAX];
	longlong lAllBet[AREA_MAX];
	memset(lPlayBet, 0, sizeof(lPlayBet));
	memset(lAllBet, 0, sizeof(lAllBet));
	memcpy(lPlayBet, m_lPlayBet, sizeof(m_lPlayBet));
	memcpy(lAllBet, m_lAllBet, sizeof(lAllBet));
	//已下注额
	longlong lNowBet = 0l;
	for (int nAreaIndex = 0; nAreaIndex < AREA_MAX; ++nAreaIndex)
		lNowBet += m_lPlayBet[nAreaIndex];

	////当前下注
	//for (int nAreaIndex = 0; nAreaIndex < AREA_MAX; ++nAreaIndex ) 
	//{
	//	lNowBet += m_lCurrentScore[nAreaIndex];
	//	lPlayBet[nAreaIndex]+=m_lCurrentScore[nAreaIndex];
	//	lAllBet[nAreaIndex]+=m_lCurrentScore[nAreaIndex];
	//}

	//庄家金币
	longlong lBankerScore = -1;

	//区域倍率
	byte cbMultiple[AREA_MAX] =
	{
		MULTIPLE_XIAN,
		MULTIPLE_PING,
		MULTIPLE_ZHUANG,
		MULTIPLE_XIAN_TIAN,
		MULTIPLE_ZHUANG_TIAN,
		MULTIPLE_TONG_DIAN,
		MULTIPLE_XIAN_PING,
		MULTIPLE_ZHUANG_PING
	};

	//区域输赢
	byte cbArae[4][4] =
	{
		{ AREA_XIAN_DUI, 255, AREA_MAX, AREA_MAX },
		{ AREA_ZHUANG_DUI, 255, AREA_MAX, AREA_MAX },
		{ AREA_XIAN, AREA_PING, AREA_ZHUANG, AREA_MAX },
		{ AREA_XIAN_TIAN, AREA_TONG_DUI, AREA_ZHUANG_TIAN, 255 }
	};
	//筹码设定
	for (int nTopL = 0; nTopL < 4; ++nTopL)
	{
		if (cbArae[0][nTopL] == AREA_MAX)
			continue;

		for (int nTopR = 0; nTopR < 4; ++nTopR)
		{
			if (cbArae[1][nTopR] == AREA_MAX)
				continue;

			for (int nCentral = 0; nCentral < 4; ++nCentral)
			{
				if (cbArae[2][nCentral] == AREA_MAX)
					continue;

				for (int nBottom = 0; nBottom < 4; ++nBottom)
				{
					if (cbArae[3][nBottom] == AREA_MAX)
						continue;

					byte cbWinArea[AREA_MAX] = { FALSE };

					//指定获胜区域
					if (cbArae[0][nTopL] != 255 && cbArae[0][nTopL] != AREA_MAX)
						cbWinArea[cbArae[0][nTopL]] = TRUE;

					if (cbArae[1][nTopR] != 255 && cbArae[1][nTopR] != AREA_MAX)
						cbWinArea[cbArae[1][nTopR]] = TRUE;

					if (cbArae[2][nCentral] != 255 && cbArae[2][nCentral] != AREA_MAX)
						cbWinArea[cbArae[2][nCentral]] = TRUE;

					if (cbArae[3][nBottom] != 255 && cbArae[3][nBottom] != AREA_MAX)
						cbWinArea[cbArae[3][nBottom]] = TRUE;

					//选择区域为玩家胜利，同等级的其他的区域为玩家输。以得出最大下注值
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 4; j++)
						{
							if (cbArae[i][j] == cbBetArea)
							{
								for (int n = 0; n < 4; ++n)
								{
									if (cbArae[i][n] != 255 && cbArae[i][n] != AREA_MAX)
									{
										cbWinArea[cbArae[i][n]] = FALSE;
									}
								}
								cbWinArea[cbArae[i][j]] = TRUE;
							}
						}
					}

					longlong lScore = m_lBankerScore;
					for (int nAreaIndex = 0; nAreaIndex < AREA_MAX; ++nAreaIndex)
					{
						if (cbWinArea[nAreaIndex] == TRUE)
						{
							lScore -= lAllBet[nAreaIndex] * (cbMultiple[nAreaIndex] - 1);
						}
						else if (cbWinArea[AREA_PING] == TRUE && (nAreaIndex == AREA_XIAN || nAreaIndex == AREA_ZHUANG))
						{

						}
						else
						{
							lScore += lAllBet[nAreaIndex];
						}
					}
					if (lBankerScore == -1)
						lBankerScore = lScore;
					else
						lBankerScore = min(lBankerScore, lScore);
				}
			}
		}
	}

	//最大下注
	longlong lMaxBet = 0L;

	//最大下注
	lMaxBet = min(m_lMeMaxScore - lNowBet, m_lAreaLimitScore - lPlayBet[cbBetArea]);

	lMaxBet = min(lMaxBet, m_lAreaLimitScore - lAllBet[cbBetArea]);

	lMaxBet = min(lMaxBet, lBankerScore / (cbMultiple[cbBetArea] - 1));

	//非零限制
	//ASSERT(lMaxBet >= 0);
	lMaxBet = max(lMaxBet, (longlong)0);

	return lMaxBet;
}

//获取总下注
unsigned int BaijialeClientKernelSink::GetAreaTotalScore(int cbBetArea)
{
	//效验参数
	ASSERT(cbBetArea < AREA_MAX);
	if (cbBetArea >= AREA_MAX) return 0;

	return m_lAllBet[cbBetArea];
}

//获取自己总下注
unsigned int BaijialeClientKernelSink::GetAreaPlayerScore(int cbBetArea)
{
	//效验参数
	ASSERT(cbBetArea < AREA_MAX);
	if (cbBetArea >= AREA_MAX) return 0;

	return m_lPlayBet[cbBetArea];
}

//获取牌点数
int BaijialeClientKernelSink::GetCardPip(int nCardID)
{
	return (int)m_CardLogic.GetCardPip(nCardID);
}

//
void BaijialeClientKernelSink::getBet()
{
	s_Locker.lock();
	if (!m_vBet.empty() )
	{
		std::vector<tagGPBet>::iterator iter;
		for (iter = m_vBet.begin(); iter != m_vBet.end(); iter++)
		{
			LuaValueDict dict;
			dict["wChairID"] = LuaValue::intValue((int)iter->wChairID);
			dict["cbBetArea"] = LuaValue::intValue((int)iter->cbBetArea);
			dict["lBetScore"] = LuaValue::intValue((int)iter->lBetScore);

			int ret = 0;
			do
			{
				LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGamePlaceBetBack");
				CC_BREAK_IF(0 == nLuaHandler);
				LuaEngine* pEngine = LuaEngine::getInstance();
				LuaStack* pStack = pEngine->getLuaStack();
				lua_State *tolua_s = pStack->getLuaState();
				lua_settop(tolua_s, 0);
				pStack->pushLuaValueDict(dict);
				ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
			} while (0);
			m_vBet.erase(iter);
			break;
		}
	}
	s_Locker.unlock();
}