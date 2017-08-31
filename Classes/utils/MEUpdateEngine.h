/****************************************************************************
 版权:
 日期：2015-01-09
 内容: 在线升级数据，下载文件为zip，下载后自动解压（解压后自动删除zip文件）,该类支持断点续传.
 ****************************************************************************/

#ifndef __MEUpdateEngine_H_
#define __MEUpdateEngine_H_

#include <string>
#include <mutex>
#include "2d/CCNode.h"

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class MEUpdateManagerDelegateProtocol;

class MEUpdateEngine : public cocos2d::Node
{
public:
	virtual ~MEUpdateEngine();

	/**
    * @brief 更新数据时的错误编码
    */
	enum class ErrorCode
    {
        // Error caused by creating a file to store downloaded data
        CREATE_FILE,//创建下载数据存储文件时错误
        /** Error caused by network
         -- network unavaivable
         -- timeout
         -- ...
         */
        NETWORK,//网络故障
		/** There is not a new version
         */
        NO_NEW_VERSION,
        /** Error caused in uncompressing stage
         -- can not open zip file
         -- can not read file global information
         -- can not read file information
         -- can not create a directory
         -- ...
         */
        UNCOMPRESS,//解压缩错误

		IOSUPDATE,
    };

	/**
    * @brief 设置下载的相关数据
	* @param packageUrl 下载文件的url
	* @param storagePath 下载文件的保存路径(解压后的文件也在该位置) 注：该路径为安装文件的私有文件夹下的相对路径
	*                    用于在私有文件夹下添加文件夹
    */
	MEUpdateEngine(const char* packageUrl = NULL, const char* versionFileUrl = NULL, const char* storagePath = NULL);

	/* @brief 获取更新包下载url
     */
    const char* getPackageUrl() const;

	/**
    * @brief 设置更新包下载url
	* @param packageUrl 下载文件的url
    */
	void setPackageUrl(const char* packageUrl);
	
	/* @brief 获取版本文件url
     */
    const char* getVersionFileUrl() const;
    
    /* @brief 设置版本文件url
     */
    void setVersionFileUrl(const char* versionFileUrl);

	/* @brief 获取基版本文件url
     */
    const char* getBaseVersionFileUrl() const;
    
    /* @brief 设置基版本文件url
     */
    void setBaseVersionFileUrl(const char* versionBaseFileUrl);

	/* @brief 获取下载文件存储地址
     */
    const char* getStoragePath() const;

	/**
    * @brief 设置下载文件存储地址
	* @param storagePath 下载文件的保存路径(解压后的文件也在该位置) 注：该路径为安装文件的私有文件夹下的相对路径,
	*                    用于在私有文件夹下添加文件夹
    */
	void setStoragePath(const char* storagePath);

	/* @brief Gets current version code.
     */
    std::string getVersion();
    
	/* @brief Sets current version code.
     */
    void setVersion( const char* version);

	/* @brief Gets current base version code.
     */
    std::string getBaseVersion();
    
	/* @brief Sets current base version code.
     */
    void setBaseVersion( const char* base_version);

	/**
    * @brief 是否下载的是安装包
    */
	bool isDownpackage(){ return _isDownpackage; }

	/* @brief 获取下载文件安装包地址
     */
    const char* getDownPackageStoragePath() const;

	/**
     * @js NA
     * @lua NA
     */
    MEUpdateManagerDelegateProtocol* getDelegate() const { return _delegate;}

	/**
    * @brief 设置接口对象
	* @param delegateProtocol 接口对象
    */
	void setDelegate(MEUpdateManagerDelegateProtocol *delegateProtocol);

	/** @brief 获取连接超时
     */
    unsigned int getConnectionTimeout();
	/**
    * @brief 设置连接超时，单位为秒
	* @param timeout 超时时间
    */
	void setConnectionTimeout(unsigned int timeout);

	/**
    * @brief 线程接口（下载进度回调） 每次下载大小 不是总的大小
    */
	friend int updateManagerProgressFunc(void *, double, double, double, double);
	
	/* @brief Check out if there is a same base version resource.
     *        You may use this method before updating, then let user determine whether
     *        he wants to update resources.
     */
    virtual bool checkBaseVersion();

	/* @brief Check out if there is a new version resource.
     *        You may use this method before updating, then let user determine whether
     *        he wants to update resources.
     */
    virtual bool checkUpdate();

	/**
    * @brief 开始更新
    */
	virtual void update();

private:
	/**
    * @brief 检查下载文件存储地址
    */
	void checkStoragePath();

	/**
    * @brief 初始化存储路径
    */
	void createStoragePath(const char *path);

	/**
    * @brief 是否初始化路径
    */
	bool createDirectory(const char *path);

	/**
    * @brief 下载
	* @return 
    */
	bool downLoad();

	/**
	* fopen函数调用如下：
	* fopen（“文件名”，“使用文件方式”）；
	* r：只读；
	* w：只写；
	* r+：允许读写；
	* w+：允许读写；
	* a：向文本文件末添加数据；
	* a+：向文本文件末添加数据，允许读；
	* rb：只读二进制文件；
	* wb：只写二进制文件；
	* rb+：只读二进制文件，允许写；
	* wb+：只写二进制文件，允许读；
	* ab：向二进制文件末添加数据；
	* ab+：向二进制文件末添加数据，允许读；
	*/
   /**
    * @brief 已下载文件的长度
	* @return 已下载文件的长度
    */
	long getLocalFileLength();

	 /**
    * @brief 设置搜索路径
    */
	void setSearchPath();

	 /**
    * @brief 下载并解压
    */
	void downloadAndUncompress();

	/**
    * @brief 解压已下载的文件
	* @return 解压情况true：解压成功
    */
	bool uncompress();

	/** @brief Destroys storage path.
     */
    void destroyStoragePath();
	
	/** @brief Destroys storage path.
     */
    void destroyTempDownPath(std::string path);

	std::string keyOfVersion() const;
    std::string keyOfDownloadedVersion() const;

private:
	//下载文件的url
	std::string _packageUrl;
	//下载文件的保存路径(解压后的文件也在该位置) 注：该路径为安装文件的私有文件夹下的相对路径,用于在私有文件夹下添加文件夹
	std::string _storagePath;
	//版本url
	std::string _versionFileUrl;
	//基版本url
	std::string _versionBaseFileUrl;
	 //! The base version of downloaded resources.
    std::string _baseversion;
	 //! The version of downloaded resources.
    std::string _version;
	//安装包名称
	std::string _downPackageName;
	//下载的版本号
	std::string _downloadedVersion;
	//接口对象
	MEUpdateManagerDelegateProtocol *_delegate;
	//超时时间
	int _connectionTimeout;
	//curl对象
	void *_curl;
	//已下载文件长度
	long m_lLocalFileLenth;
	//是否正在下载
	bool _isDownloading;
	//是否下载安装包
	bool _isDownpackage;
	bool _shouldDeleteDelegateWhenExit;
};

/**
 * @brief 下载管理接口
 */
class MEUpdateManagerDelegateProtocol
{
public:
	virtual ~MEUpdateManagerDelegateProtocol(){};

	/**
    * @brief 下载错误接口方法
	* @param errorCode 错误编码
    */
	virtual void onError(MEUpdateEngine::ErrorCode errorCode);

	/**
    * @brief 下载进度（0 - 100）
	* @param percent 进度百分比
    */
	virtual void onProgress(int percent);

	/**
    * @brief 下载下载完成并且解压完成
    */
	virtual void onSuccess();
};

#endif // !__MEUpdateEngine_H_