#include "CServerItem.h"
#include "MELog.h"
//////////////////////////////////////////////////////////////////////////
//
int __gServerItemRefCount = 0;
IServerItem* __gServerItem = 0;

IServerItem* IServerItem::create()
{
	if (__gServerItemRefCount == 0)
	{
		__gServerItem = new CServerItem();
	}

	__gServerItemRefCount++;
	PLAZZ_PRINTF("IServerItem::create ref:%d\n", __gServerItemRefCount);

	return __gServerItem;
}

void IServerItem::destory()
{
	if (__gServerItemRefCount > 0)
	{
		__gServerItemRefCount--;
		if (__gServerItemRefCount <= 0)
		{
			__gServerItemRefCount = 0;
			delete __gServerItem;
			__gServerItem = 0;
		}
	}
	PLAZZ_PRINTF("IServerItem::destory ref:%d\n", __gServerItemRefCount);

}

IServerItem* IServerItem::get()
{
	return __gServerItem;
}

//////////////////////////////////////////////////////////////////////////
CServerItem::CServerItem() 
	: mReqTableID(INVALID_TABLE)
	, mReqChairID(INVALID_CHAIR)
	, mFindTableID(INVALID_TABLE)
	, mIsGameReady(false)
	, m_MobileUser(false)
	, m_dwCustTUUID(0)
	, mMeUserItem(0)
	, mIServerItemSink(0)
	, mIChatSink(0)
	, mIStringMessageSink(0)
	, mSocketEngine(0)
	, mServiceStatus(ServiceStatus_Unknow)
{
	mExitInfo = "";
	mIsQuickSitDown=false;
	memset(&mUserAttribute,   0, sizeof(mUserAttribute));
	memset(&mServerAttribute, 0, sizeof(mServerAttribute));
	mSocketEngine = ISocketEngine::create();
	mUserManager  = new CPlazaUserManager();
	mUserManager->SetUserManagerSink(this);
	mSocketEngine->setSocketEngineSink(this);
}

CServerItem::~CServerItem()
{
	IntermitConnect(true, true);
	mIServerItemSink=0;
	mUserManager->SetUserManagerSink(0);
	mSocketEngine->setSocketEngineSink(0);
	ISocketEngine::destory(mSocketEngine);
	mSocketEngine = 0;
	SafeDelete(mUserManager);
	mUserManager  = 0;
}

//////////////////////////////////////////////////////////////////////////
//配置接口

//设置接口
bool CServerItem::SetServerItemSink(IServerItemSink* pIServerItemSink)
{
	mIServerItemSink = pIServerItemSink;
	return true;
}

//设置接口
bool CServerItem::SetChatSink(IChatSink* pIChatSink)
{
	PLAZZ_PRINTF("CServerItem::SetChatSink\n");
	mIChatSink = pIChatSink;
	return true;
}

//设置接口
bool CServerItem::SetStringMessageSink(IStringMessageSink* pIStringMessageSink)
{
	mIStringMessageSink = pIStringMessageSink;
	return true;
}

//////////////////////////////////////////////////////////////////////////
//属性接口
//用户属性
const tagUserAttribute& CServerItem::GetUserAttribute() const
{
	return mUserAttribute;
}

//房间属性
const tagServerAttribute& CServerItem::GetServerAttribute() const 
{
	return mServerAttribute;
}

//服务状态
enServiceStatus CServerItem::GetServiceStatus()
{
	return mServiceStatus;
}

//是否服务状态
bool CServerItem::IsService()
{
	return GetServiceStatus() == ServiceStatus_ServiceIng;
}

//自己状态
bool CServerItem::IsPlayingMySelf()
{
	return ((mMeUserItem!=0)&&(mMeUserItem->GetUserStatus()==US_PLAYING));
}

//自己状态
int  CServerItem::GetUserStatus()
{
	if (mMeUserItem != 0)
		return mMeUserItem->GetUserStatus();
	return US_NULL;
}

//是否自定义房间
bool CServerItem::isCustomServer() const
{
	std::string strServerName = mServerAttribute.szServerName;
	if (strServerName.find("CustomSvr") != std::string::npos)
		return true;
	return false;
}

