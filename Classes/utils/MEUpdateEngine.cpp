/****************************************************************************
 版权:
 作者: wpj
 日期：2015-01-09
 内容: 在线升级数据，下载文件为zip，下载后自动解压（解压后自动删除zip文件）,该类支持断点续传.
 ****************************************************************************/

#include "MEUpdateEngine.h"
#include "MECallBackListenerHelper.h"
#include "MELog.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8) && (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#else
#include <io.h>
#endif

#include <stdio.h>
#include <vector>
#include <thread>
#include "cocos2d.h"
#if  (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "external/curl/include/ios/curl/curl.h"
#elif  (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "external/curl/include/android/curl/curl.h"
#else
#include "curl/curl.h"
#pragma comment(lib,"libcurl_imp.lib")
#endif

#ifdef MINIZIP_FROM_SYSTEM
#include <minizip/unzip.h>
#else // from our embedded sources
#include "unzip/unzip.h"
#endif

USING_NS_CC;
using namespace std;

#define KEY_OF_VERSION   "current-version-code"
#define KEY_OF_BASE_VERSION   "current-baseversion-code"
#define KEY_OF_DOWNLOADED_VERSION    "downloaded-version-code"
/* 下载文件名 */
#define TEMP_PACKAGE_FILE_NAME "upgrade-manager-file-package.zip"
#define TEMP_DOWN_PACKAGE_PATH_NAME "/sdcard/com.yibo98.weishui/"
#define BUFFER_SIZE    8192
#define MAX_FILENAME   512

#define LOW_SPEED_LIMIT 1L
#define LOW_SPEED_TIME 5L

MEUpdateManagerDelegateProtocol g_delegate;

MEUpdateEngine::MEUpdateEngine(const char* packageUrl /* = NULL */, const char* versionFileUrl /*= NULL*/, const char* storagePath /* = NULL */):
_packageUrl(packageUrl),
_versionFileUrl(versionFileUrl),
_storagePath(storagePath),
_versionBaseFileUrl(""),
_baseversion(""),
_version(""),
_downPackageName(""),
_downloadedVersion(""),
_delegate(&g_delegate),
_connectionTimeout(0),
_isDownloading(false),
_isDownpackage(false),
_curl(nullptr),
_shouldDeleteDelegateWhenExit(false),
m_lLocalFileLenth(0L)
{
	checkStoragePath();
}

MEUpdateEngine::~MEUpdateEngine()
{
	if (_shouldDeleteDelegateWhenExit)
    {
        delete _delegate;
    }
}

const char* MEUpdateEngine::getPackageUrl() const
{
	return _packageUrl.c_str();
}

void MEUpdateEngine::setPackageUrl(const char* packageUrl)
{
	_packageUrl = packageUrl;
}

const char* MEUpdateEngine::getVersionFileUrl() const
{
    return _versionFileUrl.c_str();
}

void MEUpdateEngine::setVersionFileUrl(const char *versionFileUrl)
{
    _versionFileUrl = versionFileUrl;
}


const char* MEUpdateEngine::getBaseVersionFileUrl() const
{
	return _versionBaseFileUrl.c_str();
}
    
void MEUpdateEngine::setBaseVersionFileUrl(const char* versionBaseFileUrl)
{
	_versionBaseFileUrl = versionBaseFileUrl;
}

const char* MEUpdateEngine::getStoragePath() const
{
	return _storagePath.c_str();
}

void MEUpdateEngine::setStoragePath(const char* storagePath)
{
	_storagePath = storagePath;
    checkStoragePath();
}


const char* MEUpdateEngine::getDownPackageStoragePath() const
{
	std::string apkPath = _storagePath + _downPackageName;
	return apkPath.c_str();
}

string MEUpdateEngine::getVersion()
{
    return UserDefault::getInstance()->getStringForKey(KEY_OF_VERSION);
}

