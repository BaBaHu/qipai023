#include "cocos2d.h"
#include "CGPLoginMission.h"
#include "MELog.h"

#define MISSION_LOGIN_ACCOUNT	1
#define MISSION_LOGIN_GAMEID	2
#define MISSION_LOGIN_TYPE		3
#define MISSION_REGISTER		4
#define MISSION_UPDATE_INFO		5
#define MISSION_SERVER_INFO		6
#define MISSION_BASE_ENSURETAKE	7

USING_NS_CC;

CGPLoginMission::CGPLoginMission(const std::string& url, int port)
	: CSocketMission(url, port)
{
	mMissionType = 0;
	mIGPLoginMissionSink = 0;
}


// 设置回调接口
void CGPLoginMission::setMissionSink(IGPLoginMissionSink* pIGPLoginMissionSink)
{
	mIGPLoginMissionSink = pIGPLoginMissionSink;
}

// 账号登陆
void CGPLoginMission::loginAccount(const tagGPLoginAccount& LoginAccount)
{
	memcpy(&mLoginAccount, &LoginAccount, sizeof(mLoginAccount));
	mMissionType = MISSION_LOGIN_ACCOUNT;
	start();
}

// I D登陆
void CGPLoginMission::loginGameID(const tagGPLoginGameID& LoginGameID)
{
	memcpy(&mLoginGameID, &LoginGameID, sizeof(mLoginGameID));
	mMissionType = MISSION_LOGIN_GAMEID;
	start();
}

// 类型登陆
void CGPLoginMission::loginType(const tagGPLoginByType& LoginType)
{
	memcpy(&mLoginType, &LoginType, sizeof(mLoginType));
	mMissionType = MISSION_LOGIN_TYPE;
	start();
}

void CGPLoginMission::registerAccount(const tagGPRegisterAccount& RegisterAccount)
{
	memcpy(&mRegisterAccount, &RegisterAccount, sizeof(mRegisterAccount));
	mMissionType = MISSION_REGISTER;
	start();
}

void CGPLoginMission::updateOnlineInfo()
{
	mMissionType = MISSION_UPDATE_INFO;
	start();
}

//更新类型
void CGPLoginMission::updateServerInfo(uint16 kind)
{
	KIND_ITER it = std::find(mKindList.begin(), mKindList.end(), kind);

	if (it != mKindList.end())
	{
		return;
	}

	it = std::find(mKindWaitList.begin(), mKindWaitList.end(), kind);

	if (it != mKindWaitList.end())
	{
		return;
	}

	mKindList.push_back(kind);
	mMissionType = MISSION_SERVER_INFO;
	start();
}

void CGPLoginMission::getBaseEnsureTake()
{
	mMissionType = MISSION_BASE_ENSURETAKE;
	start();
}

//发送登陆信息
bool CGPLoginMission::sendLoginAccount(const tagGPLoginAccount& LoginAccount)
{
	MELOG(MELOG_INFO, "sendLoginAccount....................................... \n");
	
	//加密密码
	const char* sPassword = DF::MD5Encrypt(LoginAccount.szPassword);

	//变量定义
	PACKET_AIDE_SIZE(SIZE_PACK_DATA);

	//打包数据
	packet.write4Byte(DF::shared()->GetPlazaVersion());
	packet.write4Byte(0); //IP
	packet.writeString(DF::shared()->GetMachineID(), LEN_MACHINE_ID);
	packet.writeString(sPassword, LEN_PASSWORD);
	packet.writeString(LoginAccount.szAccounts, LEN_ACCOUNTS);
	packet.writeByte(LoginAccount.cbValidateFlags);

	//保存密码
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	strncpy(pGlobalUserData->szPassword,sPassword, countarray(pGlobalUserData->szPassword));

	//发送数据
	send(MDM_GP_LOGON, SUB_GP_LOGON_ACCOUNTS, packet.getBuffer(), packet.getPosition());		
	return true;
}

//发送登陆信息
bool CGPLoginMission::sendLoginGameID(const tagGPLoginGameID& LoginGameID)
{
	MELOG(MELOG_INFO, "sendLoginGameID.......................................... \n");
	//加密密码
	const char* sPassword = DF::MD5Encrypt(LoginGameID.szPassword);

	//变量定义
	PACKET_AIDE_SIZE(SIZE_PACK_DATA);
	//打包数据
	packet.writeByte(DF::shared()->GetDeviceType());
	packet.write2Byte(DF::shared()->GetPlazzKindID());
	packet.write4Byte(DF::shared()->GetPlazaVersion());
	packet.writeString(DF::shared()->GetMachineID(), LEN_MACHINE_ID);
	packet.writeString(DF::shared()->GetMobilePhone(), LEN_MOBILE_PHONE);
	packet.write4Byte(LoginGameID.dwGameID);
	packet.writeString(sPassword, LEN_PASSWORD);
	packet.writeByte(LoginGameID.cbValidateFlags);
	
	//保存密码
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	strcpy(pGlobalUserData->szPassword,sPassword);

	//发送数据
	send(MDM_GP_LOGON, SUB_GP_LOGON_GAMEID, packet.getBuffer(), packet.getPosition());		
	return true;
}

