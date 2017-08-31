#include "Convert.h"

#include "cocos2d.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "iconv.h"
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "libiconv/include/iconv.h"

#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "iconv.h"
#endif
//////////////////////////////////////////////////////////////////////////

/**
 * 计算utf8字符串长度
 * @param utf8 utf8字符串 
 * @return 字符串长度
 */
int u8len(const std::string& str)
{
	int i = 0, j = 0;
	while (str[i]) {
		if ((str[i] & 0xc0) != 0x80) j++;
		i++;
	}
	return j;
}

int u8cmp(const std::string& str1, const std::string& str2)
{
    unsigned int len1=str1.size();
    unsigned int len2=str2.size();
    unsigned int len = (len1<len2) ? len1 : len2;   
   
    int ret = memcmp(&str1[0],&str2[0],len);   
    if(ret == 0){   
        if(len1 > len2) ret = 1;   
        else if(len1 < len2) ret = -1;   
    }   
    return ret;   
}

/**
 * 计算ucs2字符串长度
 * @param ucs2 ucs2字符串 
 * @return 字符串长度
 */
int u2len(const std::string& s)
{
	const unsigned short* ucs2 = (const unsigned short*)&s[0];

	int i = 0;
	while (ucs2[i] != 0)
	{
		char c0 = ucs2[i]&0xff;
		char c1 = ucs2[i]>>8&0xff;

		if (c0 == '\0' && c1 == '\0')
			break;
		++i;
	}

	return i;
}

/////////////////////////////////////////////////////////////////////////////
static int code_convert(const char *from_charset, const char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	iconv_t cd;
    const char *temp = inbuf;
    const char **pin = &temp;
    char **pout = &outbuf;
    //memset(outbuf,0,outlen);
    cd = iconv_open(to_charset,from_charset);
    if(cd==0) return -1;
	if (-1 == iconv(cd, const_cast<char**>(pin), &inlen, pout, &outlen)) return -1;
    iconv_close(cd);
    return 0;
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	iconv_t cd;
	const char *temp = inbuf;
	const char **pin = &temp;
	char **pout = &outbuf;
	//memset(outbuf,0,outlen);
	cd = iconv_open(to_charset,from_charset);
	if(cd==0) return -1;
	if(-1 == iconv(cd, (char**)pin, &inlen, pout, &outlen)) return -1;
	iconv_close(cd);
	return 0;
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	iconv_t cd;
	const char *temp = inbuf;
	const char **pin = &temp;
	char **pout = &outbuf;
	//memset(outbuf,0,outlen);
	cd = iconv_open(to_charset,from_charset);
	if(cd==0) return -1;
	if(-1==iconv(cd,(char**)pin,&inlen,pout,&outlen)) return -1;
	iconv_close(cd);
	return 0;
#endif
    return -1;
}
     
/*UTF8转为gbk*/
std::string u2a(const std::string& s)
{
    size_t inlen = s.size();
	std::string strRet;
    strRet.resize(inlen * 2 + 2);

   if(code_convert("UTF-8", "GBK", &s[0], inlen, &strRet[0], strRet.size()))
       return s;

    return strRet;
}

/*gbk转为UTF8*/
std::string a2u(const std::string& s)
{
	size_t inlen = s.size();
	std::string strRet;
    strRet.resize(inlen * 2 + 2);

    if(code_convert("GBK", "UTF-8", &s[0], inlen, &strRet[0], strRet.size()))
       return s;
    return strRet;
}

/*gbk转为UTF16*/
std::string a2l(const std::string& s)
{
	size_t inlen = s.size();
	std::string strRet;
	strRet.resize(inlen * 2 + 2);

	if(code_convert("GBK", "UTF-16LE", &s[0], inlen, &strRet[0], strRet.size()))
		return s;
	return strRet;
}

/*utf16转为UTF8*/
std::string l2u(const std::string& s)
{
	size_t inlen = u2len(s);
	std::string strRet;
    strRet.resize(inlen * 4 + 1, '\0');

    if(code_convert("UTF-16LE", "UTF-8", &s[0], inlen*2, &strRet[0], strRet.size()))
		return s;
    return strRet;
}

/*UTF8转为utf16*/
std::string u2l(const std::string& s)
{
	return a2l(u2a(s));
}

std::string string_To_UTF8(const std::string &str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴  
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}

std::string UTF8_To_string(const std::string & str)
{
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴  
	memset(pwBuf, 0, nwLen * 2 + 2);

	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	memset(pBuf, 0, nLen + 1);

	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr = pBuf;

	delete[]pBuf;
	delete[]pwBuf;

	pBuf = NULL;
	pwBuf = NULL;

	return retStr;
}