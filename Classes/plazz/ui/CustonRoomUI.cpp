#include "CustonRoomUI.h"
#include "MTNotification.h"
#include "MECallBackListenerHelper.h"
#include "MELog.h"
USING_NS_CC;

CustonRoomUI::CustonRoomUI()
: mCustomRoomMission(DEFAULT_IP_ADDRESS, DEFAULT_PORT)
{
	mCustomRoomMission.setMissionSink(this);
}

CustonRoomUI::~CustonRoomUI()
{
	mCustomRoomMission.setMissionSink(0);
}

CustonRoomUI* CustonRoomUI::create(std::string strIp, int iPort)
{
	CustonRoomUI *pRet = new CustonRoomUI();
	if (pRet && pRet->init(strIp, iPort))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CustonRoomUI::init(std::string strIp, int iPort)
{
	mCustomRoomMission.setUrl(strIp, iPort);
	return true;
}

void CustonRoomUI::createRoom(int iKindID, int cbRound, int cbWF)
{
	MELOG(MELOG_INFO, "createRoom  %d, %d, %d\n", iKindID, cbRound, cbWF);
	tagGPCreateCustomRoom createCustomRoom;
	createCustomRoom.cbRound = cbRound;
	createCustomRoom.wKindID = iKindID;
	createCustomRoom.llBaseScore = cbWF;

	mCustomRoomMission.createCustomRoom(createCustomRoom);
}

void CustonRoomUI::enterRoom(int iRoomID)
{
	MELOG(MELOG_INFO, "enterRoom  %d\n", iRoomID);
	//获取对象
	ASSERT(CServerListData::shared() != 0);
	CServerListData * pServerListData = CServerListData::shared();

	char sz7[7] = { 0 };
	sprintf(sz7, "%06d", iRoomID);
	DF::shared()->decodeRoomID(sz7);
	dword dwRoomVerifyID = atoi(sz7);
	//word wServerID = ServerIDByUUID(dwRoomVerifyID);
	//CGameServerItem* pServer = pServerListData->searchCustomServer(wServerID);
	//if (NULL != pServer)
	//{
	//	//直接进入
	//	onGPEnterCustomRoomSuccess(dwRoomVerifyID, pServer->m_GameServer);
	//}
	//else
	//{
		//请求服务器数据
		tagGPEnterCustomRoom enterCustomRoom;
		enterCustomRoom.dwRoomVerifyID = dwRoomVerifyID;
		mCustomRoomMission.enterCustomRoom(enterCustomRoom);
	//}
	
}

bool CustonRoomUI::checkAutoEnterCustomGame()
{
	//获取对象
	ASSERT(CServerListData::shared() != 0);
	CServerListData * pServerListData = CServerListData::shared();

	//变量定义
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();
	if (pGlobalUserData->dwRoomExtData > 0)
	{
		const CGameServerItem* pSvr = pServerListData->searchCustomServerByUUID(pGlobalUserData->dwRoomExtData);
		if (NULL != pSvr)
		{
			onGPEnterCustomRoomSuccess(pGlobalUserData->dwRoomExtData, pSvr->m_GameServer);
			return true;
		}
	}
	return false;
}

void CustonRoomUI::enterCustomRoom(int dwRoomID)
{
	MELOG(MELOG_INFO, "enterCustomRoom ............... %d\n", dwRoomID);
	G_NOTIFY("CONNECT_CUSTOM_SERVER", MTData::create(dwRoomID));
}

//////////////////////////////////////////////////////////////////////////
// IGPCustomRoomMissionSink
void CustonRoomUI::onGPCreateCustomRoomSuccess(dword dwRoomID, const tagGameServer& server)
{
	char sz7[7] = { 0 };
	sprintf(sz7, "%06d", dwRoomID);
	DF::shared()->encryptRoomID(sz7);
	MELOG(MELOG_INFO, "onGPCreateCustomRoomSuccess  %d, %s\n", dwRoomID, sz7);
	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onEnterCustomRoomBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushInt(dwRoomID);
		pStack->pushInt(server.wKindID);
		pStack->pushString(server.szServerName);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 3);
	} while (0);
}

void CustonRoomUI::onGPCreateCustomRoomFailure(int errorCode)
{
	//TODO 失败提示
	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onCreateCustomRoomErrorBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushInt(errorCode);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
	} while (0);
}

void CustonRoomUI::onGPEnterCustomRoomSuccess(dword dwRoomID, const tagGameServer& server)
{
	char sz7[7] = { 0 };
	sprintf(sz7, "%06d", dwRoomID);
	DF::shared()->encryptRoomID(sz7);
	MELOG(MELOG_INFO, "onGPEnterCustomRoomSuccess  %d, %s\n", dwRoomID, sz7);
	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onEnterCustomRoomBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushInt(dwRoomID);
		pStack->pushInt(server.wKindID);
		pStack->pushString(server.szServerName);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 3);
	} while (0);
}

void CustonRoomUI::onGPEnterCustomRoomFailure(int errorCode)
{
	//TODO 失败提示
	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onEnterCustomRoomErrorBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushInt(errorCode);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
	} while (0);
}