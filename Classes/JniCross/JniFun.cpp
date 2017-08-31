#include "JniFun.h"
#include "cocos2d.h"
#include "wxapi/UtilityBase.h"
#include "MELog.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include <Jni.h>
#include "platform/android/jni/JniHelper.h"
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "IosHelper.h"
#endif

#define JAVA_CLASSNAME  "org/cocos2dx/lua/Native"
#define JAVA_CLASSNAME2  "org/cocos2dx/lua/TencentData"
#define JAVA_CLASSNAME3  "org/cocos2dx/lua/PayDemoActivity"

using namespace cocos2d;
namespace JniFun
{
	void longinWX(const char* APP_ID,const char* AppSecret)
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		JniMethodInfo minfo;
		log("JniFun::longinWX %s, %s", APP_ID, AppSecret);
		bool isHave = JniHelper::getStaticMethodInfo(minfo,JAVA_CLASSNAME,"LoginWX","(Ljava/lang/String;Ljava/lang/String;)V");
		if (isHave)
		{
			jstring jAPP_ID = minfo.env->NewStringUTF(APP_ID);
			jstring jAppSecret = minfo.env->NewStringUTF(AppSecret);
			minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,jAPP_ID,jAppSecret);

			minfo.env->DeleteLocalRef(jAPP_ID);
			minfo.env->DeleteLocalRef(jAppSecret);
			minfo.env->DeleteLocalRef(minfo.classID); 
			log("JniFun::longinWX call LoginWX over!");
		}
		else
		{
			log("JniFun call LoginWX error!");
		}
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		IosHelper::sendAuthRequest();
#endif
	}

	void shareImageWX(const char* ImgPath,int nType)
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		JniMethodInfo minfo;
		bool isHave = JniHelper::getStaticMethodInfo(minfo,JAVA_CLASSNAME,"ShareImageWX","(Ljava/lang/String;I)V");
		if (isHave)
		{
			jstring jImgPath = minfo.env->NewStringUTF(ImgPath);
			minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,jImgPath,nType);
			log("JniFun call ShareImageWX over!");

			minfo.env->DeleteLocalRef(jImgPath);
			minfo.env->DeleteLocalRef(minfo.classID); 
		}
		else
		{
			log("JniFun call ShareImageWX error!");
		}
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		if (nType == 0)
		{
			IosHelper::shareWithWeixinFriendImg("",ImgPath);
		}
		else
		{
			IosHelper::shareWithWeixinCircleImg("",ImgPath);
		}
#endif
	}

	void shareTextWX(const char* kText,int nType)
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
			JniMethodInfo minfo;
			bool isHave = JniHelper::getStaticMethodInfo(minfo,JAVA_CLASSNAME,"ShareTextWX","(Ljava/lang/String;I)V");
			if (isHave)
			{
				jstring jkText = minfo.env->NewStringUTF(kText);
				minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,jkText,nType);
				log("JniFun call ShareTextWX over!");

				minfo.env->DeleteLocalRef(jkText);
				minfo.env->DeleteLocalRef(minfo.classID); 
			}
			else
			{
				log("JniFun call ShareTextWX error!");
			}
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
			if (nType == 0)
			{
				IosHelper::shareWithWeixinFriendTxt(kText,"", kText);
			}
			else
			{
				IosHelper::shareWithWeixinCircleTxt(kText,"", kText);
			}
#endif
	}

	void shareUrlWX(const char* kUrl,const char* kTitle,const char* kDesc,int nType)
	{

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		JniMethodInfo minfo;
		bool isHave = JniHelper::getStaticMethodInfo(minfo,JAVA_CLASSNAME,"ShareUrlWX","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V");
		if (isHave)
		{
			jstring jkUrlt = minfo.env->NewStringUTF(kUrl);
			jstring jkTitle = minfo.env->NewStringUTF(kTitle);
			jstring jkDesc = minfo.env->NewStringUTF(kDesc);
			minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,jkUrlt,jkTitle,jkDesc,nType);
			log("JniFun call ShareUrlWX over!");

			minfo.env->DeleteLocalRef(jkUrlt);
			minfo.env->DeleteLocalRef(jkTitle);
			minfo.env->DeleteLocalRef(jkDesc);
			minfo.env->DeleteLocalRef(minfo.classID); 
		}
		else
		{
			log("JniFun call ShareUrlWX error!");
		}
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		if (nType == 0)
		{
			IosHelper::shareWithWeixinFriendTxt(kTitle,kUrl,kDesc);
		}
		else
		{
			IosHelper::shareWithWeixinCircleTxt(kTitle,kUrl, kDesc);
		}