void MEUpdateEngine::setVersion( const char* version)
{
	//MELOG(MELOG_INFO, "MEUpdateEngine::setVersion before = %s", version );
	UserDefault::getInstance()->setStringForKey(KEY_OF_VERSION, version);
	//MELOG(MELOG_INFO, "MEUpdateEngine::setVersion after = %s", getVersion().c_str() );
}

std::string MEUpdateEngine::getBaseVersion()
{
	return UserDefault::getInstance()->getStringForKey(KEY_OF_BASE_VERSION);
}

void MEUpdateEngine::setBaseVersion( const char* base_version)
{
	//MELOG(MELOG_INFO, "MEUpdateEngine::setVersion before = %s", base_version );
	UserDefault::getInstance()->setStringForKey(KEY_OF_BASE_VERSION, base_version);
	//MELOG(MELOG_INFO, "MEUpdateEngine::setVersion after = %s", getBaseVersion().c_str() );
}

void MEUpdateEngine::setDelegate(MEUpdateManagerDelegateProtocol *delegateProtocol)
{
	_delegate = delegateProtocol;
}

unsigned int MEUpdateEngine::getConnectionTimeout()
{
	return _connectionTimeout;
}

void MEUpdateEngine::setConnectionTimeout(unsigned int timeout)
{
	_connectionTimeout = timeout;
}

void MEUpdateEngine::checkStoragePath()
{
    if (_storagePath.size() > 0 && _storagePath[_storagePath.size() - 1] != '/')
    {
        _storagePath.append("/");
    }
	this->createStoragePath(_storagePath.c_str() );
}

// Multiple key names
static std::string keyWithHash( const char* prefix, const std::string& url )
{
    char buf[256];
    sprintf(buf,"%s%zd",prefix,std::hash<std::string>()(url));
    return buf;
}

// hashed version
std::string MEUpdateEngine::keyOfVersion() const
{
    return keyWithHash(KEY_OF_VERSION,_packageUrl);
}

// hashed version
std::string MEUpdateEngine::keyOfDownloadedVersion() const
{
    return keyWithHash(KEY_OF_DOWNLOADED_VERSION,_packageUrl);
}

static size_t getVersionCode(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    string *version = (string*)userdata;
    version->append((char*)ptr, size * nmemb);
    
    return (size * nmemb);
}

bool MEUpdateEngine::checkBaseVersion()
{
	if (_versionBaseFileUrl.size() == 0) return false;
    
	_curl = curl_easy_init();
    if (! _curl)
    {
        CCLOG("can not init curl");
        return false;
    }
    
    // Clear _version before assign new value.
    _baseversion.clear();
    
    CURLcode res;
    curl_easy_setopt(_curl, CURLOPT_URL, _versionBaseFileUrl.c_str());
    curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, getVersionCode);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &_baseversion);
    if (_connectionTimeout) curl_easy_setopt(_curl, CURLOPT_CONNECTTIMEOUT, _connectionTimeout);
    curl_easy_setopt(_curl, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(_curl, CURLOPT_LOW_SPEED_LIMIT, LOW_SPEED_LIMIT);
    curl_easy_setopt(_curl, CURLOPT_LOW_SPEED_TIME, LOW_SPEED_TIME);
	curl_easy_setopt(_curl, CURLOPT_FOLLOWLOCATION, 1 );
    res = curl_easy_perform(_curl);
    
    if (res != 0)
    {
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this]{
            if (this->_delegate)
                this->_delegate->onError(ErrorCode::NETWORK);
        });
        MELOG(MELOG_INFO, "can not get base version file content, error code is %d", res);
        curl_easy_cleanup(_curl);
        return false;
    }
    string recordedBaseVersion = this->getBaseVersion();
	MELOG(MELOG_INFO, "recordedBaseVersion = %s, _baseversion = %s", recordedBaseVersion.c_str(), _baseversion.c_str() );
    if (recordedBaseVersion != _baseversion)
    {
       _isDownpackage = true;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	   this->destroyTempDownPath(TEMP_DOWN_PACKAGE_PATH_NAME);
	   this->setStoragePath(TEMP_DOWN_PACKAGE_PATH_NAME);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC )
	   Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this]{
		   if (this->_delegate)
			   this->_delegate->onError(ErrorCode::IOSUPDATE);
	   });
	   MELOG(MELOG_INFO, "ios has big update, error code is \n");
	   curl_easy_cleanup(_curl);
	   return false;