//设置状态
void CServerItem::SetServiceStatus(enServiceStatus ServiceStatus)
{
	//设置变量
	mServiceStatus=ServiceStatus;
	return;
}

//配置房间
bool CServerItem::SetServerAttribute(CGameServerItem * pGameServerItem,word wAVServerPort,dword dwAVServerAddr)
{
	//房间属性
	CGameKindItem * pGameKindItem=pGameServerItem->m_pGameKindItem;
	memcpy(&mGameKind,&pGameKindItem->m_GameKind,sizeof(mGameKind));
	memcpy(&mGameServer,&pGameServerItem->m_GameServer,sizeof(mGameServer));

	mServerAttribute.wKindID		= mGameServer.wKindID;
	mServerAttribute.wServerID		= mGameServer.wServerID;
	//mServerAttribute.wServerType	= mGameServer.wServerType;
	//mServerAttribute.dwServerRule	= mGameServer.dwServerRule;
	mServerAttribute.wAVServerPort	= wAVServerPort;
	mServerAttribute.dwAVServerAddr	= dwAVServerAddr;
	strncpy(mServerAttribute.szServerName, mGameServer.szServerName, LEN_SERVER);

	CParameterGlobal * pParameterGlobal=CParameterGlobal::shared();
	//加载配置
	mParameterGame=pParameterGlobal->GetParameterGame(&mGameKind);
	mParameterServer=pParameterGlobal->GetParameterServer(&mGameServer);

	return true;
}

//////////////////////////////////////////////////////////////////////////
//连接接口

//配置房间
bool CServerItem::ConnectServer(CGameServerItem * pGameServerItem,word wAVServerPort,dword dwAVServerAddr)
{
	if (mServiceStatus != ServiceStatus_Unknow &&
		mServiceStatus != ServiceStatus_NetworkDown)
	{
		CGDialog("系统提示", 1, CGDLG_MB_OK, nullptr, nullptr);
		return false;
	}

	//房间属性
	SetServerAttribute(pGameServerItem, wAVServerPort, dwAVServerAddr);

	//关闭判断
	ASSERT(mServerAttribute.wServerID!=0);
	if (mServerAttribute.wServerID==0)
	{
		SetServiceStatus(ServiceStatus_Unknow);
		CGDialog("系统提示", 2, CGDLG_MB_OK, nullptr, nullptr);
		return false;
	}

	MELOG(MELOG_INFO, "flow->CServerItem::ConnectServer connect ...\n");

	//创建组件	开始连接 具体的游戏服务器了
	if (!mSocketEngine->connect(mGameServer.szServerAddr, mGameServer.wServerPort))
	{
		CGDialog("系统提示", 3, CGDLG_MB_OK, nullptr, nullptr);
		return false;
	}

	PLAZZ_PRINTF("flow->CServerItem::ConnectServer entering...");
	//设置状态
	SetServiceStatus(ServiceStatus_Entering);
	return true;
}

//中断连接
bool CServerItem::IntermitConnect(bool force, bool bExitGame)
{	
	if (mServiceStatus==ServiceStatus_Unknow ||
		mServiceStatus==ServiceStatus_NetworkDown)
		return false;

	PLAZZ_PRINTF("flow->CServerItem::IntermitConnect 中断连接 bExitGame =%d ", bExitGame);

	if (IsService())
	{
		if(IClientKernel::get())
		{
			IClientKernel::get()->Intermit("", bExitGame);
		}
	}

	//设置状态
	SetServiceStatus(ServiceStatus_NetworkDown);

	mSocketEngine->disconnect();
	mReqTableID		= INVALID_TABLE;
	mReqChairID		= INVALID_CHAIR;
	mFindTableID	= INVALID_TABLE;
	mIsGameReady	= false;
	mExitInfo		= "";
	mMeUserItem		= 0;
	mUserManager->ResetUserItem();
	return true;
}

//////////////////////////////////////////////////////////////////////////
//网络接口

//发送函数
bool CServerItem::SendSocketData(word wMainCmdID, word wSubCmdID)
{
	return SendSocketData(wMainCmdID, wSubCmdID, 0, 0);
}

//发送函数
bool CServerItem::SendSocketData(word wMainCmdID, word wSubCmdID, void * data, word dataSize)
{
	return mSocketEngine->send(wMainCmdID, wSubCmdID, (unsigned char*)data, dataSize);
}