// 登陆
bool CGPLoginMission::sendLoginType(const tagGPLoginByType& LoginType)
{
	MELOG(MELOG_INFO, "sendLoginType....................................... \n");
	log("sendLoginType = %s \n", LoginType.szNickName);
	//变量定义
	PACKET_AIDE_SIZE(SIZE_PACK_DATA);

//	unsigned char __PacketBuffer__[SIZE_PACK_DATA] = { 0 };
//	PacketAide packet(__PacketBuffer__);

	// 打包数据
	packet.write4Byte(DF::shared()->GetPlazaVersion());
	packet.write4Byte(100); //IP
	packet.writeString("machineID", LEN_MACHINE_ID);
	packet.writeByte(LoginType.cbSex);
	packet.writeString(LoginType.szAccounts, LEN_ACCOUNTS);
	packet.writeString(LoginType.szNickName, LEN_ACCOUNTS);
	packet.writeString(LoginType.szIconUrl, 256);
	packet.writeByte(LoginType.cbValidateFlags);

	// 保存密码
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();
	strncpy(pGlobalUserData->szPassword, "", countarray(pGlobalUserData->szPassword));

	// 发送数据
	if (LoginType.cbType == 2)
	{
		send(MDM_GP_LOGON, SUB_GP_WX_LOGON_ACCOUNTS, packet.getBuffer(), packet.getPosition());
	}
	else if (LoginType.cbType == 1)
	{
		send(MDM_GP_LOGON, SUB_GP_QQ_LOGON_ACCOUNTS, packet.getBuffer(), packet.getPosition());
	}
	
	return true;
}

//发送注册信息
bool CGPLoginMission::sendRegisterPacket(const tagGPRegisterAccount& RegisterAccount)
{
	MELOG(MELOG_INFO, "sendRegisterPacket.............................................. \n");
	//变量定义
	PACKET_AIDE_SIZE(SIZE_PACK_DATA);
	packet.write4Byte(DF::shared()->GetPlazaVersion());
	packet.write4Byte(0); //IP
	packet.writeString(DF::shared()->GetMachineID(), LEN_MACHINE_ID);
	packet.writeString(DF::MD5Encrypt(RegisterAccount.szLogonPass), LEN_PASSWORD);
	packet.writeString(DF::MD5Encrypt(RegisterAccount.szInsurePass), LEN_PASSWORD);
	packet.write2Byte(RegisterAccount.wFaceID);
	packet.writeByte(RegisterAccount.cbGender);
	packet.writeString(RegisterAccount.szAccounts, LEN_ACCOUNTS);
	packet.writeString(RegisterAccount.szNickName, LEN_NICKNAME);
	packet.writeString(RegisterAccount.szSpreader, LEN_ACCOUNTS);
	packet.writeString(RegisterAccount.szPassPortID, LEN_PASS_PORT_ID);
	packet.writeString("13888888888", LEN_MOBILE_PHONE);
	packet.writeString(RegisterAccount.szCompellation, LEN_COMPELLATION);
	packet.writeByte(RegisterAccount.cbValidateFlags);

	packet.write4Byte(0); //dwServerName
	packet.write2Byte(0); //UnionNumber

	//保存密码
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	strncpy(pGlobalUserData->szPassword,DF::MD5Encrypt(RegisterAccount.szLogonPass),countarray(pGlobalUserData->szPassword));

	//发送数据
	send(MDM_GP_LOGON, SUB_GP_REGISTER_ACCOUNTS, packet.getBuffer(), packet.getPosition());		
	return true;
}


// 更新人数
bool CGPLoginMission::sendUpdateOnlineInfoPacket()
{
	MELOG(MELOG_INFO, "sendUpdateOnlineInfoPacket....................................... \n");

	PACKET_AIDE_SIZE(SIZE_PACK_DATA);
	packet.setPosition(2);
	//变量定义
	int count = 0;

	//变量定义
	CServerListData * pServerListData=CServerListData::shared();
	CGameServerItemMap::iterator it = pServerListData->GetServerItemMapBegin();
	CGameServerItem * pGameServerItem=0;

	while ((pGameServerItem=pServerListData->EmunGameServerItem(it)))
	{
		//设置房间
		if (pGameServerItem!=0)
		{
			tagGameServer * pGameServer=&pGameServerItem->m_GameServer;
			packet.write2Byte(pGameServer->wServerID);
			count++;
		}
	}

	int pos = packet.getPosition();
	packet.setPosition(0);
	packet.write2Byte(count);
	packet.setPosition(pos);
	//发送数据
	send(MDM_GP_SERVER_LIST,SUB_GP_GET_ONLINE, packet.getBuffer(), packet.getPosition());

	return true;
}

// 更新类型房间列表
void CGPLoginMission::sendUpdateServerInfo()
{
	MELOG(MELOG_INFO, "sendUpdateServerInfo ....................................\n");
	//列表任务
	if (mKindList.size()>0L)
	{
		//变量定义
		uint16 wKindIDItem[MAX_KIND];
		uint16 wKindIDCount=(uint16)tmin(countarray(wKindIDItem),mKindList.size());

		//变量定义
		KIND_ITER it = mKindList.begin();
		int i = 0;
		for (; i < wKindIDCount && it != mKindList.end(); ++it)
		{
			wKindIDItem[i] = *it;
			mKindWaitList.push_back(wKindIDItem[i]);
			++i;
		}
		
		mKindList.clear();

		//发送数据
		send(MDM_GP_SERVER_LIST,SUB_GP_GET_SERVER,wKindIDItem,wKindIDCount*sizeof(uint16));
	}
	else
	{
		stop();
	}
}

bool CGPLoginMission::sendBaseEnsureTake()
{
	//获取对象
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();

	MELOG(MELOG_INFO, "sendRegisterPacket.............................................. \n");
	//变量定义
	PACKET_AIDE_SIZE(SIZE_PACK_DATA);
	packet.write4Byte(pGlobalUserData->dwUserID);
	packet.writeString(pGlobalUserData->szPassword, LEN_PASSWORD);
	packet.writeString(DF::shared()->GetMachineID(), LEN_MACHINE_ID);
	
	//发送数据
	send(MDM_GP_LOGON, SUB_GP_BASEENSURE_TAKE, packet.getBuffer(), packet.getPosition());
	return true;
}