#endif
    }
    MELOG(MELOG_INFO, "there is down package: %d", _isDownpackage);
    return true;
}

bool MEUpdateEngine::checkUpdate()
{
	if (_versionFileUrl.size() == 0) return false;
    
	_curl = curl_easy_init();
    if (! _curl)
    {
        CCLOG("can not init curl");
        return false;
    }
    
    // Clear _version before assign new value.
    _version.clear();
    
    CURLcode res;
    curl_easy_setopt(_curl, CURLOPT_URL, _versionFileUrl.c_str());
    curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, getVersionCode);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &_version);
    if (_connectionTimeout) curl_easy_setopt(_curl, CURLOPT_CONNECTTIMEOUT, _connectionTimeout);
    curl_easy_setopt(_curl, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(_curl, CURLOPT_LOW_SPEED_LIMIT, LOW_SPEED_LIMIT);
    curl_easy_setopt(_curl, CURLOPT_LOW_SPEED_TIME, LOW_SPEED_TIME);
	curl_easy_setopt(_curl, CURLOPT_FOLLOWLOCATION, 1 );
    res = curl_easy_perform(_curl);
    
    if (res != 0)
    {
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this]{
            if (this->_delegate)
                this->_delegate->onError(ErrorCode::NETWORK);
        });
        MELOG(MELOG_INFO, "can not get version file content, error code is %d", res);
        curl_easy_cleanup(_curl);
        return false;
    }
    
    string recordedVersion = this->getVersion();
	MELOG(MELOG_INFO, "recordedVersion = %s, _version = %s", recordedVersion.c_str(), _version.c_str() );
    if (recordedVersion == _version)
    {
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this]{
            if (this->_delegate)
                this->_delegate->onError(ErrorCode::NO_NEW_VERSION);
        });
        MELOG(MELOG_INFO, "there is not new version");
        // Set resource search path.
        setSearchPath();
        return false;
    }
    
    MELOG(MELOG_INFO, "there is a new version: %s", _version.c_str());
    return true;
}

void MEUpdateEngine::update()
{
 	if (_isDownloading) return;
 
 	_isDownloading = true;

	 // 1. Urls of package and version should be valid;
    // 2. Package should be a zip file.
	if (_versionFileUrl.size() == 0 ||
		_packageUrl.size() == 0 ||
        std::string::npos == _packageUrl.find(".zip"))
    {
        CCLOG("no version file url, or no package url, or the package is not a zip file");
        _isDownloading = false;
        return;
    }
	
	// Check base version.
 	if (! checkBaseVersion())
 	{
		_isDownloading = false;
 		return;
 	}

	// Check if there is a new version.
 	if (! checkUpdate())
 	{
		_isDownloading = false;
 		return;
 	}

	// Is package already downloaded?
	_downloadedVersion = UserDefault::getInstance()->getStringForKey(KEY_OF_DOWNLOADED_VERSION);

	auto t = std::thread(&MEUpdateEngine::downloadAndUncompress, this);
	t.detach();
}

