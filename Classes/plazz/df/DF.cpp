#include "../Plazz.h"
#include "DF.h"
#include "../../libs/crypt/coMD5.h"

#include "cocos2d.h"
USING_NS_CC;

static char s_NumMap[10][10] = { { 1, 2, 9, 5, 7, 0, 4, 8, 6, 3 }, { 1, 8, 9, 3, 7, 5, 4, 6, 2, 0 }, { 9, 2, 4, 6, 0, 1, 8, 7, 5, 3 }, { 9, 1, 0, 4, 3, 8, 2, 7, 6, 5 }, \
{0, 9, 8, 5, 1, 2, 7, 4, 6, 3}, { 8, 9, 2, 7, 4, 1, 6, 0, 3, 5 }, { 6, 1, 0, 7, 8, 3, 4, 9, 5, 2 }, { 5, 9, 1, 0, 6, 2, 7, 4, 8, 3 }, { 7, 5, 4, 8, 1, 0, 3, 9, 6, 2 }, { 3, 5, 9, 2, 1, 0, 8, 4, 6, 7 }
};
static char s_RevNumMap[10][10] = { { 5, 0, 1, 9, 6, 3, 8, 4, 7, 2 }, { 9, 0, 8, 3, 6, 5, 7, 4, 1, 2 }, { 4, 5, 1, 9, 2, 8, 3, 7, 6, 0 }, { 2, 1, 6, 4, 3, 9, 8, 7, 5, 0 }, \
{0, 4, 5, 9, 7, 3, 8, 6, 2, 1}, { 7, 5, 2, 8, 4, 9, 6, 3, 0, 1 }, { 2, 1, 9, 5, 6, 8, 0, 3, 4, 7 }, { 3, 2, 5, 9, 7, 0, 4, 6, 8, 1 }, { 5, 4, 9, 6, 2, 1, 8, 0, 3, 7 }, { 5, 4, 3, 0, 7, 1, 8, 9, 6, 2 }
};

//////////////////////////////////////////////////////////////////////////

DF* DF::shared() 
{
	static DF sInstance;
	return &sInstance;
}

const char* DF::MD5Encrypt(const char* pszSourceData)
{
	static std::string sPassword;
	sPassword = coMD5(pszSourceData);
	return sPassword.c_str();
}

const char* DF::encryptRoomID(char szNum7[])
{
	if (NULL == szNum7 || strlen(szNum7) != 6)
		return NULL;
	char num6[6] = { 0 };
	int sum = 0;
	for (size_t i = 1; i < 6; ++i)
	{
		num6[i] = szNum7[i] - '0';
		sum += num6[i];
	}

	int iMapIdx = sum % 10;
	szNum7[0] = iMapIdx + '0';
	for (size_t i = 1; i < 6; ++i)
		szNum7[i] = s_NumMap[iMapIdx][num6[i]] + '0';
	return szNum7;

}

const char* DF::decodeRoomID(char szNum7[])
{
	if (NULL == szNum7 || strlen(szNum7) != 6)
		return NULL;
	char num6[6] = { 0 };
	int sum = 0;
	for (size_t i = 1; i < 6; ++i)
	{
		num6[i] = szNum7[i] - '0';
	}
	int iMapIdx = szNum7[0] - '0';
	for (size_t i = 1; i < 6; ++i)
		szNum7[i] = s_RevNumMap[iMapIdx][num6[i]] + '0';
	szNum7[0] = '0';
	return szNum7;
}

//////////////////////////////////////////////////////////////////////////

DF::DF()
{
}

DF::~DF()
{
}

void DF::init(int iKindID, int iPlayers, int iClientVersion, const char* sGameName)
{
	mKindID = iKindID;
	mGamePlayers = iPlayers;
	mClientVersion = iClientVersion;
	mGameName = sGameName;
}

byte DF::GetDeviceType()
{
	return DEVICE_TYPE_PC;
}

const char* DF::GetMachineID()
{
	static bool bFirst = true;
	static char szMachineID[LEN_MACHINE_ID]={0};

	if (bFirst)
	{
		bFirst=false;

		switch (GetDeviceType())
		{
		case DEVICE_TYPE_PC:
			{
				break;
			}
		case DEVICE_TYPE_ANDROID:
			{
				break;
			}
		}

	}

	return szMachineID;
}

const char* DF::GetMobilePhone()
{
	static bool bFirst = true;
	static char szPhone[LEN_MACHINE_ID]={0};

	if (bFirst)
	{
		bFirst=false;

		switch (GetDeviceType())
		{
		case DEVICE_TYPE_PC:
			{
				break;
			}
		case DEVICE_TYPE_ANDROID:
			{
				break;
			}
		}
	}

	return szPhone;
}



uint32 DF::GetPlazaVersion()
{
	switch (GetDeviceType())
	{
	case DEVICE_TYPE_ANDROID:
		return VERSION_MOBILE_ANDROID;
	case DEVICE_TYPE_IPAD:
	case DEVICE_TYPE_IPHONE:
	case DEVICE_TYPE_ITOUCH:
		return VERSION_MOBILE_IOS;
	}

	return VERSION_PLAZA;
}

uint32 DF::GetFrameVersion()
{
	return VERSION_FRAME;
}

uint16 DF::GetPlazzKindID()
{
	return GetGameKindID();
}

uint32 DF::GetGameVersion()
{
	return mClientVersion;
	//switch (GetDeviceType())
	//{
	//case DEVICE_TYPE_ANDROID:
	//	return PROCESS_VERSION(6,0,3);
	//case DEVICE_TYPE_IPAD:
	//case DEVICE_TYPE_IPHONE:
	//case DEVICE_TYPE_ITOUCH:
	//	return PROCESS_VERSION(6,0,3);
	//}

	//return PROCESS_VERSION(6,0,3);
}

uint16 DF::GetGameKindID()
{
	return mKindID;
}
uint32 DF::GetGamePlayer()
{
	return mGamePlayers;
}

const char* DF::GetGameName(char szGameName[LEN_KIND])
{
	const char* sGameName = mGameName.c_str();
	strncpy(szGameName, sGameName, LEN_KIND);
	return sGameName;
}