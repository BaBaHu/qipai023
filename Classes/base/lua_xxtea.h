
#ifndef __luasock__lua_xxtea__
#define __luasock__lua_xxtea__

#ifdef __cplusplus
extern "C" {
#endif

#include "lua.h"
#include "lauxlib.h"
    
#ifdef __cplusplus
}
#endif

#include <stddef.h> /* for size_t & NULL declarations */
#if defined(_MSC_VER)
typedef unsigned __int32 xxtea_long;
#else
#if defined(__FreeBSD__) && __FreeBSD__ < 5
#include <inttypes.h>
#else
#include <stdint.h>
#endif
typedef uint32_t xxtea_long;
#endif
#define XXTEA_MX (z >> 5 ^ y << 2) + (y >> 3 ^ z << 4) ^ (sum ^ y) + (k[p & 3 ^ e] ^ z)
#define XXTEA_DELTA 0x9E3779B9

/* register library */
#ifdef __cplusplus
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//LUALIB_API int luaopen_xxtea( lua_State *L );
#else
LUALIB_API int luaopen_xxtea( lua_State *L );
#endif
#endif

//unsigned char *xxtea_encrypt(unsigned char *data, xxtea_long data_len, unsigned char *key, xxtea_long key_len, xxtea_long *ret_length);
//unsigned char *xxtea_decrypt(unsigned char *data, xxtea_long data_len, unsigned char *key, xxtea_long key_len, xxtea_long *ret_length);

#endif /* defined(__luasock__lua_xxtea__) */