void MEUpdateEngine::downloadAndUncompress()
{
	do
	{
		if (_downloadedVersion != _version)
        {
            if (! downLoad()) break;
            
            Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this]{
                UserDefault::getInstance()->setStringForKey(KEY_OF_DOWNLOADED_VERSION,this->_version.c_str());
                UserDefault::getInstance()->flush();
            });
        }

		// 解压zip文件.
		if (!uncompress())
		{
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this]
			{
				//解压失败，重置下载记录
				UserDefault::getInstance()->setStringForKey(KEY_OF_DOWNLOADED_VERSION, "");
				if (this->_delegate)
				{
					this->_delegate->onError(ErrorCode::UNCOMPRESS);
				}
			});
			break;
		}

		Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this] 
		{
			// Record new version code.
			this->setVersion(this->_version.c_str() );
            this->setBaseVersion(this->_baseversion.c_str() );

            // Unrecord downloaded version code.
            UserDefault::getInstance()->setStringForKey(KEY_OF_DOWNLOADED_VERSION, "");
            UserDefault::getInstance()->flush();
            
            // Set resource search path.
            this->setSearchPath();
            
            // Delete unloaded zip file.
            string zipfileName = this->_storagePath + TEMP_PACKAGE_FILE_NAME;
            if (remove(zipfileName.c_str()) != 0)
            {
                CCLOG("can not remove downloaded zip file %s", zipfileName.c_str());
            }
            
            if (this->_delegate) 
				this->_delegate->onSuccess();
		});
	} while (0);
	_isDownloading = false;
}

static size_t downLoadPackage(void *ptr, size_t size, size_t nmemb, void *userdata)
{
	FILE *fp = (FILE*)userdata;
	size_t written = fwrite(ptr, size, nmemb, fp);
	return written;
}

int updateManagerProgressFunc(void *ptr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded)
{
	static int percent = 0;
	auto manager = static_cast<MEUpdateEngine*>(ptr);
	int tmp = 0;
	if (0 < totalToDownload)
		tmp = (int)((nowDownloaded + manager->m_lLocalFileLenth) / (totalToDownload + manager->m_lLocalFileLenth) * 100);
	else
		tmp = (int)(nowDownloaded / totalToDownload * 100);

	if (percent != tmp)
	{
		percent = tmp;
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]
		{
			if (manager->_delegate)
				manager->_delegate->onProgress(percent);
		});
		CCLOG("downloading... %d%%", percent);
	}
	return 0;
}

bool MEUpdateEngine::downLoad()
{
	const string outFileName = _storagePath + TEMP_PACKAGE_FILE_NAME;
	CCLOG("downLoad path %s", outFileName.c_str());
	FILE *fp = NULL;
	if(0 == access(outFileName.c_str(), 0))
		fp = fopen(outFileName.c_str(), "ab+");// 以二进制形式追加
	else
		fp = fopen(outFileName.c_str(), "wb");// 二进制写

	// 如果文件初始化失败进行返回
	if (fp == NULL)
		return false;

	if (! fp)
	{
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this]
		{
			if (this->_delegate)
				this->_delegate->onError(ErrorCode::CREATE_FILE);
		});
		MELOG(MELOG_INFO, "can not create file %s", outFileName.c_str());
		return false;
	}

	m_lLocalFileLenth = getLocalFileLength();
	_curl = curl_easy_init();
	// Download pacakge
	CURLcode res;
	curl_easy_setopt(_curl, CURLOPT_URL, _packageUrl.c_str());//下载url
	curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, downLoadPackage);//写文件回调方法
	curl_easy_setopt(_curl, CURLOPT_WRITEDATA, fp); // 写入文件对象
	curl_easy_setopt(_curl, CURLOPT_NOPROGRESS, 0L);
	curl_easy_setopt(_curl, CURLOPT_PROGRESSFUNCTION, updateManagerProgressFunc);//下载进度回调方法
	curl_easy_setopt(_curl, CURLOPT_PROGRESSDATA, this);// 传入本类对象
	curl_easy_setopt(_curl, CURLOPT_NOSIGNAL, 1L);
	curl_easy_setopt(_curl, CURLOPT_LOW_SPEED_LIMIT, 1L);//设置“低限速”
	curl_easy_setopt(_curl, CURLOPT_LOW_SPEED_TIME, 5L);//设置“低限时”
	curl_easy_setopt(_curl, CURLOPT_FOLLOWLOCATION, 1 );//设置成跟随跳转
	//curl_easy_setopt(_curl, CURLOPT_RESUME_FROM, m_lLocalFileLenth);  // 从本地大小位置进行请求数据 这是个坑，不能下载！！！
	//curl_easy_setopt(_curl, CURLOPT_TIMEOUT, _connectionTimeout);//超时这个数额几秒钟后读操作

	res = curl_easy_perform(_curl);
	curl_easy_cleanup(_curl);
	if (res != 0)
	{
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this]
		{
			if (this->_delegate)
				this->_delegate->onError(ErrorCode::NETWORK);
		});
		MELOG(MELOG_INFO, " error when download package");
		fclose(fp);
		return false;
	}

	CCLOG(" succeed downloading package %s", _packageUrl.c_str());

	fclose(fp);
	return true;
}