//发送登录
bool CServerItem::SendLogonPacket()
{
	PLAZZ_PRINTF(("flow->CServerItem::SendLogonPacket 发送登录 "));
	//变量定义
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

// 	DWORD							wGameID;							//游戏标识
// 	DWORD							dwProcessVersion;					//进程版本
// 	BYTE                            cbDeviceType;                       //设备类型
// 	WORD                            wBehaviorFlags;                     //行为标识
// 	WORD                            wPageTableCount;                    //分页桌数
// 	DWORD							dwUserID;							//用户 I D
// 	TCHAR							szPassword[LEN_MD5];				//登录密码
// 	TCHAR							szMachineID[LEN_MACHINE_ID];		//机器标识

	//变量定义
	SetMobileUser(false);
	PACKET_AIDE_SIZE(512);

	packet.write4Byte(pGlobalUserData->dwGameID);//wGameID;							//游戏标识
	packet.write4Byte(0);
	packet.writeByte(0);
	packet.write2Byte(0);		//行为标识
	packet.write2Byte(99);		// 分页桌数
	packet.write4Byte(pGlobalUserData->dwUserID);	//用户ID
	packet.writeString_UTF8(pGlobalUserData->szPassword, LEN_PASSWORD);
	packet.writeString_UTF8(DF::shared()->GetMachineID(), LEN_MACHINE_ID);
	//packet.writeString(pGlobalUserData->szPassword, LEN_PASSWORD);
	//packet.writeString(DF::shared()->GetMachineID(), LEN_MACHINE_ID);
// 	packet.write2Byte(mServerAttribute.wKindID);
// 	packet.writeByte(eDT_MOBILE);


// 	packet.write4Byte(DF::shared()->GetPlazaVersion()); 
// 	packet.write4Byte(DF::shared()->GetFrameVersion());
// 	packet.write4Byte(DF::shared()->GetGameVersion());
// 	packet.write4Byte(0); //IP
// 	packet.write4Byte(pGlobalUserData->dwUserID);
// 	packet.writeString(pGlobalUserData->szPassword, LEN_PASSWORD);
// 	packet.writeString(DF::shared()->GetMachineID(), LEN_MACHINE_ID);
// 	packet.write2Byte(mServerAttribute.wKindID);
// 	packet.writeByte(eDT_MOBILE);

	//发送数据
	
	SendSocketData(MDM_GR_LOGON, SUB_GR_LOGON_MOBILE, packet.getBuffer(), packet.getPosition());
	//SetMobileUser(true);
	//PACKET_AIDE_SIZE(512);
	//packet.write2Byte(mServerAttribute.wKindID);
	//packet.write4Byte(DF::shared()->GetGameVersion());

	//packet.writeByte(DF::shared()->GetDeviceType());
	//packet.write2Byte(1);
	//packet.write2Byte(3);

	//packet.write4Byte(pGlobalUserData->dwUserID);
	//packet.writeString(pGlobalUserData->szPassword, LEN_PASSWORD);
	//packet.writeString(DF::shared()->GetMachineID(), LEN_MACHINE_ID);

	////发送数据
	//SendSocketData(MDM_GR_LOGON, SUB_GR_LOGON_MOBILE, packet.getBuffer(), packet.getPosition());
	return true;
}

