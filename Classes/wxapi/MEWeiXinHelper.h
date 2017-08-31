#ifndef __MEWEIXINELPER_H__
#define __MEWEIXINELPER_H__

#include <map>
#include "MissionWeiXin.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class MEWeiXinHelper: public IWeiXinMissionSink
{
public:
	static MEWeiXinHelper * getInstance();
	static void purge();

	void wxlogin();
	void shareImageWX(const char* ImgPath, int nType);
	void shareTextWX(const char* kText, int nType);
	void shareUrlWX(const char* kUrl, const char* kTitle, const char* kDesc, int nType);
	void showWebView(const char* kUrl);

	void qqlogin();
	void qqlogout();

	void applyPay(const char* subject, const char* body, const char* price);
	void applyPayByOrder(const char* order);
	void wxPay(const char* body, const char* price);
	void wxPayByOrder(const char* order);

	WxUserInfo& getLoginInfoByType(int nType);

	void onQQLoginSuccess(std::string param);
	void onApplyPayResultState(int iCode);
	void onWxShareResultState(int iCode);
	void onWxPayResultState(int iCode);
	//IWeiXinMissionSink
public:
	virtual void onWxLoginSuccess(WxUserInfo kWxUserInfo);
	virtual void onWxLoginFail(std::string kError);
protected:
	MEWeiXinHelper();
	virtual ~MEWeiXinHelper();
 protected:
	 WxUserInfo	m_kWeiXinUserInfo;
	 WxUserInfo	m_kQQUserInfo;
	 std::string m_strError;
};

#endif //__MEWEIXINELPER_H__