long MEUpdateEngine::getLocalFileLength()
{
	string filePathName = _storagePath + TEMP_PACKAGE_FILE_NAME;
	FILE *fp = fopen(filePathName.c_str(), "r");
	fseek(fp, 0, SEEK_END);
	long length = ftell(fp);
	fclose(fp);
	CCLOG("file length %ld", length);
	return length;
}

void MEUpdateEngine::setSearchPath()
{
	vector<string> searchPaths = FileUtils::getInstance()->getSearchPaths();
	vector<string>::iterator iter = searchPaths.begin();
	searchPaths.insert(iter, _storagePath);
	FileUtils::getInstance()->setSearchPaths(searchPaths);
}


bool MEUpdateEngine::uncompress()
{
	// Open the zip file
	string outFileName = _storagePath + TEMP_PACKAGE_FILE_NAME;
	unzFile zipfile = unzOpen(outFileName.c_str());
	if (! zipfile)
	{
		CCLOG("can not open downloaded zip file %s", outFileName.c_str());
		return false;
	}

	// Get info about the zip file
	unz_global_info global_info;
	if (unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
	{
		CCLOG("can not read file global info of %s", outFileName.c_str());
		unzClose(zipfile);
		return false;
	}

	// Buffer to hold data read from the zip file
	char readBuffer[BUFFER_SIZE];

	CCLOG("start uncompressing");

	// Loop to extract all files.
	uLong i;
	for (i = 0; i < global_info.number_entry; ++i)
	{
		// Get info about current file.
		unz_file_info fileInfo;
		char fileName[MAX_FILENAME];
		if (unzGetCurrentFileInfo(zipfile,
			&fileInfo,
			fileName,
			MAX_FILENAME,
			nullptr,
			0,
			nullptr,
			0) != UNZ_OK)
		{
			CCLOG("can not read file info");
			unzClose(zipfile);
			return false;
		}
		if (_isDownpackage)
		{
			_downPackageName = fileName;
		}
		const string fullPath = _storagePath + fileName;

		// Check if this entry is a directory or a file.
		const size_t filenameLength = strlen(fileName);
		if (fileName[filenameLength-1] == '/')
		{
			// Entry is a direcotry, so create it.
			// If the directory exists, it will failed scilently.
			if (!createDirectory(fullPath.c_str()))
			{
				CCLOG("can not create directory %s", fullPath.c_str());
				unzClose(zipfile);
				return false;
			}
		}
		else
		{
			//There are not directory entry in some case.
			//So we need to test whether the file directory exists when uncompressing file entry
			//, if does not exist then create directory
			const string fileNameStr(fileName);

			size_t startIndex=0;

			size_t index = fileNameStr.find("/",startIndex);

			while(index != std::string::npos)
			{
				const string dir=_storagePath + fileNameStr.substr(0,index);

				FILE *out = fopen(dir.c_str(), "r");

				if(!out)
				{
					if (!createDirectory(dir.c_str()))
					{
						CCLOG("can not create directory %s", dir.c_str());
						unzClose(zipfile);
						return false;
					}
					else
					{
						CCLOG("create directory %s",dir.c_str());
					}
				}
				else
				{
					fclose(out);
				}

				startIndex=index+1;

				index=fileNameStr.find("/",startIndex);

			}



			// Entry is a file, so extract it.

			// Open current file.
			if (unzOpenCurrentFile(zipfile) != UNZ_OK)
			{
				CCLOG("can not open file %s", fileName);
				unzClose(zipfile);
				return false;
			}

			// Create a file to store current file.
			FILE *out = fopen(fullPath.c_str(), "wb");
			if (! out)
			{
				CCLOG("can not open destination file %s", fullPath.c_str());
				unzCloseCurrentFile(zipfile);
				unzClose(zipfile);
				return false;
			}

			// Write current file content to destinate file.
			int error = UNZ_OK;
			do
			{
				error = unzReadCurrentFile(zipfile, readBuffer, BUFFER_SIZE);
				if (error < 0)
				{
					CCLOG("can not read zip file %s, error code is %d", fileName, error);
					unzCloseCurrentFile(zipfile);
					unzClose(zipfile);
					return false;
				}

				if (error > 0)
				{
					fwrite(readBuffer, error, 1, out);
				}
			} while(error > 0);

			fclose(out);
		}

		unzCloseCurrentFile(zipfile);

		// Goto next entry listed in the zip file.
		if ((i + 1) < global_info.number_entry)
		{
			if (unzGoToNextFile(zipfile) != UNZ_OK)
			{
				CCLOG("can not read next file");
				unzClose(zipfile);
				return false;
			}
		}
	}

	CCLOG("end uncompressing");
	unzClose(zipfile);

	return true;
}

void MEUpdateEngine::createStoragePath(const char *path)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	FileUtils::getInstance()->createDirectory(path);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if ((GetFileAttributesA(path)) == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectoryA(path, 0);
	}
#else
	DIR *dir = nullptr;
	dir = opendir (path);
	if (!dir)
	{
		mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO);
	}
