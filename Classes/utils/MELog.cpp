#include "MELog.h"
#include "MEFileUtil.h"

#if  (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "external/curl/include/ios/curl/curl.h"
#elif  (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "external/curl/include/android/curl/curl.h"
#else
#include "curl/curl.h"
#pragma comment(lib,"libcurl_imp.lib")
#endif

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

MELogUtil* MELogUtil::instance = NULL;
MELogUtil* MELogUtil::sharedLogManager()
{
	if(instance == NULL)
	{
		instance = new MELogUtil();
		instance->init();
	}
	return instance;
}

void MELogUtil::purge()
{
	CC_SAFE_DELETE(instance);
}

MELogUtil::MELogUtil():
	m_canWriteError(true),
	m_canWriteInfo(false),
	m_canWriteWarning(false),
	m_szCurTime(""),
	m_userName(""),
	m_strPath(""),
	bIsUpload(false)
{

}

MELogUtil::~MELogUtil()
{
}

bool MELogUtil::init()
{
	std::string path =  FileUtils::getInstance()->getWritablePath() + "log";
	setLogPath(path.c_str());
	return true;
}

void MELogUtil::setLogPath(const char* szPath)
{
	m_strPath = szPath;
	if (m_strPath.size() > 0 && m_strPath[m_strPath.size() - 1] != '/')
	{
		m_strPath.append("/");
	}
	MEFileUtil::createDir(m_strPath.c_str());
}
const char* MELogUtil::getLogPath()
{
	return m_strPath.c_str();
}

char* MELogUtil::format(char* szBuf)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	WCHAR wszBuf[MAX_LOG_LEN] = {0};
	MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, wszBuf, sizeof(wszBuf));
	OutputDebugStringW(wszBuf);
	OutputDebugStringA("\n");

	WideCharToMultiByte(CP_ACP, 0, wszBuf, sizeof(wszBuf), szBuf, sizeof(szBuf), NULL, FALSE);
#endif
	return szBuf;
}

void MELogUtil::print(int nType, char* pszFormat, ...)
{
	char szBuf[MAX_LOG_LEN];

	va_list ap;
	va_start(ap, pszFormat);
	vsnprintf(szBuf, MAX_LOG_LEN, pszFormat, ap);
	va_end(ap);

	char* pszBuf = format(szBuf);

	if(m_szCurTime == "")
		m_szCurTime = getCurrentTimeString2();

	switch(nType)
	{
	case MELOG_WARNING:
		{
			warningHandler(pszBuf);
			break;
		}
	case MELOG_ERROR:
		{
			errorHandler(pszBuf);
			break;
		}
	case MELOG_INFO:
		{
			infoHandler(pszBuf);
			break;
		}
	}
}

void MELogUtil::errorHandler(const char* szOut)
{
	//log("[ERROR]\t%s", szOut);
	if (getCanWriteError())
	{
		std::string path = m_strPath;
		path += m_szCurTime;
		path += "_error.log";
		FILE* f = fopen(path.c_str(), "a");
		if (f != NULL)
		{
			fprintf(f, "[ERROR %s]\t%s", getCurrentTimeString().c_str(), szOut);
			fclose(f);
			//if (bIsUpload)
			//	MEFtpUpload(path);
		}
		else
		{
			printf("%s %s %s\n", "open File", path.c_str(), "Error");
		}
	}
}

void MELogUtil::infoHandler(const char* szOut)
{
	//log("[INFO]\t%s", szOut);
	if (getCanWriteInfo())
	{
		std::string path = m_strPath;
		path += m_szCurTime;
		path += "_info.log";
		FILE* f = fopen(path.c_str(), "a");
		if (f != NULL)
		{
			fprintf(f, "[INFO %s]\t%s", getCurrentTimeString().c_str(), szOut);
			fclose(f);
		}
		else
		{
			MEP("%s %s %s\n", "open File", path.c_str(), "Error");
		}
	}
}

void MELogUtil::warningHandler(const char* szOut)
{
	//log("[WARNING]\t%s", szOut);
	if (getCanWriteWarning())
	{
		std::string path = m_strPath;
		path += m_szCurTime;
		path += "_warning.log";
		FILE* f = fopen(path.c_str(), "a");
		if (f != NULL)
		{
			fprintf(f, "[WARNING %s]\t%s", getCurrentTimeString().c_str(), szOut);
			fclose(f);
		}
		else
		{
			MEP("%s %s %s\n", "open File", path.c_str(), "Error");
		}
	}
}


std::string MELogUtil::getCurrentTimeString()
{
	time_t t = time(0);
	tm *tblock = localtime(&t);
	std::string ret;
	char szTime[30];
	sprintf(szTime, "%d-%d-%d %d:%d:%d", tblock->tm_year + 1900, tblock->tm_mon+1, tblock->tm_mday,tblock->tm_hour, tblock->tm_min, tblock->tm_sec);
	return szTime;
}

