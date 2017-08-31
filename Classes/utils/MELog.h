#ifndef __ME_LOG_H__
#define __ME_LOG_H__

#include "cocos2d.h"
USING_NS_CC;

#define MAX_LOG_LEN 1024 << 5

#define MELOG_ERROR		1
#define MELOG_INFO		2
#define MELOG_WARNING	3

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	#define MEP CCLog
#else
	#ifdef COCOS2D_DEBUG
		#define MEP(fmt,...) MEPLOG(fmt, ##__VA_ARGS__);
	#else
		#define MEP(fmt,...) 
	#endif
#endif

#define MEERR(fmt,...)  MELOG(MELOG_ERROR, fmt,##__VA_ARGS__)
#define MEINFO(fmt,...) MELOG(MELOG_INFO, fmt, ##__VA_ARGS__)
#define MEWARN(fmt,...) MELOG(MELOG_WARNING, fmt, ##__VA_ARGS__)


#define MELOG(tp,fmt,...) MELogUtil::sharedLogManager()->print(tp,fmt,##__VA_ARGS__)
#define MEPLOG(fmt,...)	  MELogUtil::sharedLogManager()->meprint(fmt,##__VA_ARGS__)

class MELogUtil
{
public:
	static MELogUtil* sharedLogManager();
	static void	purge();

	void setLogPath(const char* szPath);
	const char* getLogPath();

	//void MEFtpUpload(std::string szFileName);
	//void MEFtpSetUserName(std::string szName);
	//void MEFtpSetUpload(bool bRet);

	char* format(char* szBuf);
	void print(int nType, char* pszFormat, ...);
	void meprint(char* pszFormat, ...);
protected:
	void errorHandler(const char* output);
	void infoHandler(const char* output);
	void warningHandler(const char* output);

	CC_SYNTHESIZE_PASS_BY_REF(bool, m_canWriteError, CanWriteError);
	CC_SYNTHESIZE_PASS_BY_REF(bool, m_canWriteInfo, CanWriteInfo);
	CC_SYNTHESIZE_PASS_BY_REF(bool, m_canWriteWarning, CanWriteWarning);

	std::string getCurrentTimeString();
	std::string getCurrentTimeString2();
	std::string getCurrentDateString(std::string &szTime);
private:
	MELogUtil();
	~MELogUtil();
	bool init();
private:
	std::string m_szCurTime;
	std::string m_userName;
	std::string m_strPath;
	bool bIsUpload;
	static MELogUtil* instance;
};

//
static inline void _MELog(int tp, const char* msg){MELogUtil::sharedLogManager()->print(tp, "%s\n", msg);}
static inline void MELOGERROR(const char* msg){_MELog(MELOG_ERROR, msg);}
static inline void MELOGWARNING(const char* msg){_MELog(MELOG_WARNING, msg);}
static inline void MELOGINFO(const char* msg){_MELog(MELOG_INFO, msg);}

#endif // __ME_LOG_H__