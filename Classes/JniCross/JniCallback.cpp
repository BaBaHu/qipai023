#include "JniCallback.h"
#include "cocos2d.h"
#include "wxapi/MissionWeiXin.h"
#include "wxapi/MEWeiXinHelper.h"
#include "MELog.h"

//������C���Եĺ�������ΪC++�ĺ������в�ͬ�ķ������ɹ���  
//1.Java_:�Ǹ�ʽ������ӵ�  
//2.org_cocos2dx_cpp_tools_JniHelper:�ǰ���+����  
//3.onResp:��Andriod����������������  
//4.�м���Ҫ_�ֿ�

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include <Jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

using namespace cocos2d;

namespace JniFun
{
	extern "C" 
	{

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
  		 
		JNIEXPORT void JNICALL Java_org_cocos2dx_lua_Native_WxLoginGetAccessToken (JNIEnv* env, jclass method, jstring param)
		{
			const char* data = env->GetStringUTFChars(param, 0);
			log("JinCallBack :%s",data);
			MissionWeiXin::Instance().Req_Access_token(data);
			env->ReleaseStringUTFChars(param, data);
		}

		JNIEXPORT void JNICALL Java_org_cocos2dx_lua_Native_WxLoginGetFailToken (JNIEnv* env, jclass method, jstring param)
		{
			const char* data = env->GetStringUTFChars(param, 0);
			log("JinCallBack :%s",data);
			MissionWeiXin::Instance().Req_Fail_token(data);
			env->ReleaseStringUTFChars(param, data);
		}

		JNIEXPORT void JNICALL Java_org_cocos2dx_lua_Native_QQLoginGetAccessToken (JNIEnv* env, jclass method, jstring param)
		{
			const char* data = env->GetStringUTFChars(param, 0);
			log("JinCallBack :%s",data);
			MEWeiXinHelper::getInstance()->onQQLoginSuccess(data);
			env->ReleaseStringUTFChars(param, data);
		}

		JNIEXPORT void JNICALL Java_org_cocos2dx_lua_Native_QQLoginGetFailToken (JNIEnv* env, jclass method, jstring param)
		{
			const char* data = env->GetStringUTFChars(param, 0);
			log("JinCallBack :%s",data);
			MEWeiXinHelper::getInstance()->onWxLoginFail(data);
			env->ReleaseStringUTFChars(param, data);
		}

		JNIEXPORT void JNICALL Java_org_cocos2dx_lua_Native_ApplyPayResultState (JNIEnv* env, jclass method, int iCode)
		{
			cocos2d::log("JinCallBack :%d",iCode);
			MEWeiXinHelper::getInstance()->onApplyPayResultState(iCode);
		}

		JNIEXPORT void JNICALL Java_org_cocos2dx_lua_Native_WxShareResultState(JNIEnv* env, jclass method, int iCode)
		{
			cocos2d::log("JinCallBack :%d", iCode);
			MEWeiXinHelper::getInstance()->onWxShareResultState(iCode);
		}

		JNIEXPORT void JNICALL Java_org_cocos2dx_lua_Native_WxPayResultState(JNIEnv* env, jclass method, int iCode)
		{
			cocos2d::log("JinCallBack :%d", iCode);
			MEWeiXinHelper::getInstance()->onWxPayResultState(iCode);
		}
#endif
	}

} 