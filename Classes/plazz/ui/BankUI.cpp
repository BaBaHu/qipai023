#include "BankUI.h"
#include "MECallBackListenerHelper.h"
//保险柜（存款与取款、赠送）

//////////////////////////////////////////////////////////////////////////
BankUI::BankUI()
: mInsureMission(DEFAULT_IP_ADDRESS, DEFAULT_PORT)
{
	mInsureMission.setMissionSink(this);
}

BankUI::~BankUI()
{
	mInsureMission.setMissionSink(0);
}

BankUI* BankUI::create(std::string strIp, int iPort)
{
	BankUI *pRet = new BankUI();
	if (pRet && pRet->init(strIp, iPort))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

//初始化方法
bool BankUI::init(std::string strIp, int iPort)
{
	mInsureMission.setUrl(strIp, iPort);
	return true;
}


void BankUI::onInsureInfo()
{
	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onInsureUpdateBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 0);
	} while (0);
}

void BankUI::onInsureSuccess(int type, const char* szDescription)
{
	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onInsureSuccessBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushString(szDescription);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
	} while (0);
}

void BankUI::onInsureFailure(int type, const char* szDescription)
{
	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onInsureFailureBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushString(szDescription);
		pStack->pushInt(type);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 2);
	} while (0);
}

void  BankUI::query()
{
	mInsureMission.query();
}

void BankUI::save(int value)
{
	mInsureMission.save(value);
}

void BankUI::take(int64 score, const char* szInsurePass)
{
	mInsureMission.take(score, szInsurePass);
}

void BankUI::transfer(int nType, int64 score, const char* szInsurePass, const char* szNickName, uint8 cbByNickName)
{
	mInsureMission.transfer(nType, score, szInsurePass, szNickName, cbByNickName);
}

void BankUI::modifyPassword(int nType, const char* szOldPass, const char* szNewPass)
{
	mInsureMission.modifyPassword(nType, szOldPass, szNewPass);
}