std::string MELogUtil::getCurrentTimeString2()
{
	time_t t = time(0);
	tm *tblock = localtime(&t);
	std::string ret;
	char szTime[30];
	sprintf(szTime, "%d_%d_%d_%d_%d_%d", tblock->tm_year + 1900, tblock->tm_mon+1, tblock->tm_mday,tblock->tm_hour, tblock->tm_min, tblock->tm_sec);
	return szTime;
}

std::string MELogUtil::getCurrentDateString(std::string &szTime)
{
	int len = szTime.size();
	std::string ret;
	do
	{
		CC_BREAK_IF(len < 10);
		int idx = szTime.find_last_of('/');
		ret += szTime.substr(0, idx);
		int i = 0, len = ret.size();
		while (i < len)
		{
			if (ret[i++] == '/') ret[i-1] = '_';
		}
	}while(0);
	return ret;
}

void MELogUtil::meprint(char* pszFormat, ...)
{
	char szBuf[MAX_LOG_LEN];
	va_list ap;
	va_start(ap, pszFormat);
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		vsnprintf_s(szBuf, MAX_LOG_LEN, MAX_LOG_LEN, pszFormat, ap);
#else
		vsnprintf(szBuf, MAX_LOG_LEN, pszFormat, ap);
#endif
	va_end(ap);

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	WCHAR wszBuf[MAX_LOG_LEN] = {0};
	MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, wszBuf, sizeof(wszBuf));
	OutputDebugStringW(wszBuf);

	WideCharToMultiByte(CP_ACP, 0, wszBuf, sizeof(wszBuf), szBuf, sizeof(szBuf), NULL, FALSE);
	printf("%s", szBuf);
#endif	
}


/* Note: if you want this example to work on Windows with libcurl as a 
DLL, you MUST also provide a read callback with CURLOPT_READFUNCTION.
Failing to do so will give you a crash since a DLL may not use the 
variable's memory when passed in to it from an app like this. */
static size_t readCallback( void *ptr, size_t size, size_t nmemb, void *stream )
{
	/*curl_off_t nread;
	size_t retcode = fread(ptr, size, nmemb, (FILE*)stream);
	nread = (curl_off_t)retcode;
	return retcode;
	*/
	return 0;
}

//void MELogUtil::MEFtpUpload( std::string path )
//{
//	bIsUpload = false;
//	CURL *curl;
//	CURLcode res;
//	FILE *hd_src;
//	struct stat file_info;
//	curl_off_t fsize;
//
//	std::string ftpPath = "ftp://192.168.2.39/upfiles/mobilelog/win/";
//#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
//	ftpPath = "ftp://ec.7.com/mobilelog/ios/";
//#endif
//	ftpPath += m_userName;
// 	ftpPath += getCurrentDateString(m_szCurTime);
// 	ftpPath += "_error.log";
//
//	if (stat(path.c_str(), &file_info)) {
//		CCLOG("get file info error");
//		return ;
//	}
//	fsize = (curl_off_t)file_info.st_size;
//	hd_src = fopen(path.c_str(), "rb");
//
//	curl_global_init(CURL_GLOBAL_ALL);
//
//	curl = curl_easy_init();
//	if(curl){
//		/* we want to use our own read function */
//		curl_easy_setopt(curl, CURLOPT_READFUNCTION, readCallback);
//		/* enable uploading */
//		curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
//		/* specify targe */
//		curl_easy_setopt(curl, CURLOPT_URL, ftpPath.c_str());
//
//		/* now specify which file to upload */
//		curl_easy_setopt(curl, CURLOPT_READDATA, hd_src);
//		/* Set the size of the file to upload(optional). If you give a *_LARGE
//		   option you MUST make sure that the type of the passed-in argument is a 
//		   curl_off_t. If you use CURLOPT_INFLESIZE (without _LARGE) you must
//		   make sure that to pass in a type 'long' argument. */
//		curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)fsize);
//
//		curl_easy_setopt(curl, CURLOPT_USERPWD, "ftpuser:ec<>123456");
//
//		/* create dir permission */
//		curl_easy_setopt(curl, CURLOPT_FTP_CREATE_MISSING_DIRS, 1);
//
//		CCLOG("\n-----------------ftp uploading.-----------------\n");
//
//		/* Now run off and do what you've been told! */
//		res = curl_easy_perform(curl);
//
//		/* Check for errors */
//		if (res != CURLE_OK)
//			CCLOG("\nftp upload failed.\ncurl_easy_perform() failed: %s\n", curl_easy_strerror(res));
//		else
//			CCLOG("\n-----------------ftp upload success.-----------------\n");
//
//		/* always cleanup */
//		curl_easy_cleanup(curl);
//	}
//	fclose(hd_src);
//	curl_global_cleanup();
//	bIsUpload = true;
//	
//}

//void MELogUtil::MEFtpSetUserName( std::string name )
//{
//	m_userName = name + "/";
//}

//void MELogUtil::MEFtpSetUpload( bool bRet )
//{
//	bIsUpload = bRet;
//}
