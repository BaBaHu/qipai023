#include "ClientKernelSink.h"
#include "MTNotification.h"
#include "MECallBackListenerHelper.h"
#include "../utils/Timer.h"
#include "cocos2d.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "../kernel/game/CClientKernel.h"
#include "TwoHZBClientKernelSink.h"
#include "FourHZBClientKernelSink.h"
#include "FourMJClientKernelSink.h"
#include "BaijialeClientKernelSink.h"
#include "FourXZMJClientKernelSink.h"
#include "MELog.h"
#include "../df/DynamicPack.h"
#include "SimpleAudioEngine.h"

#define INFO_MAX  4
#define INFO_MAX_2  2
USING_NS_CC;
using namespace rapidjson;
using namespace CocosDenshion;

ClientKernelSink* ClientKernelSink::s_Instance = NULL;

//构造函数
ClientKernelSink::ClientKernelSink()
{
	szGlobalMessage = "";
	zeromemory(&mCustomTableInfo, sizeof(mCustomTableInfo));
	m_bEnableTimer = true;
	YvVoiceManager::GetInstance()->setUploadListern(this);
	YvVoiceManager::GetInstance()->setVoicePlaySink(this);
}

//析构函数
ClientKernelSink::~ClientKernelSink()
{
}

ClientKernelSink* ClientKernelSink::GetInstance()
{
	if (s_Instance == NULL)
	{
		int nKind = DF::shared()->GetGameKindID();
		if (nKind == 351)
		{
			s_Instance = new TwoHZBClientKernelSink();
		}
		else if (nKind == 350)
		{
			s_Instance = new FourHZBClientKernelSink();
		}
		else if (nKind == 301)
		{
			s_Instance = new FourMJClientKernelSink();
		}
		else if (nKind == 302)
		{
			s_Instance = new FourXZMJClientKernelSink();
		}
		else if (nKind == 122)
		{

			s_Instance = new BaijialeClientKernelSink();
		}
	}
	return s_Instance;
}

void ClientKernelSink::Release()
{
	CC_SAFE_DELETE(s_Instance);
}

//控制接口
//启动游戏场景
bool ClientKernelSink::SetupGameClient()
{
	PLAZZ_PRINTF(("flow->ClientKernelSink::SetupGameClient\n"));
	m_bRunning = true;
	//TODO
	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onSitDownSuccessBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushInt(DF::shared()->GetGameKindID());
		ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
	} while (0);
	return false;
}

//重置游戏
void ClientKernelSink::ResetGameClient()
{
	IClientKernel::get()->KillGameClock(IDI_START_GAME);
}

//关闭游戏
void ClientKernelSink::CloseGameClient()
{
	m_bRunning = false;
	//删除定时器
	IClientKernel::get()->KillGameClock(IDI_START_GAME);
}


//////////////////////////////////////////////////////////////////////////
//框架事件

//系统滚动消息
bool ClientKernelSink::OnGFTableMessage(const char* szMessage)
{
	G_NOTIFY("NOTICE_MSG", MTData::create(0, 0, 0, szMessage));
	return true;
}


//全局消息
bool ClientKernelSink::OnGFGlobalMessage(const char* szMessage)
{
	szGlobalMessage = szMessage;
	//TODO
	return true;
}

//公告消息
bool ClientKernelSink::OnGFNoticeMessage(const char* szMessage)
{
	//TODO
	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onNoticeMessageBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushString(szMessage);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
	} while (0);
	return true;
}

//获取系统消息
std::string ClientKernelSink::GetGlobalMessage()
{
	return szGlobalMessage;
}

//等待提示
bool ClientKernelSink::OnGFWaitTips(bool bWait)
{
	return true;
}

//比赛信息
bool ClientKernelSink::OnGFMatchInfo(tagMatchInfo* pMatchInfo)
{
	return true;
}

//比赛等待提示
bool ClientKernelSink::OnGFMatchWaitTips(tagMatchWaitTip* pMatchWaitTip)
{
	return true;
}

