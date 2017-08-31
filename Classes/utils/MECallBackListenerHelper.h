#ifndef __MECALLBACKLISTENERHELPER_H__
#define __MECALLBACKLISTENERHELPER_H__

#include "CCLuaEngine.h"
#include <map>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class MECallBackListenerHelper
{
public:
	static MECallBackListenerHelper * getInstance();
	static void purge();

	void registerScriptCallBackHandler(std::string strHandler, LUA_FUNCTION luaHanlder);
	void unregisterScriptCallBackHandler(std::string strHandler);
	LUA_FUNCTION getHandler(std::string strHandler);

protected:
	MECallBackListenerHelper();
	virtual ~MECallBackListenerHelper();
 protected:
	 std::map<std::string,LUA_FUNCTION> m_mapLuaHandler;
};

#endif //__MEMATCHVSLISTENERHELPER_H__