//发送配置
bool CServerItem::SendUserRulePacket()
{	
	PLAZZ_PRINTF(("flow->CServerItem::SendUserRulePacket 发送用户规则 "));
	//变量定义
	CParameterGlobal * pParameterGlobal=CParameterGlobal::shared();
	//变量定义
	byte cbRuleMask=0x00;

	//限制地址
	if (pParameterGlobal->m_bLimitSameIP==true)
		cbRuleMask|=UR_LIMIT_SAME_IP;

	//限制胜率
	if (mParameterGame->m_bLimitWinRate==true)
		cbRuleMask|=UR_LIMIT_WIN_RATE;
	

	//限制逃率
	if (mParameterGame->m_bLimitFleeRate==true)
		cbRuleMask|=UR_LIMIT_FLEE_RATE;
	
	//限制积分
	if (mParameterGame->m_bLimitGameScore==true)
		cbRuleMask|=UR_LIMIT_GAME_SCORE;

	PACKET_AIDE_SIZE(SIZE_PACK_DATA);
	packet.writeByte(cbRuleMask);
	packet.write2Byte(mParameterGame->m_wMinWinRate);
	packet.write2Byte(mParameterGame->m_wMaxFleeRate);
	packet.write4Byte(mParameterGame->m_lMaxGameScore);
	packet.write4Byte(mParameterGame->m_lMinGameScore);

	//携带密码
	if ((CServerRule::IsForfendLockTable(mServerAttribute.dwServerRule)==false)&&(mParameterServer->m_bTakePassword==true))
	{
		//const unsigned short* ucs2 = u8_2(mParameterServer->m_szPassword);
		//int ucs2len = ucs2_len(ucs2);
		//packet.write2Byte(ucs2len);
		//packet.write2Byte(DTP_GR_TABLE_PASSWORD);
		//packet.writeUTF16(ucs2, ucs2len);
		std::string ucs2 = u2l(mParameterServer->m_szPassword);
		int ucs2len = u2len(ucs2);
		packet.write2Byte(ucs2len);
		packet.write2Byte(DTP_GR_TABLE_PASSWORD);
		packet.writeString(ucs2, ucs2len);
	}

	//发送数据
	SendSocketData(MDM_GR_USER,SUB_GR_USER_RULE,packet.getBuffer(),packet.getPosition());
	return true;
}

//发送旁观
bool CServerItem::SendLookonPacket(word wTableID, word wChairID)
{
	PLAZZ_PRINTF(("flow->CServerItem::SendLookonPacket 发送旁观 "));
	PACKET_AIDE_SIZE(4);
	packet.write2Byte(wTableID);
	packet.write2Byte(wChairID);

	//发送数据
	SendSocketData(MDM_GR_USER,SUB_GR_USER_LOOKON, packet.getBuffer(), packet.getPosition());

	return true;
}

//发送坐下
bool CServerItem::SendSitDownPacket(word wTableID, word wChairID, const char* lpszPassword)
{
	//PLAZZ_PRINTF(("flow->CServerItem::SendSitDownPacket 发送坐下"));
	//const unsigned short* ucs2 = u8_2(lpszPassword);

	////变量定义
	//PACKET_AIDE_SIZE(128);
	//packet.write2Byte(wTableID);
	//packet.write2Byte(wChairID);
	//packet.writeUTF16(ucs2, LEN_PASSWORD);
	//	
	////发送数据
	//SendSocketData(MDM_GR_USER,SUB_GR_USER_SITDOWN, packet.getBuffer(), packet.getPosition());

	PLAZZ_PRINTF(("flow->CServerItem::SendSitDownPacket 发送坐下 "));
	std::string ucs2 = u2l(lpszPassword);		// 密码 ?

	//变量定义
	PACKET_AIDE_SIZE(128);
	packet.write2Byte(wTableID);	// 如果是快速加入的话。。0xFFFF
	packet.write2Byte(wChairID);	// 0xFFFF
	packet.writeString_UTF8(ucs2, LEN_PASSWORD);

	//发送数据  
	SendSocketData(MDM_GR_USER, SUB_GR_USER_SITDOWN, packet.getBuffer(), packet.getPosition());

	return true;
}

//发送起立
bool CServerItem::SendStandUpPacket(word wTableID, word wChairID, byte cbForceLeave)
{
	PLAZZ_PRINTF(("flow->CServerItem::SendStandUpPacket 发送起立 "));
	PACKET_AIDE_SIZE(10);
	packet.write2Byte(wTableID);
	packet.write2Byte(wChairID);
	packet.writeByte(cbForceLeave);

	//发送数据
	bool ret = SendSocketData(MDM_GR_USER,SUB_GR_USER_STANDUP, packet.getBuffer(), packet.getPosition());

	return true;
}