//比赛结果
bool ClientKernelSink::OnGFMatchResult(tagMatchResult* pMatchResult)
{
	return true;
}

//房卡结果
bool ClientKernelSink::OnGFCustomRoomResult(void* data, int dataSize)
{
	PACKET_AIDE_DATA(data);

	LuaValueDict dict;
	word wCount = packet.read2Byte();

	dword wTableOwner = packet.read4Byte();
	dict["wTableOwner"] = LuaValue::intValue(wTableOwner);

	std::string str = packet.readString(256);
	dict["szMessage"] = LuaValue::stringValue(str.c_str() );

	LuaValueDict dict1;
	LuaValueDict dict2;
	LuaValueDict dict3;
	LuaValueDict dict4;
	for (word i = 0; i < 4; ++i)
	{
		dword dwUserID = packet.read4Byte();
		if (i >= wCount)
			continue;
		dict1[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)dwUserID);
	}

	for (word i = 0; i < 4; ++i)
	{
		std::string str = packet.readString(LEN_NICKNAME);
		if (i >= wCount)
			continue;
		dict4[StringUtils::format("%d", i + 1).c_str()] = LuaValue::stringValue(str.c_str() );
	}

	for (word i = 0; i < 4; ++i)
	{
		uint32 lUserScore = packet.read8Byte();
		if (i >= wCount)
			continue;
		dict2[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)lUserScore);
	}

	for (word i = 0; i < 4; ++i)
	{
		dword dwUserFace = packet.read4Byte();
		if (i >= wCount)
			continue;
		dict3[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)dwUserFace);
	}

	LuaValueDict dict5;
	for (word i = 0; i < 4; ++i)
	{
		dword dwZMCount = packet.read4Byte();
		dword dwDPCount = packet.read4Byte();
		dword dwMGCount = packet.read4Byte();
		dword dwAGCount = packet.read4Byte();
		dword dwJPCount = packet.read4Byte();
		dword dwCJCount = packet.read4Byte();
		if (i >= wCount)
			continue;
		LuaValueDict dict51;
		dict51["dwZMCount"] = LuaValue::intValue((int)dwZMCount);
		dict51["dwDPCount"] = LuaValue::intValue((int)dwDPCount);
		dict51["dwMGCount"] = LuaValue::intValue((int)dwMGCount);
		dict51["dwAGCount"] = LuaValue::intValue((int)dwAGCount);
		dict51["dwJPCount"] = LuaValue::intValue((int)dwJPCount);
		dict51["dwCJCount"] = LuaValue::intValue((int)dwCJCount);

		dict5[StringUtils::format("%d", i + 1).c_str()] = LuaValue::dictValue(dict51);
	}

	dict["dwUserID"] = LuaValue::dictValue(dict1);
	dict["lUserScore"] = LuaValue::dictValue(dict2);
	dict["dwUserFace"] = LuaValue::dictValue(dict3);
	dict["szNick"] = LuaValue::dictValue(dict4);
	dict["dwDataCount"] = LuaValue::dictValue(dict5);

	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameCustomResultBack");
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