#endif
	}

	void showWebView(const char* url )
	{

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		JniMethodInfo minfo;
		bool isHave = JniHelper::getStaticMethodInfo(minfo,JAVA_CLASSNAME,"showWebView","(Ljava/lang/String;)V");
		if (isHave)
		{
			jstring jurl = minfo.env->NewStringUTF(url);
			minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,jurl);
			log("JniFun call showWebView over!");

			minfo.env->DeleteLocalRef(jurl);
			minfo.env->DeleteLocalRef(minfo.classID); 
			log("JniFun call showWebView over!111");
		}
		else
		{
			log("JniFun call showWebView error!");
		}
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		IosHelper::startBrowserJni(url);
#endif
	}

	void loginQQ()
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		JniMethodInfo mObjInfo;
		bool isHaveObj = JniHelper::getStaticMethodInfo(mObjInfo,"org/cocos2dx/lua/AppActivity","getTencentActivity", "()Ljava/lang/Object;");
		jobject jobj;
		if (isHaveObj){
			jobj = mObjInfo.env->CallStaticObjectMethod(mObjInfo.classID, mObjInfo.methodID);
		}
		else
		{
			log("JniFun call loginQQ error by not found method!");
		}

		JniMethodInfo methodInfo;
		bool isHaveMethod = JniHelper::getMethodInfo(methodInfo, JAVA_CLASSNAME2, "login", "()V");
		if (isHaveMethod){
			methodInfo.env->CallVoidMethod(jobj, methodInfo.methodID);
			log("JniFun::loginQQ call login over!");
		}
		else
		{
			log("JniFun call loginQQ error!");
		}
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		IosHelper::loginQQ();
#endif
	}

	void logoutQQ()
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		JniMethodInfo mObjInfo;
		bool isHaveObj = JniHelper::getStaticMethodInfo(mObjInfo, "org/cocos2dx/lua/AppActivity", "getTencentActivity", "()Ljava/lang/Object;");
		jobject jobj;
		if (isHaveObj){
			jobj = mObjInfo.env->CallStaticObjectMethod(mObjInfo.classID, mObjInfo.methodID);
		}
		else
		{
			log("JniFun call logoutQQ error by not found method!");
		}

		JniMethodInfo methodInfo;
		bool isHaveMethod = JniHelper::getMethodInfo(methodInfo, JAVA_CLASSNAME2, "logout", "()V");
		if (isHaveMethod){
			methodInfo.env->CallVoidMethod(jobj, methodInfo.methodID);
			log("JniFun::logoutQQ call logout over!");
		}
		else
		{
			log("JniFun call logoutQQ error!");
		}
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        IosHelper::logoutQQ();
#endif
	}

	void applyPay(const char* subject, const char* body, const char* price)
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		JniMethodInfo minfo;
		log("JniFun::applyPay ............................... %s, %s, %s", subject, body, price);
		bool isHave = JniHelper::getStaticMethodInfo(minfo,JAVA_CLASSNAME3,"pay","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		if (isHave)
		{
			jstring jSubject = minfo.env->NewStringUTF(subject);
			jstring jBody = minfo.env->NewStringUTF(body);
			jstring jPrice = minfo.env->NewStringUTF(price);
			minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,jSubject,jBody,jPrice);
			minfo.env->DeleteLocalRef(jSubject);
			minfo.env->DeleteLocalRef(jBody);
			minfo.env->DeleteLocalRef(jPrice);
			minfo.env->DeleteLocalRef(minfo.classID); 
			log("JniFun::applyPay call pay over!");
		}
		else
		{
			log("JniFun call applyPay error!");
		}
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		
#endif
	}

	void applyPayByOrder(const char* order)
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		JniMethodInfo minfo;
		log("JniFun::applyPay ............................... %s", order);
		bool isHave = JniHelper::getStaticMethodInfo(minfo, JAVA_CLASSNAME3, "payByOrder", "(Ljava/lang/String;)V");
		if (isHave)
		{
			jstring jOrder = minfo.env->NewStringUTF(order);
			minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jOrder);
			minfo.env->DeleteLocalRef(jOrder);
			minfo.env->DeleteLocalRef(minfo.classID);
			log("JniFun::applyPay call pay over!");
		}
		else
		{
			log("JniFun call applyPay error!");
		}
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#endif
	}

	void wxPay(const char* body, const char* price)
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		JniMethodInfo minfo;
		log("JniFun::wxPay ............................... %s, %s", body, price);
		bool isHave = JniHelper::getStaticMethodInfo(minfo, JAVA_CLASSNAME, "wxPay", "(Ljava/lang/String;Ljava/lang/String;)V");
		if (isHave)
		{
			jstring jBody = minfo.env->NewStringUTF(body);
			jstring jPrice = minfo.env->NewStringUTF(price);
			minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jBody, jPrice);
			minfo.env->DeleteLocalRef(jBody);
			minfo.env->DeleteLocalRef(jPrice);
			minfo.env->DeleteLocalRef(minfo.classID);
			log("JniFun::wxPay call pay over!");
		}
		else
		{
			log("JniFun call wxPay error!");
		}
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#endif
	}

	void wxPayByOrder(const char* order)
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		JniMethodInfo minfo;
		log("JniFun::wxPay ............................... %s", order);
		bool isHave = JniHelper::getStaticMethodInfo(minfo, JAVA_CLASSNAME, "wxPayByOrder", "(Ljava/lang/String;)V");
		if (isHave)
		{
			jstring jOrder = minfo.env->NewStringUTF(order);
			minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jOrder);
			minfo.env->DeleteLocalRef(jOrder);
			minfo.env->DeleteLocalRef(minfo.classID);
			log("JniFun::wxPay call pay over!");
		}
		else
		{
			log("JniFun call wxPay error!");
		}
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        IosHelper::wxPayByOrder(order);
#endif
	}
}
