#include "MEImageDownloader.h"
#include "MECallBackListenerHelper.h"
#include "MEFileUtil.h"
#include "MELog.h"
#define DEFAULT_CONNECTION_TIMEOUT 8

NS_CC_BEGIN

MEImageDownloader::MEImageDownloader(const std::string &storagePath)
: _storagePath("")
{
	_storagePath = storagePath;
	MEFileUtil::createDir(_storagePath.c_str());
	FileUtils::getInstance()->addSearchPath(storagePath, true);

	cocos2d::Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(MEImageDownloader::upTime), this, 0.0f, false);
}

MEImageDownloader::~MEImageDownloader()
{
	cocos2d::Director::getInstance()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(MEImageDownloader::upTime), this);
}

MEImageDownloader* MEImageDownloader::create(const std::string& storagePath)
{
	MEImageDownloader* ret = new (std::nothrow) MEImageDownloader(storagePath);
	if (ret)
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

void MEImageDownloader::upTime(float fTime)
{
	OnImagic();
	ImagicDownInfoList::iterator itor = m_pDownList.begin();
	while (itor != m_pDownList.end())
	{
		ImagicDownInfo& kInfo = *itor;
		kInfo.fActTime += fTime;
		if (kInfo.fActTime > 20.0f)
		{
			itor = m_pDownList.erase(itor);
		}
		else
		{
			itor++;
		}
	}
}

void MEImageDownloader::GetImagic(cocos2d::network::HttpClientEx *sender, cocos2d::network::HttpResponseEx *response)
{
	response->retain();
	m_pGetList.push_back(response);
}

void MEImageDownloader::OnImagic()
{
	if (m_pGetList.size() == 0)
	{
		return;
	}
	cocos2d::network::HttpResponseEx *response = m_pGetList[0];
	m_pGetList.erase(m_pGetList.begin());
	std::string kUrl = response->getHttpRequest()->getUrl();
	std::string kImagicName = "test.png";

	ImagicDownInfoList::iterator itor1 = m_pDownList.begin();
	while (itor1 != m_pDownList.end())
	{
		ImagicDownInfo& kInfo = *itor1;
		if (kInfo.kUrl.find(kUrl.c_str()) != std::string::npos)
		{
			kImagicName = kInfo.kImagicName;
			break;
		}
		itor1++;
	}
    bool bSucess = false;
	std::vector<char> *buffer = response->getResponseData();
	if (buffer->size() != 0)
	{
        cocos2d::CCImage* img = new cocos2d::CCImage;
        img->initWithImageData((unsigned char*)buffer->data(), buffer->size());
        
        if (img->getData())
        {
			std::string path = _storagePath + kImagicName;
            bSucess = img->saveToFile(path, false);
        }
        delete img;
    }
    
	ImagicDownInfoList::iterator itor2 = m_pDownList.begin();
	while (itor2 != m_pDownList.end())
	{
		ImagicDownInfo& kInfo = *itor2;
		if (kInfo.kUrl.find(kUrl.c_str()) != std::string::npos)
		{
			if (bSucess)
			{
				this->onSuccess(kInfo.kUrl, _storagePath, kInfo.customId);
			}
			itor2 = m_pDownList.erase(itor2);
		}
		else
		{
			itor2++;
		}
	}
	response->release();
}

void MEImageDownloader::downImage(std::string srcUrl, const std::string& filename, const std::string& customId)
{
	if (srcUrl == "")
	{
		return;
	}
	std::string path = _storagePath + filename;
    if (cocos2d::CCTextureCache::sharedTextureCache()->addImage(path.c_str()))
    {
		// CCLOG("file already downloaded, just return");
		this->onSuccess(srcUrl, _storagePath, customId);
		return;
	}

	bool bHaveGet = false;
	for (int i = 0; i<(int)m_pDownList.size(); i++)
	{
		ImagicDownInfo& kInfo = m_pDownList[i];
		if (kInfo.customId == customId)
		{
			bHaveGet = true;
		}
	}

	if (!bHaveGet)
	{
		ImagicDownInfo kInfo;
		kInfo.customId = customId;
		kInfo.kImagicName = filename;
		kInfo.kUrl = srcUrl;
		cocos2d::network::HttpRequestEx* pRequest = MCWebReq::instance().getFileEx(srcUrl,CC_CALLBACK_2(MEImageDownloader::GetImagic, this));
		kInfo.pRequest = pRequest;
		m_pDownList.push_back(kInfo);
	}
}

void MEImageDownloader::onSuccess(const std::string &srcUrl, const std::string &storagePath, const std::string &customId)
{
	MELOG(MELOG_INFO, "Download image downloaded, url:{%s} custom:{%s} ", srcUrl.c_str(), customId.c_str());
	int ret = 0;
	do
	{
		std::string strHandler = "Down" + customId + "Succ";
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler(strHandler);
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushString(srcUrl.c_str());
		pStack->pushString(customId.c_str());
		pStack->pushString(storagePath.c_str());
		ret = pStack->executeFunctionByHandler(nLuaHandler, 3);
	} while (0);
}

NS_CC_END
