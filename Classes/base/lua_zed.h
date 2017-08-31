
#ifndef __LUA_ZEB_H_
#define __LUA_ZEB_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "lua.h"
#include "lauxlib.h"

#ifdef __cplusplus
}
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//extern int luaopen_zed(lua_State *L);
#else
extern int luaopen_zed(lua_State *L);
#endif

#endif // __LUA_ZEB_H_