//语音聊天	
bool  ClientKernelSink::OnGFTableVoiceChat(void* data, int dataSize)
{
	PACKET_AIDE_DATA(data);
	byte cbChatType = packet.readByte();
	dword dwSendChairID = packet.read4Byte();
	LuaValueDict dict;
	dict["cbChatType"] = LuaValue::intValue(cbChatType);
	dict["dwSendChairID"] = LuaValue::intValue(dwSendChairID);

	dword dwChair = IClientKernel::get()->GetMeChairID();
	if (dwChair == dwSendChairID)
		return true;

	if (cbChatType == en_ChatType_Voice)
	{
		std::string url = packet.readString(128);
		dict["url"] = LuaValue::stringValue(url.c_str());
	}
	else if (cbChatType == en_ChatType_VoiceText)
	{
		byte idx = packet.readByte();
		dict["idx"] = LuaValue::intValue(idx);

		byte sex = packet.readByte();
		dict["sex"] = LuaValue::intValue(sex);
	}

	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameVoiceStartPlayBack");
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

//////////////////////////////////////////////////////////////////////////
//游戏事件

//旁观消息
bool ClientKernelSink::OnEventLookonMode(void* data, int dataSize)
{
	return true;
}

//场景消息
bool ClientKernelSink::OnEventSceneMessage(byte cbGameStatus, bool bLookonUser, void* data, int dataSize)
{
	return false;
}

//游戏消息
bool ClientKernelSink::OnEventGameMessage(int sub, void* data, int wSize)
{
	if (!m_bRunning)
		return true;

	////错误断言
	//ASSERT(false);

	return true;
}

//管理消息
bool  ClientKernelSink::OnEventManageMessage(int sub, void* data, int dataSize)
{
	MELOG(MELOG_INFO, "ClientKernelSink OnEventManageMessage msg code: %d\n", sub);
	if (!m_bRunning)
		return true;

	switch (sub)
	{
	case SUB_GR_DISMISSVOTENotiy:
		return OnGameDismissVoteNotify(data, dataSize);
	case SUB_GR_DISMISSVOTERes:
		return OnGameDismissVoteResult(data, dataSize);
	}

	////错误断言
	//ASSERT(false);

	return true;
}

bool ClientKernelSink::OnGameDismissVoteNotify(void* data, word wSize)
{
	PACKET_AIDE_DATA(data);

	LuaValueDict dict;
	dword dwRequesterID = packet.read4Byte();
	dict["dwRequesterID"] = LuaValue::intValue((int)dwRequesterID);
	bool bUpdate = packet.readByte();
	dict["bUpdate"] = LuaValue::booleanValue(bUpdate);

	dword wCount = 0;
	int nKind = DF::shared()->GetGameKindID();
	if (nKind == 351)
	{
		wCount = 2;
	}
	else if (nKind == 350)
	{
		wCount = 4;
	}
	else if (nKind == 301)
	{
		wCount = 4;
	}
	else if (nKind == 302)
	{
		wCount = 4;
	}

	LuaValueDict dict1;
	for (word i = 0; i < 6; ++i)
	{
		byte cbStatus = packet.readByte();
		if (i >= wCount)
			continue;
		dict1[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)cbStatus);
	}
	dict["cbStatus"] = LuaValue::dictValue(dict1);

	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameDismissVoteNotifyBack");
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

bool ClientKernelSink::OnGameDismissVoteResult(void* data, word	wSize)
{
	PACKET_AIDE_DATA(data);

	LuaValueDict dict;
	byte cbResult = packet.readByte();
	dict["cbResult"] = LuaValue::intValue((int)cbResult);

	std::string str = packet.readString(128);
	dict["szDescribe"] = LuaValue::stringValue(str.c_str() );

	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameDismissVoteResultBack");
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

//////////////////////////////////////////////////////////////////////////
//时钟事件
//用户时钟
void ClientKernelSink::OnEventUserClock(word wChairID, word wUserClock)
{
	//PLAZZ_PRINTF("ClientKernelSink::OnEventUserClock wChairID = %d, wUserClock = %d \n", wChairID, wUserClock);
	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onUserClockBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushInt(wChairID);
		pStack->pushInt(wUserClock);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 2);
	} while (0);
}

//时钟删除
bool ClientKernelSink::OnEventGameClockKill(word wChairID)
{
	MELOG(MELOG_INFO, "ClientKernelSink::OnEventGameClockKill wChairID = %d \n", wChairID);
	return true;
}

