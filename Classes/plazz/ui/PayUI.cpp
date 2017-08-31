#include "PayUI.h"
#include "MECallBackListenerHelper.h"

//////////////////////////////////////////////////////////////////////////
PayUI::PayUI()
: mExchangeMission(DEFAULT_IP_ADDRESS, DEFAULT_PORT)
{
	mExchangeMission.setMissionSink(this);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    m_bridge = new IOSiAP_Bridge();
#endif
}

PayUI::~PayUI()
{
	mExchangeMission.setMissionSink(0);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CC_SAFE_DELETE(m_bridge);
#endif
}

PayUI* PayUI::create(std::string strIp, int iPort)
{
	PayUI *pRet = new PayUI();
	if (pRet && pRet->init(strIp, iPort))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

//初始化方法
bool PayUI::init(std::string strIp, int iPort)
{
	mExchangeMission.setUrl(strIp, iPort);
	return true;
}


// 兑换道具
void PayUI::exchange(int item)
{
	mExchangeMission.exchange(item);
}

void PayUI::payIpa(const char* proId)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	m_bridge->requestProducts(proId);
#endif
}

// 
void PayUI::pay(int nBuyType, long long lBuyCount, unsigned int lPayRMB, int nPayType)
{
	tagPay Pay;
	Pay.mBuyType = nBuyType;
	Pay.mBuyCount = lBuyCount;
	Pay.mPayRMB = lPayRMB;
	Pay.mPayType = nPayType;

	mExchangeMission.pay(Pay);
}

void PayUI::payCard(const char* card, const char* pwd)
{
	mExchangeMission.payCard(card, pwd);
}

void PayUI::share()
{
	mExchangeMission.share();
}

void  PayUI::onGPExchangeResult(int lResultCode, const char* szDescription)
{

}

void PayUI::onGPShaerResult(const char* szDescription)
{
	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onShareResultBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushString(szDescription);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
	} while (0);
}

void  PayUI::onGPPayCardResult(const char* szDescription)
{
	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onPayCardResultBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushString(szDescription);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
	} while (0);
}
