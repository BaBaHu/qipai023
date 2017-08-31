#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "lua_module_register.h"
#include "plazz/ui/MTNotification.h"
#include "YvVoiceManager.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_LINUX)
#include "ide-support/CodeIDESupport.h"
#endif

#if (COCOS2D_DEBUG > 0) && (CC_CODE_IDE_DEBUG_SUPPORT > 0)
#include "runtime/Runtime.h"
#include "ide-support/RuntimeLuaImpl.h"
#endif

using namespace CocosDenshion;
USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate()
{
	m_dispathMsgNode = NULL;
}

AppDelegate::~AppDelegate()
{
	if (m_dispathMsgNode != NULL)
	{
		m_dispathMsgNode->stopDispatch();
		m_dispathMsgNode->release();
		m_dispathMsgNode = NULL;
	}
    SimpleAudioEngine::end();
	MTNotification::purge();
#if (COCOS2D_DEBUG > 0) && (CC_CODE_IDE_DEBUG_SUPPORT > 0)
    // NOTE:Please don't remove this call if you want to debug with Cocos Code IDE
    RuntimeEngine::getInstance()->end();
#endif

}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages,
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // set default FPS
    Director::getInstance()->setAnimationInterval(1.0 / 60.0f);

    // register lua module
    auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    lua_State* L = engine->getLuaStack()->getLuaState();
    lua_module_register(L);
    
    register_all_packages();

    LuaStack* stack = engine->getLuaStack();
    stack->setXXTEAKeyAndSign("ff06ff770b0c3f12ffffff51ff32ff47", strlen("ff06ff770b0c3f12ffffff51ff32ff47"), "XXTEA", strlen("XXTEA"));
    
	Director::getInstance()->getScheduler()->schedule(schedule_selector(MTNotification::post),MTNotification::shared(),(float)(1.0 / 60.0), false);
	
#if (COCOS2D_DEBUG > 0) && (CC_CODE_IDE_DEBUG_SUPPORT > 0)
	// NOTE:Please don't remove this call if you want to debug with Cocos Code IDE
	auto runtimeEngine = RuntimeEngine::getInstance();
	runtimeEngine->addRuntime(RuntimeLuaImpl::create(), kRuntimeEngineLua);
	runtimeEngine->start();
#else
	if (engine->executeScriptFile("src/main.lua"))
	{
		return false;
	}
#endif

	if (m_dispathMsgNode == NULL)
	{
		m_dispathMsgNode = DispatchMsgNode::create();
		m_dispathMsgNode->retain();
		m_dispathMsgNode->startDispatch();
	}
	YvVoiceManager::GetInstance()->Init();

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

	if (ScriptEngineManager::getInstance()->getScriptEngine() != nullptr) {
		auto engine = LuaEngine::getInstance();
		engine->executeGlobalFunction("applicationDidEnterBackground");
	}
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();

	if (ScriptEngineManager::getInstance()->getScriptEngine() != nullptr) {
		auto engine = LuaEngine::getInstance();
		engine->executeGlobalFunction("applicationWillEnterForeground");
	}
}