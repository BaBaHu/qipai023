
#ifndef __LUA_LPACK_H_
#define __LUA_LPACK_H_

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//extern int luaopen_pack(lua_State *L);
#else
int luaopen_pack(lua_State *L);
#endif

#endif