//时钟信息
bool ClientKernelSink::OnEventGameClockInfo(word wChairID, uint nElapse, word wClockID)
{
	IClientKernel * kernel = IClientKernel::get();

	switch (wClockID)
	{
	case IDI_START_GAME:	//游戏开始
		{
			//离开游戏
			if (nElapse==0 && (!kernel->IsLookonMode()) && (wChairID==kernel->GetMeChairID())) 
			{
				int ret = 0;
				do
				{
					LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameStateErrorBack");
					CC_BREAK_IF(0 == nLuaHandler);
					LuaEngine* pEngine = LuaEngine::getInstance();
					LuaStack* pStack = pEngine->getLuaStack();
					lua_State *tolua_s = pStack->getLuaState();
					lua_settop(tolua_s, 0);
					ret = pStack->executeFunctionByHandler(nLuaHandler, 0);
				} while (0);
				return true;
			}

			//超时警告
			if ((nElapse<=5)&&(wChairID== kernel->GetMeChairID())&&(!kernel->IsLookonMode()))
			{
				
			}
			return true;
		}
	case IDI_OUT_CARD:		//出牌定时器
		{
			if (nElapse == 0 && (!kernel->IsLookonMode()) && (wChairID == kernel->GetMeChairID()))
			{
				int ret = 0;
				do
				{
					LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameChuPaiTimeOutBack");
					CC_BREAK_IF(0 == nLuaHandler);
					LuaEngine* pEngine = LuaEngine::getInstance();
					LuaStack* pStack = pEngine->getLuaStack();
					lua_State *tolua_s = pStack->getLuaState();
					lua_settop(tolua_s, 0);
					ret = pStack->executeFunctionByHandler(nLuaHandler, 0);
				} while (0);
				return true;
			}
			return true;
		}
	case IDI_OPERATE_CARD:	//操作定时器
		{
			if (nElapse == 0 && (!kernel->IsLookonMode()) )
			{
				int ret = 0;
				do
				{
					LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameOperateNotifyTimeOutBack");
					CC_BREAK_IF(0 == nLuaHandler);
					LuaEngine* pEngine = LuaEngine::getInstance();
					LuaStack* pStack = pEngine->getLuaStack();
					lua_State *tolua_s = pStack->getLuaState();
					lua_settop(tolua_s, 0);
					ret = pStack->executeFunctionByHandler(nLuaHandler, 0);
				} while (0);
				return true;
			}
			return true;
		}
	case IDI_SELECT_CARD:	//选牌定时器
	{
		if (nElapse == 0 && (!kernel->IsLookonMode()) && (wChairID == kernel->GetMeChairID()))
		{
			int ret = 0;
			do
			{
				LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameSelectPaiTimeOutBack");
				CC_BREAK_IF(0 == nLuaHandler);
				LuaEngine* pEngine = LuaEngine::getInstance();
				LuaStack* pStack = pEngine->getLuaStack();
				lua_State *tolua_s = pStack->getLuaState();
				lua_settop(tolua_s, 0);
				ret = pStack->executeFunctionByHandler(nLuaHandler, 0);
			} while (0);
			return true;
		}
		return true;
	}
	case IDI_CHANGE_CARD:
	{
		if (nElapse == 0 && (!kernel->IsLookonMode()) && (wChairID == kernel->GetMeChairID()))
		{
			int ret = 0;
			do
			{
				LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameChangeCardTimeOutBack");
				CC_BREAK_IF(0 == nLuaHandler);
				LuaEngine* pEngine = LuaEngine::getInstance();
				LuaStack* pStack = pEngine->getLuaStack();
				lua_State *tolua_s = pStack->getLuaState();
				lua_settop(tolua_s, 0);
				ret = pStack->executeFunctionByHandler(nLuaHandler, 0);
			} while (0);
			return true;
		}
		return true;
	}
	case IDI_WAIT_CARD:		//等待定时器
		{
			return true;
		}
	case IDI_FREE:
	case IDI_PLACE_JETTON:
	case IDI_DISPATCH_CARD:
	case IDI_PLACE_JETTON_BUFFER:
		{
			return true;
		}
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
//用户事件

//用户进入
void ClientKernelSink::OnEventUserEnter(IClientUserItem * pIClientUserItem, bool bLookonUser)
{
	if(!bLookonUser)
	{ 
		word wChairID = pIClientUserItem->GetChairID();
		//TODO
		IClientKernel* kernel = IClientKernel::get();
		//if (wChairID != kernel->GetMeChairID())
		{
			LuaValueDict dict;
			dict["sex"] = LuaValue::intValue((int)pIClientUserItem->GetGender() );
			dict["ficeid"] = LuaValue::intValue((int)pIClientUserItem->GetFaceID());
			dict["nickName"] = LuaValue::stringValue(pIClientUserItem->GetNickName() );
			dict["gold"] = LuaValue::intValue((int)pIClientUserItem->GetUserScore());
			dict["status"] = LuaValue::intValue((int)pIClientUserItem->GetUserStatus());
			dict["chair"] = LuaValue::intValue((int)pIClientUserItem->GetChairID());
			dict["type"] = LuaValue::intValue((int)pIClientUserItem->GetUserType());
			dict["url"] = LuaValue::stringValue(pIClientUserItem->GetIconUrl());
			dict["isEnter"] = LuaValue::booleanValue(true);
			int ret = 0;
			do
			{
				LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameUserBack");
				CC_BREAK_IF(0 == nLuaHandler);
				LuaEngine* pEngine = LuaEngine::getInstance();
				LuaStack* pStack = pEngine->getLuaStack();
				lua_State *tolua_s = pStack->getLuaState();
				lua_settop(tolua_s, 0);
				pStack->pushLuaValueDict(dict);
				ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
			} while (0);
		}
	}
}

//用户离开
void ClientKernelSink::OnEventUserLeave(IClientUserItem * pIClientUserItem, bool bLookonUser)
{
	if(!bLookonUser)
	{
		word wChairID = pIClientUserItem->GetChairID();
		//TODO
		IClientKernel* kernel = IClientKernel::get();
		//if (wChairID != kernel->GetMeChairID())
		{
			LuaValueDict dict;
			dict["status"] = LuaValue::intValue((int)pIClientUserItem->GetUserStatus());
			dict["chair"] = LuaValue::intValue((int)pIClientUserItem->GetChairID());
			dict["isEnter"] = LuaValue::booleanValue(false);
			int ret = 0;
			do
			{
				LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameUserBack");
				CC_BREAK_IF(0 == nLuaHandler);
				LuaEngine* pEngine = LuaEngine::getInstance();
				LuaStack* pStack = pEngine->getLuaStack();
				lua_State *tolua_s = pStack->getLuaState();
				lua_settop(tolua_s, 0);
				pStack->pushLuaValueDict(dict);
				ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
			} while (0);
		}
	}
}

//用户积分
void ClientKernelSink::OnEventUserScore(IClientUserItem * pIClientUserItem, bool bLookonUser)
{
	int nKind = DF::shared()->GetGameKindID();
	if (nKind == 122)
	{
		return;
	}

	if (!bLookonUser && m_bRunning)
	{
		word wChairID = pIClientUserItem->GetChairID();
		//TODO
		IClientKernel* kernel = IClientKernel::get();
		//if (wChairID != kernel->GetMeChairID())
		{
			LuaValueDict dict;
			dict["gold"] = LuaValue::intValue((int)pIClientUserItem->GetUserScore());
			dict["chair"] = LuaValue::intValue((int)pIClientUserItem->GetChairID());
			int ret = 0;
			do
			{
				LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameUserScoreBack");
				CC_BREAK_IF(0 == nLuaHandler);
				LuaEngine* pEngine = LuaEngine::getInstance();
				LuaStack* pStack = pEngine->getLuaStack();
				lua_State *tolua_s = pStack->getLuaState();
				lua_settop(tolua_s, 0);
				pStack->pushLuaValueDict(dict);
				ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
			} while (0);
		}
	}
}

//用户状态
void ClientKernelSink::OnEventUserStatus(IClientUserItem * pIClientUserItem, bool bLookonUser)
{
	int nKind = DF::shared()->GetGameKindID();
	if (nKind == 122)
	{
		return;
	}

	if (!bLookonUser)
	{
		word wChairID = pIClientUserItem->GetChairID();
		//TODO
		IClientKernel* kernel = IClientKernel::get();
		//if (wChairID != kernel->GetMeChairID())
		{
			LuaValueDict dict;
			dict["status"] = LuaValue::intValue((int)pIClientUserItem->GetUserStatus());
			dict["chair"] = LuaValue::intValue((int)pIClientUserItem->GetChairID());
			int ret = 0;
			do
			{
				LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameUserStatusBack");
				CC_BREAK_IF(0 == nLuaHandler);
				LuaEngine* pEngine = LuaEngine::getInstance();
				LuaStack* pStack = pEngine->getLuaStack();
				lua_State *tolua_s = pStack->getLuaState();
				lua_settop(tolua_s, 0);
				pStack->pushLuaValueDict(dict);
				ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
			} while (0);
		}
	}
		
}

//用户属性
void ClientKernelSink::OnEventUserAttrib(IClientUserItem * pIClientUserItem, bool bLookonUser)
{
}

//用户头像
void ClientKernelSink::OnEventCustomFace(IClientUserItem * pIClientUserItem, bool bLookonUser)
{
}

//用户自定义桌子
void ClientKernelSink::OnEventCustomTable(IClientUserItem * pIClientUserItem, bool bLookonUser)
{
	if (!bLookonUser)
	{
		//获取用户
		tagCustomTableInfo * pCustomTableInfo = pIClientUserItem->GetCustomTableInfo();
		memcpy(&mCustomTableInfo, pCustomTableInfo, sizeof(tagCustomTableInfo));
		
		UpdateCustomTableInfo();
	}
}

void ClientKernelSink::UpdateCustomTableInfo()
{

	if (mCustomTableInfo.dwCreateUser == 0 || mCustomTableInfo.cbExData <= 0)
		return;

	LuaValueDict dict;
	dict["cbCurRound"] = LuaValue::intValue((int)mCustomTableInfo.cbCurRound);
	dict["cbMaxRound"] = LuaValue::intValue((int)mCustomTableInfo.cbMaxRound);
	dict["dwCreateFlag"] = LuaValue::intValue((int)mCustomTableInfo.dwCreateFlag);
	dict["dwCreateUser"] = LuaValue::intValue((int)mCustomTableInfo.dwCreateUser);
	LuaValueDict dict1;
	for (size_t i = 0; i < mCustomTableInfo.wChairCount; i++)
	{
		dict1[StringUtils::format("%d", i + 1).c_str()] = LuaValue::intValue((int)mCustomTableInfo.lChairScore[i]);
	}
	dict["lChairScore"] = LuaValue::dictValue(dict1);

	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameCustomTableBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushLuaValueDict(dict);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
	} while (0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

int ClientKernelSink::getUserTypeByChair(int nChair)
{
	IClientKernel* kernel = IClientKernel::get();
	if (kernel)
	{
		IClientUserItem* pIClientUserItem = kernel->GetTableUserItem(nChair);
		if (pIClientUserItem != NULL){
			return pIClientUserItem->GetUserType();
		}
	}
	return 0;
}

const char* ClientKernelSink::getUserIconUrlByChair(int nChair)
{
	IClientKernel* kernel = IClientKernel::get();
	if (kernel)
	{
		IClientUserItem* pIClientUserItem = kernel->GetTableUserItem(nChair);
		if (pIClientUserItem != NULL){
			return pIClientUserItem->GetIconUrl();
		}
	}
	return "";
}

const char*  ClientKernelSink::getUserNameByID(int nChair)
{
	IClientKernel* kernel = IClientKernel::get();
	if (kernel)
	{
		IClientUserItem* pIClientUserItem = kernel->GetTableUserItem(nChair);
		if (pIClientUserItem != NULL){
			return pIClientUserItem->GetNickName();
		}
	}
	return "";
}

void ClientKernelSink::startTalk()
{
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	YvVoiceManager::GetInstance()->StartRecord();
}

void ClientKernelSink::endTalk(bool bSend)
{
	YvVoiceManager::GetInstance()->StopRecord();
}

void ClientKernelSink::onUpLoadFileListern(YVSDK::UpLoadFileRespond* resp)
{
	cocos2d::log("ClientKernelSink::onUpLoadFileListern ........................");
	std::string url;
	url.clear();
	url.append(resp->fileurl);

	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	//发送给其他人
	PACKET_AIDE_SIZE(512);
	packet.writeByte(en_ChatType_Voice);
	packet.write4Byte(IClientKernel::get()->GetMeChairID());
	packet.writeString(url.c_str(), 128);
	//发送数据
	IClientKernel::get()->SendSocketData(MDM_GF_FRAME, SUB_GR_TABLE_TALK, packet.getBuffer(), packet.getPosition());
}

void ClientKernelSink::playTalk(int nChair, const char* url)
{
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	YvVoiceManager::GetInstance()->PlayRecord(url);
}

void ClientKernelSink::onPlayComplete()
{
	cocos2d::log("ClientKernelSink::onPlayComplete ........................");
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameVoicePlayFinishBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		ret = pStack->executeFunctionByHandler(nLuaHandler,0);
	} while (0);
}

void ClientKernelSink::playChat(int nChair, int nIdx, int nSex)
{
	//发送给其他人
	PACKET_AIDE_SIZE(512);
	packet.writeByte(en_ChatType_VoiceText);
	packet.write4Byte(IClientKernel::get()->GetMeChairID());
	packet.writeByte(nIdx);
	packet.writeByte(nSex);
	//发送数据
	IClientKernel::get()->SendSocketData(MDM_GF_FRAME, SUB_GR_TABLE_TALK, packet.getBuffer(), packet.getPosition());
}

void  ClientKernelSink::setGameOffline()
{
	m_bRunning = false;
}

//发送进入场景消息
void ClientKernelSink::enterGame()
{
	IClientKernel::get()->SendGameOption();
}

//发送离开场景消息
void ClientKernelSink::leaveGame()
{
	IClientKernel::get()->Intermit("", true);
	Release();
}

//发送准备消息
void ClientKernelSink::ready()
{
	IClientKernel::get()->SendUserReady(0, 0);
	//删除定时器
	IClientKernel::get()->KillGameClock(IDI_START_GAME);
}

//设置时钟
void ClientKernelSink::StartGameClock(int wChairID, int nTimerID, int nTimer)
{
	if (m_bEnableTimer)
	{
		IClientKernel::get()->SetGameClock(wChairID, nTimerID, nTimer);
	}
}

//设置时钟
void ClientKernelSink::setGameClock(int wChairID, int nTimerID, int nTimer)
{
	//删除定时器
	IClientKernel::get()->KillGameClock(IDI_OUT_CARD);
	IClientKernel::get()->KillGameClock(IDI_WAIT_CARD);
	IClientKernel::get()->KillGameClock(IDI_OPERATE_CARD);
	StartGameClock(wChairID, nTimerID, nTimer);
}

//清除时钟
void ClientKernelSink::clearGameClock(int wChairID)
{
	IClientKernel::get()->KillGameClock(IDI_OUT_CARD);
	IClientKernel::get()->KillGameClock(IDI_WAIT_CARD);
	IClientKernel::get()->KillGameClock(IDI_OPERATE_CARD);
	IClientKernel::get()->KillGameClock(IDI_SELECT_CARD);
	IClientKernel::get()->KillGameClock(IDI_CHANGE_CARD);
	
}

//是否可启动时钟
void  ClientKernelSink::setEnableGameClock(bool bEnable)
{
	m_bEnableTimer = bEnable;
}

//获取桌子玩家最小的金币数量
int ClientKernelSink::getTableMinGold()
{
	int nGold = -1;
	IClientKernel* kernel = IClientKernel::get();
	for (word i = 0; i<DF::shared()->GetGamePlayer(); i++){
		IClientUserItem* pIClientUserItem = kernel->GetTableUserItem(i);
		if (pIClientUserItem != NULL){
			int iGold = pIClientUserItem->GetUserScore();
			if (nGold == -1)
			{
				nGold = iGold;
			}
			else if (iGold <= nGold)
			{
				nGold = iGold;
			}
		}
	}
	return nGold;
}