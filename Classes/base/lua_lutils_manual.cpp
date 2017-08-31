#include "lua_lutils_manual.h"
#include "CCLuaEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#if __cplusplus
//extern "C" {
#endif
extern int luaopen_crypt(lua_State *L);
extern int luaopen_zed(lua_State *L);
extern int luaopen_zlib(lua_State *L);
extern int luaopen_pack(lua_State *L);
extern int luaopen_xxtea(lua_State *L);
#else
#if __cplusplus
extern "C" {
#endif
    
#include "lua_zlib.h"
#include "lua_xxtea.h"
#include "lpack.h"
#include "lua_crypt.h"
#include "lua_zed.h"
#endif
static luaL_Reg luax_exts[] = {
	{"crypt", luaopen_crypt},
	{"zed", luaopen_zed},
    {"zlib", luaopen_zlib},
    {"pack", luaopen_pack},
    {"xxtea", luaopen_xxtea},
    {NULL, NULL}
};
    
void luaopen_lua_utils(lua_State *L)
{
    // load extensions
    luaL_Reg* lib = luax_exts;
    lua_getglobal(L, "package");
    lua_getfield(L, -1, "preload");
    for (; lib->func; lib++)
    {
        lua_pushcfunction(L, lib->func);
        lua_setfield(L, -2, lib->name);
    }
    lua_pop(L, 2);
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#if __cplusplus
//} // extern "C"
#endif
#else
#if __cplusplus
} // extern "C"
#endif
#endif


int register_lutils_module(lua_State* L)
{
    lua_getglobal(L, "_G");
    if (lua_istable(L,-1))//stack:...,_G,
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        luaopen_lua_utils(L);
#endif
    }
    lua_pop(L, 1);
    return 1;
}