void CGPLoginMission::onEventTCPSocketLink()
{
	switch (mMissionType)
	{
		// 登陆
	case MISSION_LOGIN_ACCOUNT:
		sendLoginAccount(mLoginAccount);
		break;
		// 登陆
	case MISSION_LOGIN_GAMEID:
		sendLoginGameID(mLoginGameID);
		break;
	case MISSION_LOGIN_TYPE:
		sendLoginType(mLoginType);
		break;
		// 注册
	case MISSION_REGISTER:
		sendRegisterPacket(mRegisterAccount);
		break;
		// 更新人数
	case MISSION_UPDATE_INFO:
		sendUpdateOnlineInfoPacket();
		break;
		// 更新类型房间列表
	case MISSION_SERVER_INFO:
		sendUpdateServerInfo();
		break;
	case MISSION_BASE_ENSURETAKE:
		sendBaseEnsureTake();
		break;
	}
}

void CGPLoginMission::onEventTCPSocketShut()
{
	MELOG(MELOG_INFO, "CGPLoginMission::onEventTCPSocketShut: close socket \n");
}

void CGPLoginMission::onEventTCPSocketError(int errorCode)
{
	MELOG(MELOG_INFO, "CGPLoginMission::onEventTCPSocketError: connect error code[%d] \n", errorCode);
	if (mIGPLoginMissionSink)
		mIGPLoginMissionSink->onGPError(errorCode);
}

