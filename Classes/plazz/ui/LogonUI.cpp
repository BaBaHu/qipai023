#include "LogonUI.h"
#include "MTNotification.h"
#include "MECallBackListenerHelper.h"
#include "MELog.h"
#include "wxapi/MEWeiXinHelper.h"
#include "YvVoiceManager.h"

USING_NS_CC;

const char* ACCOUNT_ACCOUNT		= "account";
const char* ACCOUNT_PASSWORD	= "password";

LogonUI::LogonUI()
: mLogionMission(DEFAULT_IP_ADDRESS, DEFAULT_PORT)
,mNoticeMsgMission(DEFAULT_IP_ADDRESS, 30312)
{
	mIsRemeber = true;
	mLogionMission.setMissionSink(this);
	mNoticeMsgMission.setMissionSink(this);
}

LogonUI::~LogonUI()
{
	mLogionMission.setMissionSink(0);
	mNoticeMsgMission.setMissionSink(0);
}

LogonUI* LogonUI::create(std::string strIp, int iPort)
{
	LogonUI *pRet = new LogonUI();
	if (pRet && pRet->init(strIp, iPort))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool LogonUI::init(std::string strIp, int iPort)
{
	mLogionMission.setUrl(strIp, iPort);
	
	/*std::string sAccount = UserDefault::getInstance()->getStringForKey(ACCOUNT_ACCOUNT, "");
	std::string sPassword = UserDefault::getInstance()->getStringForKey(ACCOUNT_PASSWORD, "");
	if (!sAccount.empty() && !sPassword.empty())
	{
		sAccount = decode(sAccount);
		sPassword = decode(sPassword);
	}
	else
	{
		sAccount = "";
		sPassword = "";
	}*/
	return true;
}

void LogonUI::login(std::string strAccount, std::string strPwd)
{
	tagGPLoginAccount loginAccount;
	loginAccount.cbValidateFlags = MB_VALIDATE_FLAGS|LOW_VER_VALIDATE_FLAGS;
	strcpy(loginAccount.szAccounts, strAccount.c_str());
	strcpy(loginAccount.szPassword, strPwd.c_str());

	if (mIsRemeber)
	{
		mAccount = strAccount; //encode(strAccount);
		mPassword = strPwd; //encode(strPwd);
	}
	
	mLogionMission.loginAccount(loginAccount);
}

void LogonUI::logout()
{
	YvVoiceManager::GetInstance()->CpLogout();
}

void LogonUI::regist(std::string strAccount, std::string strPwd)
{
	tagGPRegisterAccount tagAccount;
	memset(&tagAccount, 0, sizeof(tagAccount));
	tagAccount.cbValidateFlags = LOW_VER_VALIDATE_FLAGS | MB_VALIDATE_FLAGS;
	memcpy(tagAccount.szAccounts, strAccount.c_str(), sizeof(tagAccount.szAccounts));
	memcpy(tagAccount.szLogonPass, strPwd.c_str(), sizeof(tagAccount.szLogonPass));
	memcpy(tagAccount.szInsurePass, strPwd.c_str(), sizeof(tagAccount.szInsurePass));
	memcpy(tagAccount.szNickName, strAccount.c_str(), sizeof(tagAccount.szNickName));

	mIsRemeber = true;
	if (mIsRemeber)
	{
		mAccount = strAccount; //encode(strAccount);
		mPassword = strPwd; //encode(strPwd);
	}

	mLogionMission.registerAccount(tagAccount);
}

void  LogonUI::loginByType(int nLoginType)
{
	WxUserInfo info = MEWeiXinHelper::getInstance()->getLoginInfoByType(nLoginType);

	tagGPLoginByType loginType;
	loginType.cbValidateFlags = MB_VALIDATE_FLAGS | LOW_VER_VALIDATE_FLAGS;
	loginType.cbSex = info.sex;
	loginType.cbType = nLoginType;
	if (nLoginType == 2)
	{
		strcpy(loginType.szAccounts, info.unionid.c_str());
	}
	else if (nLoginType == 1)
	{
		strcpy(loginType.szAccounts, info.openid.c_str());
	}
	strcpy(loginType.szNickName, info.nickname.c_str());
	strcpy(loginType.szIconUrl, info.headimgurl.c_str());

	mLogionMission.loginType(loginType);
}

void LogonUI::getBaseEnsureTake()
{
	mLogionMission.getBaseEnsureTake();
}

//////////////////////////////////////////////////////////////////////////
// IGPLoginMissionSink
void LogonUI::onGPLoginSuccess()
{
	//变量定义
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	tagUserInsureInfo * pUserInsureInfo=pGlobalUserInfo->GetUserInsureInfo();

	log("wFaceID %d", pGlobalUserData->wFaceID);
	log("cbGender %d", pGlobalUserData->cbGender);
	log("dwGameID %lu", pGlobalUserData->dwGameID);
	log("dwUserID %lu", pGlobalUserData->dwUserID);
	log("dwCustomID %lu", pGlobalUserData->dwCustomID);
	log("dwUserMedal %lu", pGlobalUserData->dwUserMedal);
	log("dwExperience %lu", pGlobalUserData->dwExperience);
	log("dwLoveLiness %lu", pGlobalUserData->dwLoveLiness);
	log("cbMoorMachine %d", pGlobalUserData->cbMoorMachine);
	log("lUserScore " LLSTRING, pUserInsureInfo->lUserScore);
	log("lUserInsure " LLSTRING, pUserInsureInfo->lUserInsure);
	log("szAccounts %s", pGlobalUserData->szAccounts);
	log("szNickName %s", pGlobalUserData->szNickName);
	MELOG(MELOG_INFO, "szUrl %s", pGlobalUserData->szIconUrl);
	log("cbDailiOrder %d", pGlobalUserData->cbDailiOrder);
	MELOG(MELOG_INFO, "cbUserType %d", pGlobalUserData->cbUserType);
	log("cbMemberOrder %d", pGlobalUserData->cbMemberOrder);
	log("MemberOverDate %04d/%02d/%02d %02d:%02d:%02d %d", pGlobalUserData->MemberOverDate.wYear,
		pGlobalUserData->MemberOverDate.wMonth,pGlobalUserData->MemberOverDate.wDay,
		pGlobalUserData->MemberOverDate.wHour,pGlobalUserData->MemberOverDate.wMinute,
		pGlobalUserData->MemberOverDate.wMinute,pGlobalUserData->MemberOverDate.wDayOfWeek);

	log("szUnderWrite %s", pGlobalUserData->szUnderWrite);

	YvVoiceManager::GetInstance()->CpLogin(pGlobalUserData->szAccounts, pGlobalUserData->szAccounts);

	if (mIsRemeber)
	{
		UserDefault::getInstance()->setStringForKey(ACCOUNT_ACCOUNT, mAccount);
		UserDefault::getInstance()->setStringForKey(ACCOUNT_PASSWORD, mPassword);
	}
}

void LogonUI::onGPLoginComplete()
{
	G_NOTIFY("LOGON_COMPLETE", 0);	// 消息的方式调用 logonCompleteNotify, onGPLoginComplete()是来至网络的
	mNoticeMsgMission.loginMsg();
}

void  LogonUI::onGPBaseEnsureComplete(bool bSuccessed, const char* szDescription)
{
	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onBaseEnsureBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushBoolean(bSuccessed);
		pStack->pushString(szDescription);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 2);
	} while (0);
}

void LogonUI::onGPLoginFailure(const char* szDescription)
{
	//TODO 失败提示
	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onLoginErrorBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushString(szDescription);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
	} while (0);
}

void LogonUI::onGPError(int err)
{
	log("LogonUI::onGPError %d", err);
	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onNetErrorBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushInt(err);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
	} while (0);
}

void  LogonUI::onGPNotice(const char* szMessage)
{
	G_NOTIFY("NOTICE_MSG", MTData::create(0, 0, 0, szMessage) );
}

void  LogonUI::onGPMsgError(int errorCode)
{

}
