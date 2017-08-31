#ifndef __ME_SKYLINE_IMAGE_DOWNLOADER_H__
#define __ME_SKYLINE_IMAGE_DOWNLOADER_H__

#include "cocos2d.h"
#include "../web/MCWebReq.h"
USING_NS_CC;

NS_CC_BEGIN

struct ImagicDownInfo
{
	ImagicDownInfo()
	{
		fActTime = 0;
		pRequest = NULL;
	}
	cocos2d::network::HttpRequestEx* pRequest;
	std::string kUrl;
	std::string kImagicName;
	std::string customId;
	float fActTime;
};

typedef std::vector<ImagicDownInfo> ImagicDownInfoList;

class MEImageDownloader : public Ref 
{
public:
	static MEImageDownloader* create(const std::string &storagePath);

	MEImageDownloader(const std::string &storagePath);
	virtual ~MEImageDownloader();
	void downImage(std::string srcUrl, const std::string& filename, const std::string& customId);

private:
	void OnImagic();
	void GetImagic(cocos2d::network::HttpClientEx *sender, cocos2d::network::HttpResponseEx *response);
	void upTime(float fTime);
	void onSuccess(const std::string &srcUrl, const std::string &storagePath, const std::string &customId);
private:
	ImagicDownInfoList m_pDownList;
	std::vector<cocos2d::network::HttpResponseEx*> m_pGetList;
	//! The path to store downloaded resources.
	std::string _storagePath;
};

NS_CC_END

#endif
