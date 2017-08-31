#ifndef _types_H_
#define _types_H_

//////////////////////////////////////////////////////////////
#include <assert.h>
#include <stdio.h>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <deque>
#include <iomanip>
#include <list>
#include <sstream>

#include <assert.h>
#include <stdarg.h>

#ifndef ASSERT
#define ASSERT(f) assert(f)
#endif

///////////////////////////////////////////////////////////////////////////////////////

typedef signed char			int8;
typedef signed short		int16;
typedef signed int			int32;
typedef long long			int64;

typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef unsigned long long	uint64;

typedef unsigned char		byte;
typedef unsigned int		uint;
typedef unsigned short		word;
typedef uint32				dword;
typedef long long			longlong;
typedef unsigned long long	handle;
#define TRUE				1
#define FALSE				0


#ifdef _WIN32
#define LLSTRING "%I64d"
#define ULLSTRING "%U64d"
#else
#define LLSTRING "%lld"
#define ULLSTRING "%llu"
#endif

#define makeword(a, b)      ((word)(((byte)(((longlong)(a)) & 0xff)) | ((word)((byte)(((longlong)(b)) & 0xff))) << 8))
#define makelong(a, b)      ((long)(((word)(((longlong)(a)) & 0xffff)) | ((dword)((word)(((longlong)(b)) & 0xffff))) << 16))
#define loword(l)           ((word)(((longlong)(l)) & 0xffff))
#define hiword(l)           ((word)((((longlong)(l)) >> 16) & 0xffff))
#define lobyte(w)           ((byte)(((longlong)(w)) & 0xff))
#define hibyte(w)           ((byte)((((longlong)(w)) >> 8) & 0xff))

//////////////////////////////////////////////////////////////////////////
// 功能函数
inline std::string toString(int value)
{
	static char szTemp[256];
	sprintf(&szTemp[0], "%d", value);
	return szTemp;
}

inline std::string toString(int64 value)
{
	static char szTemp[256];
	sprintf(&szTemp[0], LLSTRING, value);
	return szTemp;
}

static std::string stringFormatC(const char* format, ...)
{
	static char szTemp[1024];
	va_list vlist;
	va_start(vlist, format);
	vsprintf(&szTemp[0], format, vlist);
	va_end(vlist);
	return szTemp;
} // 

#define stringFormat(format, ...) stringFormatC(format.c_str(), ##__VA_ARGS__)

template<typename T>
inline T tmin(const T& a, const T& b)
{
	return a < b ? a : b;
}

template<typename T>
inline T tmax(const T& a, const T& b)
{
	return a < b ? b : a;
}

//////////////////////////////////////////////////////////////////////////
// 宏定义
#define countarray(ary)		(sizeof(ary)/sizeof(ary[0]))
#define zeromemory(x, size)	memset(x, 0, size)

///////////////////////////////////////////////////////////////////////////////////////

#endif // _types_H_