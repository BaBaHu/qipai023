#ifndef _LogonUI_H_
#define _LogonUI_H_

#include "cocos2d.h"
#include "../plazz/GPMission.h"

USING_NS_CC;

class LogonUI : public Ref, public IGPLoginMissionSink, public IGPMsgMissionSink
{
public:
	LogonUI();
	~LogonUI();
	static LogonUI* create(std::string strIp, int iPort);

	void login(std::string strAccount, std::string strPwd);
	void logout();
	void regist(std::string strAccount, std::string strPwd);
	void loginByType(int nLoginType);
	void getBaseEnsureTake();
	//////////////////////////////////////////////////////////////////////////
	// IGPLoginMissionSink
public:
	virtual void onGPLoginSuccess();
	virtual void onGPLoginComplete();
	virtual void onGPBaseEnsureComplete(bool bSuccessedconst, const char* szDescription);
	virtual void onGPLoginFailure(const char* szDescription);
	virtual void onGPError(int err);
	// IGPMsgMissionSink
public:
	virtual void onGPNotice(const char* szDescription);
	virtual void onGPMsgError(int errorCode);
private:
	bool init(std::string strIp, int iPort);
private:
	int			mLoginState; // 0:没什么 1:登陆界面 2:注册界面 3:go 登陆中 4:go 登陆完成
	bool		mIsRemeber;
	std::string mAccount;
	std::string mPassword;
	
	//////////////////////////////////////////////////////////////////////////
	// mission
	CGPLoginMission	mLogionMission;
	CGPNoticeMsgMission mNoticeMsgMission;
};
#endif // _LogonUI_H_