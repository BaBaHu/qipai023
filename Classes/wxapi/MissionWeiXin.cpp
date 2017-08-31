#include "MissionWeiXin.h"
#include "JniCross/JniFun.h"
#include "UtilityBase.h"
#include "MELog.h"
#include "codeConv.h"
#include <iostream>
#include <vector>
using namespace std;

FV_SINGLETON_STORAGE(MissionWeiXin)

MissionWeiXin::MissionWeiXin()
	:m_pJinMissionSink(NULL)
{
	punct_value.clear();
	if (punct_value.size() != 2)
	{
		punct_value.push_back(0xE3808A);
		punct_value.push_back(0xE3808B);
	}
}

MissionWeiXin::~MissionWeiXin()
{
	
}

void MissionWeiXin::logonWeiXin()
{
	std::string access_token = cocos2d::UserDefault::getInstance()->getStringForKey("access_token");
	std::string refresh_token = cocos2d::UserDefault::getInstance()->getStringForKey("refresh_token");
	std::string openid = cocos2d::UserDefault::getInstance()->getStringForKey("openid","");
	if (access_token != "" && openid != "")
	{
		Req_UserInfo(access_token,openid);
	}
	else
	{
		JniFun::longinWX("","");
	}
}
void MissionWeiXin::restWeiXin()
{
	cocos2d::UserDefault::getInstance()->setStringForKey("access_token","");
	cocos2d::UserDefault::getInstance()->setStringForKey("refresh_token","");
}
void MissionWeiXin::setMissionSink( IWeiXinMissionSink* pJniMissionSink )
{
	m_pJinMissionSink = pJniMissionSink;
}

IWeiXinMissionSink* MissionWeiXin::getMissionSink()
{
	return m_pJinMissionSink;
}

void MissionWeiXin::Req_Fail_token(std::string param)
{
	if (m_pJinMissionSink)
	{
		m_pJinMissionSink->onWxLoginFail(param);
	}
}
void MissionWeiXin::Req_Access_token(std::string param)
{
	MELOG(MELOG_INFO, "Req_Access_token : %s\n", param.c_str() );
	std::vector<std::string> kVector = utility::split(param, ":");
	if (kVector.size() != 4)
	{
		log("if (kVector.size() != 4)");
		return ;
	}
	std::string kUrl = "https://api.weixin.qq.com/sns/oauth2/access_token?";

    cocos2d::log("MissionWeiXin::Req_Access_token");
	m_kWxAppId = kVector[0];
	m_kWxAppSecret = kVector[1];

	MCWebReq::pushValue(kUrl,"appid",kVector[0]);
	MCWebReq::pushValue(kUrl,"secret",kVector[1]);
	MCWebReq::pushValue(kUrl,"code",kVector[2]);
	MCWebReq::pushValue(kUrl,"grant_type",kVector[3]);

	//	kUrl="https://api.weixin.qq.com/sns/oauth2/access_token?appid=wx79ad4c77ea07f41e&secret=66ad79231c6954ba68811afb14fad5e2&code=031RcTgJ17gEpa028PfJ1a9VgJ1RcTgO&grant_type=authorization_code";
	MCWebReq::instance().sendRequestDocumentUrl(kUrl,CC_CALLBACK_1(MissionWeiXin::Rsp_Access_token,this),nullptr);
}

void MissionWeiXin::Rsp_Access_token(rapidjson::Document* pDoc)
{
	std::string access_token = MCWebReq::getDataValueStr(pDoc,"access_token");
	int expires_in = MCWebReq::getDataValueInt(pDoc,"expires_in");
	std::string refresh_token = MCWebReq::getDataValueStr(pDoc,"refresh_token");
	std::string openid = MCWebReq::getDataValueStr(pDoc,"openid");
	std::string scope = MCWebReq::getDataValueStr(pDoc,"scope");
	std::string unionid = MCWebReq::getDataValueStr(pDoc,"unionid");

	cocos2d::log("MissionWeiXin::Rsp_Access_token JNIMission access_token:%s",access_token.c_str());
	cocos2d::log("MissionWeiXin::Rsp_Access_token JNIMission expires_in:%d",expires_in);
	cocos2d::log("MissionWeiXin::Rsp_Access_token JNIMission refresh_token:%s",refresh_token.c_str());
	cocos2d::log("MissionWeiXin::Rsp_Access_token JNIMission openid:%s",openid.c_str());
	cocos2d::log("MissionWeiXin::Rsp_Access_token JNIMission scope:%s",scope.c_str());
	cocos2d::log("MissionWeiXin::Rsp_Access_token JNIMission unionid:%s",unionid.c_str());

	cocos2d::UserDefault::getInstance()->setStringForKey("access_token",access_token);
	cocos2d::UserDefault::getInstance()->setStringForKey("refresh_token",refresh_token);
	cocos2d::UserDefault::getInstance()->setStringForKey("openid",openid);
	cocos2d::UserDefault::getInstance()->setStringForKey("unionid",unionid);
	cocos2d::UserDefault::getInstance()->flush();

	Req_UserInfo(access_token,openid);
}

