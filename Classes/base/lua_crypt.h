//
//  lua-crypt.h
//  Chocolate
//
//  Created by Andres Lee on 15/3/26.
//
//

#ifndef __SKYLINE__lua_crypt__
#define __SKYLINE__lua_crypt__


#ifdef __cplusplus
extern "C" {
#endif

#include "lua.h"
#include "lauxlib.h"

#ifdef __cplusplus
}
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//extern int luaopen_crypt(lua_State *L);
#else
extern int luaopen_crypt(lua_State *L);
#endif

#endif /* defined(__SKYLINE__lua_crypt__) */
