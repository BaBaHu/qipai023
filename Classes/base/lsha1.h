#ifndef __SKYLINE__lua_sha1__
#define __SKYLINE__lua_sha1__


#if __cplusplus
extern "C" {
#endif
#include "lauxlib.h"

	// defined in lsha1.c
	int lsha1(lua_State *L);
	int lhmac_sha1(lua_State *L);

#if __cplusplus
}
#endif

#endif /* defined(__SKYLINE__lua_sha1__) */