bool CGPLoginMission::onEventTCPSocketRead(int main, int sub, void* data, int size) 
{
	MELOG(MELOG_INFO, "onEventTCPSocketRead main:%d sub:%d size:%d \n", main, sub, size);
	switch (main)
	{
	case MDM_GP_LOGON:			
		return onSocketMainLogon(sub, data, size);
	case MDM_GP_SERVER_LIST:	return onSocketMainServerList(sub, data, size);
	default:
		break;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
// 登陆信息
bool CGPLoginMission::onSocketMainLogon(int sub, void* data, int size)
{
	switch (sub)
	{
		//登录成功
	case SUB_GP_LOGON_SUCCESS:		return onSocketSubLogonSuccess(data, size);
		//登录失败
	case SUB_GP_LOGON_FAILURE:		return onSocketSubLogonFailure(data, size);
		//登录失败
	case SUB_GP_VALIDATE_MBCARD:	return onSocketSubLogonValidateMBCard(data, size);
		//升级提示
	case SUB_GP_UPDATE_NOTIFY:		return onSocketSubUpdateNotify(data, size);
		//登录完成
	case SUB_GP_LOGON_FINISH:		return onSocketSubLogonFinish(data, size);
		//登录完成
	case SUB_GP_BASEENSURE_RESULT:		return onSocketBaseEnsureResult(data, size);
	}

	return false;
}

//登录成功
bool CGPLoginMission::onSocketSubLogonSuccess(void* data, int size)
{
	MELOG(MELOG_INFO, "Logon Success.......................................\n");
	PACKET_AIDE_DATA(data);

	//变量定义
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();

	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();
	tagUserInsureInfo * pUserInsureInfo = pGlobalUserInfo->GetUserInsureInfo();


	CMD_GP_LogonSuccess* lpLogonSuccess = (CMD_GP_LogonSuccess*)data;

	//保存信息
	pGlobalUserData->wFaceID = packet.read2Byte();
	pGlobalUserData->dwUserID = packet.read4Byte();
	pGlobalUserData->dwGameID = packet.read4Byte();
	pGlobalUserData->dwGroupID = packet.read4Byte();
	pGlobalUserData->dwCustomID = packet.read4Byte();
	pGlobalUserData->dwUserMedal = packet.read4Byte();
	pGlobalUserData->dwExperience = packet.read4Byte();
	pGlobalUserData->dwLoveLiness = packet.read4Byte();
	pGlobalUserData->dwMasterRight = packet.read4Byte();

	//用户成绩
	pUserInsureInfo->lUserScore = packet.read8Byte();
	pUserInsureInfo->lUserInsure = packet.read8Byte();

	pGlobalUserData->cbGender = packet.readByte();
	pGlobalUserData->cbMoorMachine = packet.readByte();

	std::string sAccount = packet.readStringFromAnsi_2(LEN_ACCOUNTS);
	std::string sNickname = packet.readStringFromAnsi_2(LEN_NICKNAME);
	std::string sGroupName = packet.readStringFromAnsi_2(LEN_GROUP_NAME);

	//std::string sAccount = packet.readStringFromAnsi(LEN_ACCOUNTS);
	//std::string sNickname = packet.readStringFromAnsi(LEN_NICKNAME);
	//std::string sGroupName = packet.readStringFromAnsi(LEN_GROUP_NAME);


	//帐号信息
	if (sNickname.length() <= 0 || sNickname == "" || sNickname[0] == '\0')
	{
		sNickname = "ID ";
		char szBuf[32] = { 0 };
		sprintf(szBuf, "%04d", pGlobalUserData->dwGameID/100);
		sNickname += szBuf;
		sNickname += "**";
	}
	strncpy(pGlobalUserData->szAccounts, sAccount.c_str(), countarray(pGlobalUserData->szAccounts));
	strncpy(pGlobalUserData->szNickName, sNickname.c_str(), countarray(pGlobalUserData->szNickName));

	pGlobalUserData->cbDailiOrder = packet.readByte(); //0普通 1代理
	pGlobalUserData->cbUserType = packet.readByte();

	packet.readByte();
	packet.readByte();
	pGlobalUserData->lRoomCard = packet.read4Byte();

	while (size > packet.getPosition())
	{
		//提取数据
		word wDataSize = packet.read2Byte();
		word wDataDescribe = packet.read2Byte();
		if (wDataDescribe == 0) break;

		//提取数据
		switch (wDataDescribe)
		{
			case DTP_GP_MEMBER_INFO:	//会员信息
			{

				pGlobalUserData->cbMemberOrder = packet.readByte();
				pGlobalUserData->MemberOverDate.wYear = packet.read2Byte();
				pGlobalUserData->MemberOverDate.wMonth = packet.read2Byte();
				pGlobalUserData->MemberOverDate.wDayOfWeek = packet.read2Byte();
				pGlobalUserData->MemberOverDate.wDay = packet.read2Byte();
				pGlobalUserData->MemberOverDate.wHour = packet.read2Byte();
				pGlobalUserData->MemberOverDate.wMinute = packet.read2Byte();
				pGlobalUserData->MemberOverDate.wSecond = packet.read2Byte();
				pGlobalUserData->MemberOverDate.wMilliseconds = packet.read2Byte();

				break;
			}
			case DTP_GP_UNDER_WRITE:	//个性签名
			{
				std::string sUnderWrite = packet.readString(wDataSize / 2);
				strncpy(pGlobalUserData->szUnderWrite, sUnderWrite.c_str(), countarray(pGlobalUserData->szUnderWrite));
				break;
			}
			case DTP_GP_ICON_URL:
			{
				std::string sUrl = packet.readString(wDataSize / 2);
				strncpy(pGlobalUserData->szIconUrl, sUrl.c_str(), countarray(pGlobalUserData->szIconUrl));
				break;
			}
		}
	}

	//本地加载
	if (pGlobalUserData->dwCustomID!=0)
	{
		//CCustomFaceManager * pCustomFaceManager=CCustomFaceManager::GetInstance();
		//pCustomFaceManager->LoadUserCustomFace(pLogonSuccess->dwUserID,pLogonSuccess->dwCustomID,pGlobalUserData->CustomFaceInfo);
	}

	if (mIGPLoginMissionSink)
		mIGPLoginMissionSink->onGPLoginSuccess();

	return true;
}

//登录失败
bool CGPLoginMission::onSocketSubLogonFailure(void* data, int size)
{
	MELOG(MELOG_INFO, "Logon Failure...............................\n");
	int baseSize = 4;
	//效验参数
	ASSERT(size>=baseSize);
	if (size<baseSize) return false;

	PACKET_AIDE_DATA(data);
	int lResultCode	= packet.read4Byte();
	std::string str	= packet.readString((size-baseSize)/2);

	//关闭连接
	stop();

	//显示消息
	if (mIGPLoginMissionSink)
		mIGPLoginMissionSink->onGPLoginFailure(str.c_str());

	return true;
}

//升级提示
bool CGPLoginMission::onSocketSubUpdateNotify(void* data, int size)
{
	MELOG(MELOG_INFO, "Update Notify...............................\n");
	//效验参数
	ASSERT(size>=6);
	if (size<6) return false;

	PACKET_AIDE_DATA(data);
	byte cbMustUpdate = packet.readByte();
	byte cbAdviceUpdate = packet.readByte();
	dword dwCurrentVersion = packet.read4Byte();

	std::string sURL;

	while (size > packet.getPosition())
	{
		//提取数据
		word wDataSize = packet.read2Byte();
		word wDataDescribe = packet.read2Byte();

		if (wDataDescribe==0) break;

		////提取数据
		//switch (wDataDescribe)
		//{
		////case DTP_GP_URL_DOWNLOAD:	//下载路径
		////	{
		////		sURL = packet.readString(wDataSize/2);
		////		break;
		////	}		
		//default:
		//	break;
		//}
	}

	// 关闭连接升级
	stop();


	//提示消息
	if ((cbMustUpdate==TRUE)||(cbAdviceUpdate==TRUE))
	{
		//构造提示
		if (cbMustUpdate==FALSE)
		{
			//构造提示
			CGDialog("系统提示", 11, CGDLG_MB_OK | CGDLG_MB_CANCEL,
				nullptr,
				[&](){ // 取消操作,继续游戏
					if (MISSION_LOGIN_ACCOUNT==mMissionType)
						mLoginAccount.cbValidateFlags = MB_VALIDATE_FLAGS;
					else 
						mLoginGameID.cbValidateFlags = MB_VALIDATE_FLAGS;
					// 执行登陆
					start();
				});
			return true;
		}
		else
		{
			//构造提示
			CGDialog("系统提示", 12, CGDLG_MB_OK | CGDLG_MB_CANCEL,
				[&](){ 
					// 执行游戏下载
				},
				nullptr);
			return true;
		}
	}

	return true;
}

//登录失败(密保卡)
bool CGPLoginMission::onSocketSubLogonValidateMBCard(void* data, int size)
{
	MELOG(MELOG_INFO, "Logon Validate MBCard Failure...............................\n");
	//效验参数
	ASSERT(size==4);
	if (size!=4) return false;

	PACKET_AIDE_DATA(data);
	uint uMBCardID = packet.read4Byte();

	stop();

	CGDialog("系统提示", 13, CGDLG_MB_OK);
	return true;
}

//登录完成
bool CGPLoginMission::onSocketSubLogonFinish(void* data, int size)
{
	MELOG(MELOG_INFO, "Logon Finish.................................. \n");
	int baseSize = 8;
	//效验参数
	ASSERT(size==baseSize);
	if (size!=baseSize) return false;

	//变量定义
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();

	PACKET_AIDE_DATA(data);
	word wIntermitTime = packet.read2Byte();
	word wOnLineCountTime = packet.read2Byte();
	pGlobalUserData->dwRoomExtData = packet.read4Byte();

	//变量定义
	CParameterGlobal * pParameterGlobal=CParameterGlobal::shared();

	//时间配置
	pParameterGlobal->m_wIntermitTime=wIntermitTime;
	pParameterGlobal->m_wOnLineCountTime=wOnLineCountTime;

	//变量定义
	//CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	//tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	////网络加载
	//if ((pGlobalUserData->dwCustomID!=0)&&(pGlobalUserData->CustomFaceInfo.dwDataSize==0L))
	//{
	//	CCustomFaceManager * pCustomFaceManager=CCustomFaceManager::GetInstance();
	//	pCustomFaceManager->LoadUserCustomFace(pGlobalUserData->dwUserID,pGlobalUserData->dwCustomID);
	//}


	//关闭处理(获取完基本信息了)
	stop();

	if (mIGPLoginMissionSink)
		mIGPLoginMissionSink->onGPLoginComplete();

	return true;
}

//////////////////////////////////////////////////////////////////////////
// 列表信息
bool CGPLoginMission::onSocketMainServerList(int sub, void* data, int size)
{
	switch (sub)
	{
	case SUB_GP_LIST_TYPE:		return onSocketListType(data, size);
	case SUB_GP_LIST_KIND:		return onSocketListKind(data, size);
	case SUB_GP_LIST_NODE:		return onSocketListNode(data, size);
	case SUB_GP_LIST_PAGE:		return onSocketListPage(data, size);
	case SUB_GP_LIST_SERVER:	return onSocketListServer(data, size);
	case SUB_GP_LIST_FINISH:	return onSocketListFinish(data, size);
	case SUB_GP_SERVER_FINISH:	return onSocketServerFinish(data, size);
	case SUB_GR_KINE_ONLINE:	return onSocketKindOnline(data, size);
	case SUB_GR_SERVER_ONLINE:	return onSocketServerOnline(data, size);
	case SUB_GR_ONLINE_FINISH:	return onSocketOnlineFinish(data, size);
	case SUB_GP_VIDEO_OPTION:	return onSocketVideoOption(data, size);
	case SUB_GP_LIST_CTSERVER:  return OnSubCustomServerList(data, size);
	case SUB_GP_LIST_CUSTSERVER:  return onSocketListCustomServer(data, size);
	case SUB_L2C_CUSTOMTABLE_LIST:	return onSocketCustomTableList(data, size);
	}

	return false;
}

//种类信息
bool CGPLoginMission::onSocketListType(void* data, int size)
{
	MELOG(MELOG_INFO, "List Type................................ \n");
	int itemSize = 38;//2+2+2+2+LEN_TYPE*2;			// 修改之后的话，应该是，2+2+2 + LEN_TYPE = 38
	//效验参数
	ASSERT(size%itemSize==0);
	if (size%itemSize!=0) return false;

	//变量定义
	int iItemCount=size/itemSize;
	PACKET_AIDE_DATA(data);

	//获取对象
	ASSERT(CServerListData::shared()!=0);
	CServerListData * pServerListData=CServerListData::shared();

	std::string sTypename;

	//更新数据
	for (int i=0;i<iItemCount;i++)
	{
		tagGameType GameType;
		GameType.wJoinID = packet.read2Byte();
		GameType.wSortID = packet.read2Byte();
		GameType.wTypeID = packet.read2Byte();
		//packet.read2Byte();			//wGameState
		sTypename = packet.readStringFromAnsi_2(LEN_TYPE);
		strncpy(GameType.szTypeName, sTypename.c_str(), countarray(GameType.szTypeName));

		MELOG(MELOG_INFO, "ListType:%s \n", GameType.szTypeName);
		pServerListData->InsertGameType(&GameType);
	}

	return true;
}

//类型信息
bool CGPLoginMission::onSocketListKind(void* data, int size)
{
	MELOG(MELOG_INFO, "List Kind..................................... \n");
	//int itemSize=156;		//2+2+2+2+2+2+4+4+4+4+LEN_KIND*2+LEN_PROCESS*2;
	int itemSize = 82;		//2+2+2+2+2+4+4+LEN_KIND + LEN_PROCESS;
	//效验参数
	ASSERT(size%itemSize==0);
	if (size%itemSize!=0) return false;

	//变量定义
	int iItemCount=size/itemSize;

	//获取对象
	ASSERT(CServerListData::shared()!=0);
	CServerListData * pServerListData=CServerListData::shared();

	PACKET_AIDE_DATA(data);

	std::string str;

	//更新数据
	for (int i=0;i<iItemCount;i++)
	{
		tagGameKind GameKind;
		//游戏种类

		GameKind.wTypeID = packet.read2Byte();
		GameKind.wJoinID = packet.read2Byte();
		GameKind.wSortID = packet.read2Byte();
		GameKind.wKindID = packet.read2Byte();
		GameKind.wGameID = packet.read2Byte();
		//packet.read2Byte();//wGameState
		GameKind.dwOnLineCount = packet.read4Byte();
		//packet.read4Byte();//dwAndroidCount
		//packet.read4Byte();//wUnionNumbers
		GameKind.dwFullCount = packet.read4Byte();
		str = packet.readStringFromAnsi_2(LEN_KIND);
		strncpy(GameKind.szKindName, str.c_str(), countarray(GameKind.szKindName));
		str = packet.readStringFromAnsi_2(LEN_PROCESS);
		strncpy(GameKind.szProcessName, str.c_str(), countarray(GameKind.szProcessName));

		MELOG(MELOG_INFO, "ListKind kind:%d name:%s process:%s \n ", GameKind.wKindID, GameKind.szKindName, GameKind.szProcessName);
		pServerListData->InsertGameKind(&GameKind);
	}

	return true;
}

// 节点信息
bool CGPLoginMission::onSocketListNode(void* data, int size)
{
	MELOG(MELOG_INFO, "List Node............................................ \n");
	int itemSize=2+2+2+2+LEN_NODE*2;
	//效验参数
	ASSERT(size%itemSize==0);
	if (size%itemSize!=0) return false;

	//变量定义
	int iItemCount=size/itemSize;

	//获取对象
	ASSERT(CServerListData::shared()!=0);
	CServerListData * pServerListData=CServerListData::shared();

	PACKET_AIDE_DATA(data);
	std::string str;

	//更新数据
	for (int i=0;i<iItemCount;i++)
	{
		tagGameNode GameNode;
		GameNode.wKindID = packet.read2Byte();
		GameNode.wJoinID = packet.read2Byte();
		GameNode.wSortID = packet.read2Byte();
		GameNode.wNodeID = packet.read2Byte();
		str = packet.readString(LEN_NODE);
		strncpy(GameNode.szNodeName, str.c_str(), countarray(GameNode.szNodeName));
		MELOG(MELOG_INFO, "NodeName:%s \n", GameNode.szNodeName);
		pServerListData->InsertGameNode(&GameNode);
	}

	return true;
}

// 页面信息
bool CGPLoginMission::onSocketListPage(void* data, int size)
{
	MELOG(MELOG_INFO, "List Page..................................... \n");
	int itemSize=2+2+2+2+2+LEN_PAGE*2;
	//效验参数
	ASSERT(size%itemSize==0);
	if (size%itemSize!=0) return false;

	//变量定义
	int iItemCount=size/itemSize;

	//获取对象
	ASSERT(CServerListData::shared()!=0);
	CServerListData * pServerListData=CServerListData::shared();

	PACKET_AIDE_DATA(data);
	std::string str;

	//更新数据
	for (int i=0;i<iItemCount;i++)
	{
		tagGamePage GamePage;
		GamePage.wPageID = packet.read2Byte();
		GamePage.wKindID = packet.read2Byte();
		GamePage.wNodeID = packet.read2Byte();
		GamePage.wSortID = packet.read2Byte();
		GamePage.wOperateType = packet.read2Byte();

		str	= packet.readString(LEN_PAGE);
		strncpy(GamePage.szDisplayName, str.c_str(), countarray(GamePage.szDisplayName));
		MELOG(MELOG_INFO, "ListPage:%s \n", GamePage.szDisplayName);
		pServerListData->InsertGamePage(&GamePage);
	}

	return true;
}

// 房间列表
bool CGPLoginMission::onSocketListServer(void* data, int size)
{
	MELOG(MELOG_INFO, "List Server......................................... \n");
	int iSize = sizeof(tagGameServer);
	ASSERT(size % iSize == 0);
	
	//获取对象
	ASSERT(CServerListData::shared()!=0);
	CServerListData * pServerListData=CServerListData::shared();

	//变量定义
	int iItemCount = size / sizeof(tagGameServer);
	
	PACKET_AIDE_DATA(data);
	std::string str;


// 		word	 wKindID;							//名称索引
// 		word	 wNodeID;							//节点索引
// 		word	 wSortID;							//排序索引
// 		word	 wServerID;							//房间索引
// 		word	 wServerPort;						//房间端口
// 		word	 wGameState;						//游戏状态[07/10/2015 yaoni]
// 		dword	 dwOnLineCount;						//在线人数
// 		dword	 dwAndroidCount;					//机器人数
// 		dword	 dwFullCount;						//满员人数
// 		dword	 dwServerRule;						//房间规则[9/6/2015 zby]
// 		word	 wServerType;						//房间类型
// 		char	 szServerAddr[32 * 2];				//房间名称
// 		char	 szServerName[LEN_SERVER * 2];		//房间名称
// 		uint32	 lCellScore;						//单位积分
// 		SCORE	 lRestrictScore;					//限制积分
// 		SCORE	 lMinTableScore;					//最低积分
// 		SCORE	 lMinEnterScore;					//最低积分
// 		SCORE	 lMaxEnterScore;					//最高积分

// 		struct tagGameServer
// 		{
// 			WORD							wKindID;							//名称索引
// 			WORD							wNodeID;							//节点索引
// 			WORD							wSortID;							//排序索引
// 			WORD							wServerID;							//房间索引
// 			WORD							wServerPort;						//房间端口
// 			DWORD							dwOnLineCount;						//在线人数
// 			DWORD							dwFullCount;						//满员人数
// 			TCHAR							szServerAddr[32];					//房间名称
// 			TCHAR							szServerName[LEN_SERVER];			//房间名称
// 		};


	for (int i=0;i<iItemCount;i++)
	{
		tagGameServer GameServer;
		GameServer.wKindID = packet.read2Byte();
		GameServer.wNodeID = packet.read2Byte();
		GameServer.wSortID = packet.read2Byte();
		GameServer.wServerID = packet.read2Byte();
		GameServer.wServerPort = packet.read2Byte();
		packet.read2Byte();//wGameState
		GameServer.dwOnLineCount = packet.read4Byte();
		packet.read4Byte();//dwAndroidCount
		GameServer.dwFullCount = packet.read4Byte();
		packet.read4Byte();//dwServerRule
		packet.read2Byte();//wServerType

		str = packet.readString(LEN_SERVERADDR*2);
		strncpy(GameServer.szServerAddr, str.c_str(), countarray(GameServer.szServerAddr));

		str = packet.readString(LEN_SERVER*2);
		strncpy(GameServer.szServerName, str.c_str(), countarray(GameServer.szServerName));

		GameServer.lCellScore		= packet.read4Byte();//lCellScore
		GameServer.lRestrictScore	= packet.read8Byte(); //限制积分
		GameServer.lMinTableScore	= packet.read8Byte();
		GameServer.lMinEnterScore	= packet.read8Byte(); //最低积分
		GameServer.lMaxEnterScore	= packet.read8Byte();

		MELOG(MELOG_INFO, "ListServer address:%s server:%s \n", GameServer.szServerAddr, GameServer.szServerName);
		pServerListData->InsertGameServer(&GameServer);
	}

	return true;
}

// 列表完成
bool CGPLoginMission::onSocketListFinish(void* data, int size)
{
	MELOG(MELOG_INFO, "List Finish........................................ \n");
	ASSERT(CServerListData::shared()!=0);
	if (CServerListData::shared()!=0) 
	{
		CServerListData::shared()->OnEventListFinish();
	}
	return true;
}

//房间完成
bool CGPLoginMission::onSocketServerFinish(void* data, int size)
{
	MELOG(MELOG_INFO, "Server Finish......................................... \n");
	//效验数据
	ASSERT(size%sizeof(word)==0);
	if (size%sizeof(word)!=0) return false;

	//获取对象
	ASSERT(CServerListData::shared()!=0);
	CServerListData * pServerListData=CServerListData::shared();

	//任务处理
	for (uint i=0;i<(size/sizeof(word));i++)
	{
		uint16 kind = ((uint16 *)data)[i];
		mKindWaitList.remove(kind);
		pServerListData->OnEventKindFinish(kind);
	}

	//关闭连接
	stop();
	return true;
}

//////////////////////////////////////////////////////////////////////////
// 在线更新
//////////////////////////////////////////////////////////////////////////
//类型在线
bool CGPLoginMission::onSocketKindOnline(void* data, int size)
{
	MELOG(MELOG_INFO, "Kind Online............................................ \n");
	//变量定义
	PACKET_AIDE_DATA(data);
	word wKindCount = packet.read2Byte();
	//获取对象
	CServerListData * pServerListData=CServerListData::shared();

	//设置人数
	for (int i=0;i<wKindCount;i++)
	{
		word wKindID = packet.read2Byte();
		dword dwOnLineCount = packet.read4Byte();
		pServerListData->SetKindOnLineCount(wKindID,dwOnLineCount);
	}

	return true;
}

//房间在线
bool CGPLoginMission::onSocketServerOnline(void* data, int size)
{
	MELOG(MELOG_INFO, "Server Online........................................... \n");
	//变量定义
	PACKET_AIDE_DATA(data);
	word wServerCount=packet.read2Byte();

	//获取对象
	CServerListData * pServerListData=CServerListData::shared();

	//设置人数
	for (int i=0;i<wServerCount;i++)
	{
		word wServerID = packet.read2Byte();
		dword dwOnLineCount = packet.read4Byte();
		pServerListData->SetServerOnLineCount(wServerID,dwOnLineCount);
	}
	return true;
}

// 在线更新完成
bool CGPLoginMission::onSocketOnlineFinish(void* data, int size)
{
	MELOG(MELOG_INFO, "Online Update Finish..................................... \n");
	//获取对象
	CServerListData * pServerListData=CServerListData::shared();
	//完成通知
	pServerListData->SetServerOnLineFinish();

	//关闭连接
	stop();
	return true;
}

//////////////////////////////////////////////////////////////////////////

//视频配置
bool CGPLoginMission::onSocketVideoOption(void* data, int size)
{
	MELOG(MELOG_INFO, "Video Option......................................... \n");
	//效验数据
	ASSERT(size==6);
	if(size!=6) return false;

	//变量定义
	PACKET_AIDE_DATA(data);
	word wAVServerPort = packet.read2Byte();
	dword dwAVServerAddr = packet.read4Byte();

	//转化地址
	byte * pClientAddr=(byte *)&dwAVServerAddr;
	PLAZZ_PRINTF("onSocketVideoOption ip:%d.%d.%d.%d port:%d", 
		pClientAddr[0],pClientAddr[1],pClientAddr[2],pClientAddr[3],
		wAVServerPort);
	////获取对像
	//CPlatformFrame *pPlatfromFrame=CPlatformFrame::GetInstance();
	//if(pPlatfromFrame==0) return false;

	//pPlatfromFrame->SetVideoOption(pAVServerOption->wAVServerPort,pAVServerOption->dwAVServerAddr);
	return true;
}

//房间列表
bool CGPLoginMission::OnSubCustomServerList(void* data, int size)
{
	MELOG(MELOG_INFO, "custom server list........................................ \n");
	ASSERT(size % sizeof(tagGameServer) == 0);

	//获取对象
	ASSERT(CServerListData::shared() != 0);
	CServerListData * pServerListData = CServerListData::shared();

	//变量定义
	int iItemCount = size / sizeof(tagGameServer);

	PACKET_AIDE_DATA(data);
	std::string str;

	for (int i = 0; i<iItemCount; i++)
	{
		tagGameServer GameServer;
		GameServer.wKindID = packet.read2Byte();
		GameServer.wNodeID = packet.read2Byte();
		GameServer.wSortID = packet.read2Byte();
		GameServer.wServerID = packet.read2Byte();
		GameServer.wServerPort = packet.read2Byte();
		packet.read2Byte();//wGameState
		GameServer.dwOnLineCount = packet.read4Byte();
		packet.read4Byte();//dwAndroidCount
		GameServer.dwFullCount = packet.read4Byte();
		packet.read4Byte();//dwServerRule
		packet.read2Byte();//wServerType

		str = packet.readStringFromAnsi_2(LEN_SERVERADDR);
		strncpy(GameServer.szServerAddr, str.c_str(), countarray(GameServer.szServerAddr));

		str = packet.readStringFromAnsi_2(LEN_SERVER);
		strncpy(GameServer.szServerName, str.c_str(), countarray(GameServer.szServerName));

		GameServer.lCellScore = packet.read4Byte();//lCellScore
		GameServer.lRestrictScore = packet.read8Byte(); //限制积分
		GameServer.lMinTableScore = packet.read8Byte();
		GameServer.lMinEnterScore = packet.read8Byte(); //最低积分
		GameServer.lMaxEnterScore = packet.read8Byte();

		MELOG(MELOG_INFO, "ListServer address:%s server:%s \n", GameServer.szServerAddr, GameServer.szServerName);
		pServerListData->addCustomServer(GameServer);
	}

	return true;
}

//自定义房间列表
bool CGPLoginMission::onSocketListCustomServer(void* data, int size)
{
	MELOG(MELOG_INFO, "list custom server ........................................ \n");
	ASSERT(size % sizeof(tagGameServer) == 0);

	//获取对象
	ASSERT(CServerListData::shared() != 0);
	CServerListData * pServerListData = CServerListData::shared();

	//变量定义
	int iItemCount = size / sizeof(tagGameServer);

	PACKET_AIDE_DATA(data);
	std::string str;

	for (int i = 0; i<iItemCount; i++)
	{
		tagGameServer GameServer;
		GameServer.wKindID = packet.read2Byte();
		GameServer.wNodeID = packet.read2Byte();
		GameServer.wSortID = packet.read2Byte();
		GameServer.wServerID = packet.read2Byte();
		GameServer.wServerPort = packet.read2Byte();
		packet.read2Byte();//wGameState
		GameServer.dwOnLineCount = packet.read4Byte();
		packet.read4Byte();//dwAndroidCount
		GameServer.dwFullCount = packet.read4Byte();
		packet.read4Byte();//dwServerRule
		packet.read2Byte();//wServerType

		str = packet.readStringFromAnsi_2(LEN_SERVERADDR);
		strncpy(GameServer.szServerAddr, str.c_str(), countarray(GameServer.szServerAddr));

		str = packet.readStringFromAnsi_2(LEN_SERVER);
		strncpy(GameServer.szServerName, str.c_str(), countarray(GameServer.szServerName));

		GameServer.lCellScore = packet.read4Byte();//lCellScore
		GameServer.lRestrictScore = packet.read8Byte(); //限制积分
		GameServer.lMinTableScore = packet.read8Byte();
		GameServer.lMinEnterScore = packet.read8Byte(); //最低积分
		GameServer.lMaxEnterScore = packet.read8Byte();

		MELOG(MELOG_INFO, "ListServer address:%d server:%s \n", GameServer.dwFullCount, GameServer.szServerName);
		pServerListData->addCustomServer(GameServer);
	}

	return true;
}

//请求自己创建的房间列表
bool CGPLoginMission::onSocketCustomTableList(void* data, int size)
{
	MELOG(MELOG_INFO, "Custom Table List ........................................ \n");
	ASSERT(size % sizeof(tagGameServer) == 0);

	//获取对象
	ASSERT(CServerListData::shared() != 0);
	CServerListData * pServerListData = CServerListData::shared();
	pServerListData->rmvMyAllCustomTables();

	//变量定义
	int iItemCount = size / sizeof(tagGameServer);

	PACKET_AIDE_DATA(data);
	std::string str;

	for (int i = 0; i<iItemCount; i++)
	{
		tagGameServer GameServer;
		GameServer.wKindID = packet.read2Byte();
		GameServer.wNodeID = packet.read2Byte();
		GameServer.wSortID = packet.read2Byte();
		GameServer.wServerID = packet.read2Byte();
		GameServer.wServerPort = packet.read2Byte();
		packet.read2Byte();//wGameState
		GameServer.dwOnLineCount = packet.read4Byte();
		packet.read4Byte();//dwAndroidCount
		GameServer.dwFullCount = packet.read4Byte();
		packet.read4Byte();//dwServerRule
		packet.read2Byte();//wServerType

		str = packet.readString(LEN_SERVERADDR);
		strncpy(GameServer.szServerAddr, str.c_str(), countarray(GameServer.szServerAddr));

		str = packet.readString(LEN_SERVER);
		strncpy(GameServer.szServerName, str.c_str(), countarray(GameServer.szServerName));

		GameServer.lCellScore = packet.read4Byte();//lCellScore
		GameServer.lRestrictScore = packet.read8Byte(); //限制积分
		GameServer.lMinTableScore = packet.read8Byte();
		GameServer.lMinEnterScore = packet.read8Byte(); //最低积分
		GameServer.lMaxEnterScore = packet.read8Byte();

		MELOG(MELOG_INFO, "Self ListServer address:%d server:%s \n", GameServer.dwFullCount, GameServer.szServerName);
		pServerListData->addMyCustomTable(GameServer);
	}

	return true;
}

bool CGPLoginMission::onSocketBaseEnsureResult(void* data, int size)
{
	MELOG(MELOG_INFO, "BaseEnsureResult...............................\n");
	int baseSize = 9;
	//效验参数
	ASSERT(size >= baseSize);
	if (size<baseSize) return false;

	PACKET_AIDE_DATA(data);
	bool bSuccessed = packet.readByte();
	SCORE lGameScore = packet.read8Byte();
	std::string str = packet.readString((size - baseSize) / 2);

	if (bSuccessed)
	{
		//获取对象
		CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
		tagUserInsureInfo * pUserInsureInfo = pGlobalUserInfo->GetUserInsureInfo();
		//设置游戏币
		pUserInsureInfo->lUserScore = lGameScore;
	}
	
	//关闭连接
	stop();

	//显示消息
	if (mIGPLoginMissionSink)
		mIGPLoginMissionSink->onGPBaseEnsureComplete(bSuccessed, str.c_str());

	return true;
}