void MissionWeiXin::Req_UserInfo(const std::string& access_token,const std::string& open_id)
{
    cocos2d::log("MissionWeiXin::Req_UserInfo");
	std::string kUrl = "https://api.weixin.qq.com/sns/userinfo?";
	MCWebReq::pushValue(kUrl,"access_token",access_token);
	MCWebReq::pushValue(kUrl,"openid",open_id);
	MCWebReq::instance().sendRequestDocumentUrl(kUrl,CC_CALLBACK_1(MissionWeiXin::Rsp_UserInfo,this),nullptr);
}
void MissionWeiXin::Rsp_UserInfo(rapidjson::Document* pDoc)
{
	int errcode = MCWebReq::getDataValueInt(pDoc,"errcode");
    cocos2d::log("MissionWeiXin::Rsp_UserInfo, error code %d", errcode);
	if (errcode!=0)
	{
		JniFun::longinWX("","");
		return;
	}

	WxUserInfo kWxUserInfo;
	kWxUserInfo.openid = MCWebReq::getDataValueStr(pDoc,"openid");

	std::string strNickName = MCWebReq::getDataValueStr(pDoc, "nickname");
	MELOG(MELOG_INFO, "before : %s\n", strNickName.c_str());
	cocos2d::log("name before %s", strNickName.c_str());
	kWxUserInfo.nickname = IsUTF8(strNickName.c_str(), strNickName.length());
	MELOG(MELOG_INFO, "after :  %s\n", kWxUserInfo.nickname.c_str());
	cocos2d::log("name after %s", kWxUserInfo.nickname.c_str());

	kWxUserInfo.sex = MCWebReq::getDataValueInt(pDoc,"sex");
	kWxUserInfo.province = MCWebReq::getDataValueStr(pDoc,"province");
	kWxUserInfo.city = MCWebReq::getDataValueStr(pDoc,"city");
	kWxUserInfo.country = MCWebReq::getDataValueStr(pDoc,"country");
	kWxUserInfo.headimgurl = MCWebReq::getDataValueStr(pDoc,"headimgurl");
	kWxUserInfo.unionid = MCWebReq::getDataValueStr(pDoc,"unionid");

	if (kWxUserInfo.sex == 2)
	{
		kWxUserInfo.sex = 0;
	}
	else
	{
		kWxUserInfo.sex = 1;
	}

	cocos2d::UserDefault::getInstance()->setStringForKey("openid",kWxUserInfo.openid);
	cocos2d::UserDefault::getInstance()->setStringForKey("unionid",kWxUserInfo.unionid);
	cocos2d::UserDefault::getInstance()->flush();
	log("Rsp_UserInfo finish .....................................\n");

	if (m_pJinMissionSink)
	{
		m_pJinMissionSink->onWxLoginSuccess(kWxUserInfo);
	}
}


void MissionWeiXin::Req_RefreshToken()
{
	std::string kUrl = "https://api.weixin.qq.com/sns/oauth2/refresh_token?";
	std::string access_token = cocos2d::UserDefault::getInstance()->getStringForKey("access_token");
	std::string refresh_token = cocos2d::UserDefault::getInstance()->getStringForKey("refresh_token");

	MCWebReq::pushValue(kUrl,"appid",access_token);
	MCWebReq::pushValue(kUrl,"grant_type","refresh_token");
	MCWebReq::pushValue(kUrl,"refresh_token",refresh_token);
	MCWebReq::instance().sendRequestDocumentUrl(kUrl,CC_CALLBACK_1(MissionWeiXin::Rsp_RefreshToken,this),nullptr);
}
void MissionWeiXin::Rsp_RefreshToken(rapidjson::Document* pDoc)
{
	Rsp_Access_token(pDoc);
}

void MissionWeiXin::shareScreenWeiXin(std::string strImagic,int nShareType /*= SHARE_SESSION*/)
{
	JniFun::shareImageWX(strImagic.c_str(), nShareType);
}
void MissionWeiXin::shareTextWeiXin(std::string kText,int nShareType /*= SHARE_SESSION*/)
{
	JniFun::shareTextWX(kText.c_str(),nShareType);
}
void MissionWeiXin::shareUrlWeiXin(std::string kUrl,std::string kTitle,std::string kDesc,int nShareType)
{
	JniFun::shareUrlWX(kUrl.c_str(),kTitle.c_str(),kDesc.c_str(),nShareType);
}

