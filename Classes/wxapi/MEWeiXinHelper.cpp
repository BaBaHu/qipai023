#include "MEWeiXinHelper.h"
#include "MECallBackListenerHelper.h"
#include "MELog.h"
#include "JniCross/JniFun.h"

static MEWeiXinHelper *g_sharedWeiXinHelper = NULL;

MEWeiXinHelper::MEWeiXinHelper()
{
	memset(&m_kWeiXinUserInfo, 0, sizeof(m_kWeiXinUserInfo));
	MissionWeiXin::Instance().setMissionSink(this);
}

MEWeiXinHelper::~MEWeiXinHelper()
{
	MissionWeiXin::Instance().setMissionSink(0);
}

MEWeiXinHelper * MEWeiXinHelper::getInstance()
{
	if (g_sharedWeiXinHelper == NULL)
		g_sharedWeiXinHelper = new MEWeiXinHelper();
	return g_sharedWeiXinHelper;
}

void MEWeiXinHelper::purge()
{
	if (g_sharedWeiXinHelper)
	{
		delete g_sharedWeiXinHelper;
		g_sharedWeiXinHelper = NULL;
	}
}

void  MEWeiXinHelper::wxlogin()
{
    MELOG(MELOG_INFO, "wxlogin .................................\n");
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	int start = 100;
	int end = 100102;
//	int random = CCRANDOM_0_1() * (end - start + 1) * start;		
	int random = end + CCRANDOM_0_1() * 1000 ;	// 为了使用网狐服务器，账号在101000~101999

	char p[10];
	sprintf(p, "%d", random);

	std::string strrandom(p);

//	std::string kNickName = "grwoing_" + strrandom;
	std::string kNickName = strrandom;

	m_kWeiXinUserInfo.unionid = kNickName;
	m_kWeiXinUserInfo.nickname = "";
	m_kWeiXinUserInfo.headimgurl = "";

	onWxLoginSuccess(m_kWeiXinUserInfo);	// 把m_kWeiXinUserInfo 这个参数传入lua中区  最后执行 lua 中的 onOtherLoginBack 表示用微信登陆成功
#else
	cocos2d::log("µ˜”√Œ¢–≈£°");
	MissionWeiXin::Instance().logonWeiXin();
#endif
}

void MEWeiXinHelper::shareImageWX(const char* ImgPath, int nType)
{
	MELOG(MELOG_INFO, "shareImageWX .................................%s, %d\n", ImgPath, nType);
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#else
	cocos2d::log("µ˜”√Œ¢–≈∑÷œÌÕº∆¨£°");
	MissionWeiXin::Instance().shareScreenWeiXin(ImgPath, nType);
#endif
}

void MEWeiXinHelper::shareTextWX(const char* kText, int nType)
{
	MELOG(MELOG_INFO, "shareTextWX .................................%s, %d\n", kText, nType);
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#else
	cocos2d::log("µ˜”√Œ¢–≈∑÷œÌŒƒ◊÷£°");
	MissionWeiXin::Instance().shareTextWeiXin(kText, nType);
#endif
}

void MEWeiXinHelper::shareUrlWX(const char* kUrl, const char* kTitle, const char* kDesc, int nType)
{
	MELOG(MELOG_INFO, "shareUrlWX .................................%s, %s, %s, %d\n", kUrl, kTitle, kDesc, nType);
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#else
	cocos2d::log("µ˜”√Œ¢–≈∑÷œÌURL£°");
	MissionWeiXin::Instance().shareUrlWeiXin(kUrl, kTitle, kDesc, nType);
#endif
}

void MEWeiXinHelper::showWebView(const char* kUrl)
{
	MELOG(MELOG_INFO, "showWebView .................................%s\n", kUrl);
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#else
	cocos2d::log("打开网页");
	JniFun::showWebView(kUrl);
#endif
}

void MEWeiXinHelper::qqlogin()
{
	MELOG(MELOG_INFO, "qqlogin .................................\n");
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#else
	cocos2d::log("µ˜”√QQµ«»Î£°");
	JniFun::loginQQ();
#endif
}

void MEWeiXinHelper::qqlogout()
{
	MELOG(MELOG_INFO, "qqlogout .................................\n");
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	
#else
	cocos2d::log("µ˜”√QQµ«≥ˆ£°");
	JniFun::logoutQQ();
#endif
}

void MEWeiXinHelper::applyPay(const char* subject, const char* body, const char* price)
{
	MELOG(MELOG_INFO, "applyPay .................................\n");
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	
#else
	cocos2d::log("µ˜”√÷ß∏∂±¶£°");
	JniFun::applyPay(subject, body, price);
#endif
}

void MEWeiXinHelper::applyPayByOrder(const char* order)
{
	MELOG(MELOG_INFO, "applyPay .................................\n");
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#else
	cocos2d::log("µ˜”√÷ß∏∂±¶£°");
	JniFun::applyPayByOrder(order);
#endif
}

void MEWeiXinHelper::wxPay(const char* body, const char* price)
{
	MELOG(MELOG_INFO, "wxPay .................................\n");
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#else
	cocos2d::log("µ˜”√Œ¢–≈÷ß∏∂£°");
	JniFun::wxPay(body, price);
#endif
}