//发送刷新桌子
bool CServerItem::SendRefreshTabePacket(word wTableIdx)
{
	PLAZZ_PRINTF("flow->CServerItem::SendRefreshTabePacket 发送桌子刷新 ");

	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();

	PACKET_AIDE_SIZE(512);
	packet.write4Byte(pGlobalUserData->dwUserID);
	packet.write2Byte(wTableIdx);

	//发送数据
	SendSocketData(MDM_GR_USER, SUB_GR_USER_INFO_REQ, packet.getBuffer(), packet.getPosition());
	return true;
}

//发送聊天
bool CServerItem::SendUserChatPacket(dword dwTargetUserID, const char* pszChatString, dword dwColor)
{
	//PLAZZ_PRINTF(("flow->CServerItem::SendUserChatPacket 发送聊天"));

	//const unsigned short* ucs2 = u8_2(pszChatString);
	//int ucs2len = ucs2_len(ucs2);

	////构造信息
	//PACKET_AIDE_SIZE(512);
	//packet.write2Byte(ucs2len);
	//packet.write4Byte((dwColor&0xFFFF<<8)|(dwColor&0xFF0000>>16));
	//packet.write4Byte(dwTargetUserID);
	//packet.writeUTF16(ucs2, ucs2len);

	////发送命令
	//SendSocketData(MDM_GR_USER,SUB_GR_USER_CHAT, packet.getBuffer(), packet.getPosition());

	PLAZZ_PRINTF(("flow->CServerItem::SendUserChatPacket 发送聊天 "));

	std::string ucs2 = u2l(pszChatString);
	int ucs2len = u2len(ucs2);

	//构造信息
	PACKET_AIDE_SIZE(512);
	packet.write2Byte(ucs2len);
	packet.write4Byte((dwColor&0xFFFF<<8)|(dwColor&0xFF0000>>16));
	packet.write4Byte(dwTargetUserID);
	packet.writeString(ucs2, ucs2len);

	//发送命令
	SendSocketData(MDM_GR_USER,SUB_GR_USER_CHAT, packet.getBuffer(), packet.getPosition());
	return true;
}

//发送表情
bool CServerItem::SendExpressionPacket(dword dwTargetUserID, word wItemIndex)
{
	PLAZZ_PRINTF(("flow->CServerItem::SendExpressionPacket 发送表情 "));

	PACKET_AIDE_SIZE(6);
	packet.write2Byte(wItemIndex);
	packet.write4Byte(dwTargetUserID);

	//发送命令
	SendSocketData(MDM_GR_USER,SUB_GR_USER_EXPRESSION,packet.getBuffer(),packet.getPosition());

	return true;
}

//////////////////////////////////////////////////////////////////////////
//内部函数

//聊天效验
bool CServerItem::EfficacyUserChat(const char* pszChatString, word wExpressionIndex)
{
	//变量定义
	ASSERT(mMeUserItem!=0);
	byte cbMemberOrder=mMeUserItem->GetMemberOrder();
	byte cbMasterOrder=mMeUserItem->GetMasterOrder();

	//长度比较
	if(pszChatString != 0)
	{
		if(u8len(pszChatString) >= (LEN_USER_CHAT/2))
		{
			if (mIChatSink)
				mIChatSink->InsertSystemChat(26);
			return false;
		}
	}

	//房间配置
	if (CServerRule::IsForfendRoomChat(mServerAttribute.dwServerRule)&&(cbMasterOrder==0))
	{
		//原始消息
		if (wExpressionIndex==INVALID_WORD)
		{
			char szChatString[256]={0};
			sprintf(szChatString, "\n %s", pszChatString);
		
			if (mIChatSink)
				mIChatSink->InsertSystemChat(szChatString);
		}

		if (mIChatSink)
			mIChatSink->InsertSystemChat(25);

		return false;
	}

	//权限判断
	if (CUserRight::CanRoomChat(mUserAttribute.dwUserRight)==false)
	{
		//原始消息
		if (wExpressionIndex==INVALID_WORD)
		{
			char szChatString[256]={0};
			sprintf(szChatString, "\n %s", pszChatString);
			
			if (mIChatSink)
				mIChatSink->InsertSystemChat(szChatString);
		}

		//插入消息
		if (mIChatSink)
			mIChatSink->InsertSystemChat(24);

		return false;
	}

	//速度判断
	static dword dwChatTime=0;
	dword dwCurrentTime=(dword)time(0);
	if ((cbMasterOrder==0)&&((dwCurrentTime-dwChatTime)<=TIME_USER_CHAT))
	{
		//原始消息
		if (wExpressionIndex==INVALID_WORD)
		{
			char szChatString[256]={0};
			sprintf(szChatString, "\n %s", pszChatString);
			
			if (mIChatSink)
				mIChatSink->InsertSystemChat(szChatString);
		}

		//插入消息
		if (mIChatSink)
			mIChatSink->InsertSystemChat(23);

		return false;
	}

	//设置变量
	dwChatTime=dwCurrentTime;
	return true;
}

