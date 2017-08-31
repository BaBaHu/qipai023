/**
*  $Id: md5.h,v 1.2 2006/03/03 15:04:49 tomas Exp $
*  Cryptographic module for Lua.
*  @author  Roberto Ierusalimschy
*/


#ifndef md5_h
#define md5_h

#define HASHSIZE       16

#if __cplusplus
extern "C" {
#endif

void md5 (const char *message, long len, char *output);

#if __cplusplus
}
#endif


#endif
