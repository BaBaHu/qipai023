#ifndef _MISSION_WEIXIN_H_
#define _MISSION_WEIXIN_H_

#include <string>
#include "FvSingleton.h"
#include "../web/MCWebReq.h"

struct WxUserInfo
{
	std::string openid;
	std::string nickname;
	int		   sex;
	std::string province;
	std::string city;
	std::string country;
	std::string headimgurl;
	std::string unionid;
};

class IWeiXinMissionSink
{
public:
	virtual ~IWeiXinMissionSink(){}
	virtual void onWxLoginSuccess(WxUserInfo kWxUserInfo ){}
	virtual void onWxLoginFail(std::string kError){}
};

class MissionWeiXin:public FvSingleton<MissionWeiXin>
{
public:
	const static int SHARE_SESSION = 0;
	const static int SHARE_MOMENTS = 1;
	const static char str_seq = '*';
	
public:
	MissionWeiXin();
	~MissionWeiXin();
public:
	void logonWeiXin();
	void restWeiXin();
	void setMissionSink(IWeiXinMissionSink* pJniMissionSink);
	IWeiXinMissionSink* getMissionSink();
	void shareScreenWeiXin(std::string strImagic,int nShareType = SHARE_SESSION);
	void shareTextWeiXin(std::string kText,int nShareType = SHARE_SESSION);
	void shareUrlWeiXin(std::string kUrl,std::string kTitle,std::string kDesc,int nShareType = SHARE_SESSION);
public:
	void Req_Fail_token(std::string param);
	void Req_Access_token(std::string param);
	void Rsp_Access_token(rapidjson::Document* pDoc);

	void Req_UserInfo(const std::string& access_token,const std::string& open_id);
	void Rsp_UserInfo(rapidjson::Document* pDoc);

	void Req_RefreshToken();
	void Rsp_RefreshToken(rapidjson::Document* pDoc);

private:
	bool IsEmoji(int32_t sym);
	bool RemoveEmoji(std::string & str);
	std::string IsUTF8(const char* pBuffer, long size);
private:
	IWeiXinMissionSink*   m_pJinMissionSink;
	std::vector<uint32_t>  punct_value;
	std::string       m_kWxAppId;
	std::string       m_kWxAppSecret;
	std::string		  m_kUrl;
};

#endif //_MISSION_WEIXIN_H_