void MEWeiXinHelper::wxPayByOrder(const char* order)
{
	MELOG(MELOG_INFO, "wxPayByOrder .................................\n");
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#else
	cocos2d::log("µ˜”√Œ¢–≈÷ß∏∂£°");
	JniFun::wxPayByOrder(order);
#endif
}

WxUserInfo& MEWeiXinHelper::getLoginInfoByType(int nLoginType)
{
	log("getLoginInfoByType .................................%d\n", nLoginType);
	if (nLoginType == 2)
	{
		return m_kWeiXinUserInfo;
	}
	else if (nLoginType == 1)
	{
		return m_kQQUserInfo;
	}
}

void MEWeiXinHelper::onWxLoginSuccess(WxUserInfo kWxUserInfo)
{
	log("onWxLoginSuccess .................................\n");
	memcpy(&m_kWeiXinUserInfo, &kWxUserInfo, sizeof(WxUserInfo));

	log("MEWeiXinHelper::onWxLoginSuccess : openid %s\n", m_kWeiXinUserInfo.openid.c_str());
	log("MEWeiXinHelper::onWxLoginSuccess : unionid %s\n", m_kWeiXinUserInfo.unionid.c_str());
	log("MEWeiXinHelper::onWxLoginSuccess : nickname %s\n", m_kWeiXinUserInfo.nickname.c_str());
	log("MEWeiXinHelper::onWxLoginSuccess : sex %d\n", m_kWeiXinUserInfo.sex);
	log("MEWeiXinHelper::onWxLoginSuccess : headimgurl %s\n", m_kWeiXinUserInfo.headimgurl.c_str());

	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onOtherLoginBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushInt(2);
		pStack->pushString(m_kWeiXinUserInfo.headimgurl.c_str());
		ret = pStack->executeFunctionByHandler(nLuaHandler, 2);		// 执行onOtherLoginBack 主要是把登陆参数，传到lua中去
	} while (0);
}

void MEWeiXinHelper::onWxLoginFail(std::string kError)
{
	log("LogonUI::onWxLoginFail %s", kError.c_str());
	m_strError = kError;

	Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
		int ret = 0;
		do
		{
			LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onLoginErrorBack");
			CC_BREAK_IF(0 == nLuaHandler);
			LuaEngine* pEngine = LuaEngine::getInstance();
			LuaStack* pStack = pEngine->getLuaStack();
			lua_State *tolua_s = pStack->getLuaState();
			lua_settop(tolua_s, 0);
			pStack->pushString(m_strError.c_str());
			ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
		} while (0);
	});
}

void MEWeiXinHelper::onQQLoginSuccess(std::string param)
{
	log("MEWeiXinHelper::onQQLoginSuccess : %s\n", param.c_str());
	std::vector<std::string> kVector = utility::split(param, "+");
	if (kVector.size() != 6)
	{
		log("if (kVector.size() != 6)");
		return;
	}
	m_kQQUserInfo.openid = kVector[0].c_str();
	m_kQQUserInfo.unionid = kVector[1].c_str();
	m_kQQUserInfo.nickname = kVector[3].c_str();
	m_kQQUserInfo.headimgurl = kVector[4].c_str();
	if ("男" == kVector[5].c_str())
	{
		m_kQQUserInfo.sex = 2;
	}
	else
	{
		m_kQQUserInfo.sex = 1;
	}
	log("MEWeiXinHelper::onQQLoginSuccess : openid %s\n", m_kQQUserInfo.openid.c_str());
	log("MEWeiXinHelper::onQQLoginSuccess : unionid %s\n", m_kQQUserInfo.unionid.c_str());
	log("MEWeiXinHelper::onQQLoginSuccess : nickname %s\n", m_kQQUserInfo.nickname.c_str());
	log("MEWeiXinHelper::onQQLoginSuccess : sex %d\n", m_kQQUserInfo.sex );
	log("MEWeiXinHelper::onQQLoginSuccess : headimgurl %s\n", m_kQQUserInfo.headimgurl.c_str() );

	Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
		int ret = 0;
		do
		{
			LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onOtherLoginBack");
			CC_BREAK_IF(0 == nLuaHandler);
			LuaEngine* pEngine = LuaEngine::getInstance();
			LuaStack* pStack = pEngine->getLuaStack();
			lua_State *tolua_s = pStack->getLuaState();
			lua_settop(tolua_s, 0);
			pStack->pushInt(1);
			pStack->pushString(m_kQQUserInfo.headimgurl.c_str());
			ret = pStack->executeFunctionByHandler(nLuaHandler, 2);
		} while (0);
	});
}

void MEWeiXinHelper::onApplyPayResultState(int iCode)
{
	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onApplyPayResultStateBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushInt(iCode);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
	} while (0);
}

void MEWeiXinHelper::onWxShareResultState(int iCode)
{
	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onWxShareResultStateBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushInt(iCode);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
	} while (0);
}

void  MEWeiXinHelper::onWxPayResultState(int iCode)
{
	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onApplyPayResultStateBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushInt(iCode);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
	} while (0);
}