//桌子效验
bool CServerItem::EfficacyTableRule(word wTableID, word wChairID, bool bReqLookon, char strDescribe[256])
{
	if (isCustomServer())
		return true;

	//效验参数
	ASSERT(wTableID<mTableFrame.GetTableCount());
	ASSERT(wChairID<mTableFrame.GetChairCount());

	//状态过滤
	if (mServiceStatus!=ServiceStatus_ServiceIng) return false;
	if (wTableID>=mTableFrame.GetTableCount()) return false;
	if (wChairID>=mTableFrame.GetChairCount()) return false;

	//变量定义
	ASSERT(CParameterGlobal::shared()!=0);
	CParameterGlobal * pParameterGlobal=CParameterGlobal::shared();

	//变量定义
	ITable * pITable=mTableFrame.GetTableItem(wTableID);
	IClientUserItem * pITableUserItem=pITable->GetClientUserItem(wChairID);

	if (pITableUserItem != 0)
	{
		CGDialog("系统提示", 16, CGDLG_MB_OK, nullptr, nullptr);
		return false;
	}

	//变量定义
	bool bGameStart=pITable->GetPlayFlag();
	bool bDynamicJoin=CServerRule::IsAllowDynamicJoin(mServerAttribute.dwServerRule);

	//游戏状态
	if ((bGameStart==true)&&(bDynamicJoin==false)&&(bReqLookon==false))
	{
		CGDialog("系统提示", 17, CGDLG_MB_OK, nullptr, nullptr);
		return false;
	}

	//其他判断
	if ((bReqLookon==false)&&(mMeUserItem->GetMasterOrder()==0))
	{
		//规则判断
		for (word i=0;i<mTableFrame.GetChairCount();i++)
		{
			//获取用户
			IClientUserItem * pITableUserItem=pITable->GetClientUserItem(i);
			if ((pITableUserItem==0)||(pITableUserItem==mMeUserItem)) continue;

			//厌恶玩家
			if (pParameterGlobal->m_bLimitDetest==true)
			{
				if (pITableUserItem->GetUserCompanion()==CP_DETEST)
				{
					//设置提示
					//sprintf(strDescribe, "%s[ %s ]!", IDSTRING(18), pITableUserItem->GetNickName());
					return false;
				}
			}

			//胜率效验
			if (mParameterGame->m_bLimitWinRate==true)
			{
				if (((word)(pITableUserItem->GetUserWinRate()*1000L))<mParameterGame->m_wMinWinRate)
				{
					//sprintf(strDescribe, "[ %s ] %s", pITableUserItem->GetNickName(), IDSTRING(19));
					return false;
				}
			}

			//逃率效验
			if (mParameterGame->m_bLimitFleeRate)
			{
				if (((word)(pITableUserItem->GetUserFleeRate()*1000L))<mParameterGame->m_wMaxFleeRate)
				{
					//sprintf(strDescribe, "[ %s ] %s", pITableUserItem->GetNickName(), IDSTRING(20));
					return false;
				}
			}

			//积分效验
			if (mParameterGame->m_bLimitGameScore)
			{
				//最高积分
				if (pITableUserItem->GetUserScore()>mParameterGame->m_lMaxGameScore)
				{
					//sprintf(strDescribe, "[ %s ] %s", pITableUserItem->GetNickName(), IDSTRING(21));
					return false;
				}

				//最低积分
				if (pITableUserItem->GetUserScore()<mParameterGame->m_lMinGameScore)
				{
					//sprintf(strDescribe, "[ %s ] %s", pITableUserItem->GetNickName(), IDSTRING(22));
					return false;
				}
			}
		}
	}

	return true;
}