#endif
}

bool MEUpdateEngine::createDirectory(const char *path)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	return FileUtils::getInstance()->createDirectory(path);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	BOOL ret = CreateDirectoryA(path, nullptr);
	if (!ret && ERROR_ALREADY_EXISTS != GetLastError())
	{
		return false;
	}
	return true;
#else
	mode_t processMask = umask(0);
	int ret = mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO);
	umask(processMask);
	if (ret != 0 && (errno != EEXIST))
	{
		return false;
	}
	return true;
#endif
}

void MEUpdateEngine::destroyStoragePath()
{
    // Delete recorded version codes.
    this->setVersion("");
    this->setBaseVersion("");

    // Remove downloaded files
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    string command = "rm -r ";
    // Path may include space.
    command += "\"" + _storagePath + "\"";
    system(command.c_str());    
#else
    string command = "rd /s /q ";
    // Path may include space.
    command += "\"" + _storagePath + "\"";
    system(command.c_str());
#endif
}

void MEUpdateEngine::destroyTempDownPath(std::string path)
{
	// Remove downloaded files
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    string command = "rm -r ";
    // Path may include space.
    command += "\"" + path + "\"";
    system(command.c_str());    
#else
    string command = "rd /s /q ";
    // Path may include space.
    command += "\"" + path + "\"";
    system(command.c_str());
#endif
}

void MEUpdateManagerDelegateProtocol::onProgress(int percent)
{
	if(percent < 0)
		return;
	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onProgress");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushInt(percent);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
	} while (0);
}

void MEUpdateManagerDelegateProtocol::onSuccess()
{
	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onSuccess");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 0);
	} while (0);
}

void MEUpdateManagerDelegateProtocol::onError(MEUpdateEngine::ErrorCode errorCode)
{
	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onError");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushInt((int)errorCode);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
	} while (0);
}