bool MissionWeiXin::IsEmoji(int32_t sym)
{
	// ranges of symbol codes with unicode emojies.
	static std::vector<std::pair<int32_t, int32_t>> ranges = { { 0x2190, 0x21FF }, { 0x2300, 0x243F }, { 0x2600, 0x26FF }, { 0x2700, 0x27BF }, { 0x3000, 0x303F }, /*{ 0x1F1E6, 0x1F1FF },*/{ 0x1F300, 0x1F6FF }, { 0x1F900, 0x1F9FF } };
	for (auto range : ranges)
	{
		if (sym >= range.first && sym <= range.second)
		{
			return true;
		}
	}
	return false;
}

bool MissionWeiXin::RemoveEmoji(std::string & str)
{
	std::wstring  datavalue = string_to_wstring(str);
	std::wstring  ret;
	bool isChanged = false;
	cout << datavalue[0] << endl;

	auto data = datavalue.data();
	size_t length = datavalue.length();
	for (size_t i = 0; i < length; ++i)
	{
		int32_t sym = 0;
		cout << data[i] << endl;
		memcpy(&sym, data + i, sizeof(int32_t));

		if (!IsEmoji(sym))
		{
			ret += sym;
		}
		else
		{
			while (i + 1 < length)
			{
				i++;
				memcpy(&sym, data + i, sizeof(int32_t));
				if (sym != 0x200D && sym != 0xFE0F)
				{
					i--;
					break;
				}
			}
			isChanged = true;
		}
	}
	str = wstring_to_string(ret);
	// true means "we removed some emojies".
	return isChanged;
}

std::string MissionWeiXin::IsUTF8(const char* pBuffer, long size)
{
	char word[4] = { "\0" };

	string str_word = "";
	int last_pos = 0;
	int temp_pos = 0;
	
	uint32_t min = 0xE4B880;
	uint32_t max = 0xE9BEA0;

	uint32_t word_code = 0;
	unsigned char* start = (unsigned char*)pBuffer;
	unsigned char* end = (unsigned char*)pBuffer + size;
	while (start < end)
	{
		if (*start < 0x80) // (10000000): 值小于0x80的为ASCII字符
		{

			bool flag = false;
			
			if ((*start >= 0x41 && *start <= 0x5A) || (*start >= 0x61 && *start <= 0x7A))
			{

				//if (last_pos != temp_pos)
				//	str_word += str_seq;
				if (*start >= 0x41 && *start <= 0x5A)
					str_word += tolower(*start);
				else
					str_word += (*start);
				flag = true;
			}
			else if ((*start >= 0x30 && *start <= 0x39) || (*start == '-') || (*start == '_') || (*start == '@'))
			{
				//if (last_pos != temp_pos)
				//	str_word += str_seq;
				str_word += (*start);
				flag = true;
			}
			start++;
			temp_pos++;
			if (flag == true)
				last_pos = temp_pos;
		}
		else if (*start < (0xC0)) // (11000000): 值介于0x80与0xC0之间的为无效UTF-8字符
		{
			start++;
			temp_pos++;
		}
		else if (*start < (0xE0)) // (11100000): 此范围内为2字节UTF-8字符
		{
			if (start >= end - 1)
				break;
			start += 2;
			temp_pos += 2;
		}
		else if (*start < (0xF0)) //(11110000): 此范围内为3字节UTF-8字符
		{

			if (start >= end - 2)
				break;


			bool flag = false;
			if ((*start >= (0xE3)) && (*start <= (0xE9)) || (*start == 0xEF))
			{
				if ((start[1] & (0xC0)) == 0x80 || (start[2] & (0xC0)) == 0x80)
				{

					word[0] = start[0];
					word[1] = start[1];
					word[2] = start[2];

					word_code |= ((uint32_t)start[0]) << 16;
					word_code |= ((uint32_t)start[1]) << 8;
					word_code |= (uint32_t)start[2];

					if ((word_code >= min) && (word_code <= max))
					{
						if ((temp_pos != last_pos) && (last_pos>0))
						{
							//str_word += str_seq;
						}
						str_word += word;
						flag = true;
					}
					else
					{
						if (find(punct_value.begin(), punct_value.end(), word_code) != punct_value.end())
						{
							if ((temp_pos != last_pos) && (last_pos>0))
							{
								//str_word += str_seq;
							}
							str_word += word;
							flag = true;
						}
					}
					word_code = 0;
				}

			}

			start += 3;
			temp_pos += 3;
			if (flag == true)
				last_pos = temp_pos;
		}
		else
		{
			start += 4;
			temp_pos += 4;
		}
	}
	return str_word;
}