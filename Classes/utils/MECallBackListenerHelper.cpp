#include "MECallBackListenerHelper.h"
#include "MELog.h"

static MECallBackListenerHelper *g_sharedCallBackListenerHelper = NULL;

MECallBackListenerHelper::MECallBackListenerHelper()
{
	m_mapLuaHandler.clear();
}

MECallBackListenerHelper::~MECallBackListenerHelper()
{
	m_mapLuaHandler.clear();
	CCLOG("cocos2d: deallocing MECollideListenerHelper.");
}

MECallBackListenerHelper * MECallBackListenerHelper::getInstance()
{
	if (g_sharedCallBackListenerHelper == NULL)
		g_sharedCallBackListenerHelper = new MECallBackListenerHelper();
	return g_sharedCallBackListenerHelper;
}

void MECallBackListenerHelper::purge()
{
	if (g_sharedCallBackListenerHelper)
	{
		delete g_sharedCallBackListenerHelper;
		g_sharedCallBackListenerHelper = NULL;
	}
}

void MECallBackListenerHelper::registerScriptCallBackHandler(std::string strHandler, int luaHandler)
{
	MELOG(MELOG_INFO, "[LUA] registerScriptMatchVsHandler script handler: %s,%d\n", strHandler.c_str(), luaHandler);
	if ( m_mapLuaHandler.find(strHandler) != m_mapLuaHandler.end() )
	{
		unregisterScriptCallBackHandler(strHandler);
	}
	m_mapLuaHandler[strHandler] = luaHandler;
}

void MECallBackListenerHelper::unregisterScriptCallBackHandler(std::string strHandler)
{
	MELOG(MELOG_INFO, "[LUA] unregisterScriptMatchVsHandler script handler: %s\n", strHandler.c_str());
	if (m_mapLuaHandler.find(strHandler) != m_mapLuaHandler.end())
	{
		m_mapLuaHandler.erase(strHandler);
	}
}

LUA_FUNCTION MECallBackListenerHelper::getHandler(std::string strHandler)
{
	if (m_mapLuaHandler.find(strHandler) != m_mapLuaHandler.end())
	{
		return m_mapLuaHandler[strHandler];
	}
	return 0;
}