#pragma  once
#include "cocos2d.h"

namespace JniFun
{
	void longinWX(const char* APP_ID,const char* AppSecret);
	void shareImageWX(const char* ImgPath,int nType);
	void shareTextWX(const char* kText,int nType);
	void shareUrlWX(const char* kUrl,const char* kTitle,const char* kDesc,int nType);
	void showWebView(const char* url );

	void loginQQ();
	void logoutQQ();

	void applyPay(const char* subject, const char* body, const char* price);
	void applyPayByOrder(const char* order);
	void wxPay(const char* body, const char* price);
	void wxPayByOrder(const char* order);
} 