#include "CServerItem.h"
#include "MELog.h"

//用户处理
bool CServerItem::OnSocketMainUser(int sub, void* data, int dataSize)
{
	MELOG(MELOG_INFO, "CServerItem::OnSocketMainUser sub = %d \n", sub);
	switch (sub)
	{
		//请求坐下失败
	case SUB_GR_REQUEST_FAILURE:	return OnSocketSubRequestFailure(data,dataSize);
		//邀请玩家
	case SUB_GR_USER_INVITE:		return OnSocketSubUserInvite(data,dataSize);
		//等待分配
	case SUB_GR_USER_WAIT_DISTRIBUTE: return OnSocketSubWaitDistribute(data,dataSize);
		//用户进入
	case SUB_GR_USER_ENTER:			return OnSocketSubUserEnter(data,dataSize);
		//用户积分
	case SUB_GR_USER_SCORE:			return OnSocketSubUserScore(data,dataSize);
		//用户状态
	case SUB_GR_USER_STATUS:		return OnSocketSubUserStatus(data,dataSize);
		//用户聊天
	case SUB_GR_USER_CHAT:			return OnSocketSubUserChat(data,dataSize);
		//用户表情
	case SUB_GR_USER_EXPRESSION:	return OnSocketSubExpression(data,dataSize);
		//用户私聊
	case SUB_GR_WISPER_CHAT:		return OnSocketSubWisperUserChat(data,dataSize);
		//私聊表情
	case SUB_GR_WISPER_EXPRESSION:	return OnSocketSubWisperExpression(data,dataSize);
		//道具成功
	case SUB_GR_PROPERTY_SUCCESS:	return OnSocketSubPropertySuccess(data,dataSize);
		//道具失败
	case SUB_GR_PROPERTY_FAILURE:	return OnSocketSubPropertyFailure(data,dataSize);
		//道具效应
	case SUB_GR_PROPERTY_EFFECT:	return OnSocketSubPropertyEffect(data,dataSize);
		//礼物消息
	case SUB_GR_PROPERTY_MESSAGE:   return OnSocketSubPropertyMessage(data,dataSize);
		//喇叭消息
	case SUB_GR_PROPERTY_TRUMPET:	return OnSocketSubPropertyTrumpet(data,dataSize);
		//低保信息
	//case SUB_GR_GUARANTEEING:	return OnGameGuaranteeing(data,dataSize);
		//更新积分   更新自定义房间信息 实际上是这个	在服务器哪里发送 
	case SUB_GR_USERS_SCORE: return OnUpdateCustTInfo(data, dataSize);		// 其中 当前局数是在变化中的，而且分数也是在变化中的。

		//更新房卡
	case SUB_GR_USER_ROOMCARD: 
	{
		if (dataSize == sizeof(int))
		{
			CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();
			pGlobalUserData->lRoomCard = *((int*)data);
			//
			MELOG(MELOG_INFO, "SUB_GR_USER_ROOMCARD finish:%d \n", pGlobalUserData->lRoomCard);
		}
		break;
	}
		//喜报消息
	case SUB_GR_GLAD_MESSAGE:		return OnSocketSubGladMessage(data,dataSize);
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
// 桌子状态
//请求失败
bool CServerItem::OnSocketSubRequestFailure(void* data, int dataSize)
{
	PACKET_AIDE_DATA(data);
	int lErrorCode = packet.read4Byte();
	std::string str = packet.readString((dataSize-4)/2);

	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubRequestFailure 请求坐下失败:%s"), str.c_str());

	////变量定义
	//IClientUserItem * pITableUserItem=0;
	//word wMeTableID=mMeUserItem->GetTableID();
	//word wMeChairID=mMeUserItem->GetChairID();
	
	//界面还原
	if ((mReqTableID!=INVALID_TABLE)&&(mReqChairID!=INVALID_TABLE)&&(mReqChairID!=MAX_CHAIR))
	{
		IClientUserItem * pITableUserItem=mTableFrame.GetClientUserItem(mReqTableID,mReqChairID);
		if (pITableUserItem == mMeUserItem)
			mTableFrame.SetClientUserItem(mReqTableID,mReqChairID,0);
	}

	//设置变量
	mReqTableID=INVALID_TABLE;
	mReqChairID=INVALID_CHAIR;
	if (mIsQuickSitDown)
	{
		mIsQuickSitDown = false;
		if (CServerRule::IsAllowQuickMode(mServerAttribute.dwServerRule))
		{//快速坐下,防作弊模式
			IntermitConnect(true, true);
			if (mIServerItemSink)
				mIServerItemSink->OnGFServerClose(str);
		}
	}
	else 
	{
		//提示消息
		if (mIServerItemSink)
			mIServerItemSink->onGRRequestFailure(str);
	}

	return true;
}

//等待分配
bool CServerItem::OnSocketSubWaitDistribute(void *data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubRequestFailure 等待分配"));

	//更新桌面
	mTableFrame.SetTableStatus(true);

	//游戏通知
	OnSocketMainGameFrame(MDM_GF_FRAME,SUB_GR_USER_WAIT_DISTRIBUTE,data,dataSize);
	return true;
}

//邀请玩家
bool CServerItem::OnSocketSubUserInvite(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubUserInvite 邀请玩家 "));

	PACKET_AIDE_DATA(data);
	word wTableID = packet.read2Byte();
	dword dwUserID = packet.read4Byte();

	ASSERT(wTableID<mTableFrame.GetTableCount());
	if (mTableFrame.GetPlayFlag(wTableID)==true) 
		return true;

	//寻找用户
	IClientUserItem * pIUserItem=mUserManager->SearchUserByUserID(dwUserID);
	if (pIUserItem==0) return true;
	if (pIUserItem->GetTableID()==INVALID_TABLE) return true;

	//变量定义
	ASSERT(CParameterGlobal::shared()!=0);
	CParameterGlobal * pParameterGlobal=CParameterGlobal::shared();

	//用户过虑
	if (pIUserItem->GetUserCompanion()==CP_DETEST) return true;
	if (pParameterGlobal->m_cbInviteMode==INVITE_MODE_NONE) return true;
	if ((pParameterGlobal->m_cbInviteMode==INVITE_MODE_FRIEND)&&(pIUserItem->GetUserCompanion()!=CP_FRIEND)) return true;

	//提示消息
	char szMessage[256]={0};
	sprintf(szMessage, "[ %s ] 邀请您加入第 [ %d ] 游戏桌进行游戏，是否同意? ",pIUserItem->GetNickName(),wTableID+1);
	
	CGDialog("系统消息", szMessage, CGDLG_MB_OK|CGDLG_MB_CANCEL,
		[&](){
			word wChairID=INVALID_CHAIR;
			word wNullCount=mTableFrame.GetNullChairCount(wTableID,wChairID);
			if (wNullCount==0) 
			{
				CGDialog("系统消息", 10, CGDLG_MB_OK, nullptr, nullptr);
				return;
			}
			PerformSitDownAction(wTableID,wChairID,false);
		},
		nullptr);
	return true;
}

//////////////////////////////////////////////////////////////////////////
//用户信息
//#define READ_PACKET(szOut)														\
//int len=wDataSize/2;															\
//u2string str;																	\
//str.resize(len+1,'\0');															\
//packet.readUTF16(&str[0], len);													\
//strncpy(szOut, u2_8(&str[0]), countarray(szOut))
#define READ_PACKET(szOut)									\
std::string str = packet.readString(wDataSize/2);			\
strncpy(szOut, str.c_str(), countarray(szOut))

//用户进入
bool CServerItem::OnSocketSubUserEnter(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubUserEnter 用户进入"));

	//变量定义
	tagUserInfo UserInfo;
	tagCustomFaceInfo CustomFaceInfo;
	zeromemory(&UserInfo,sizeof(UserInfo));
	zeromemory(&CustomFaceInfo,sizeof(CustomFaceInfo));
	
	//变量定义
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	
	PACKET_AIDE_DATA(data);

	//用户属性
	UserInfo.dwGameID = packet.read4Byte();
	UserInfo.dwUserID = packet.read4Byte();
	UserInfo.dwGroupID = packet.read4Byte();
	UserInfo.wFaceID = packet.read2Byte();
	UserInfo.dwCustomID = packet.read4Byte();

	//用户属性
	UserInfo.cbGender = packet.readByte();
	UserInfo.cbMemberOrder = packet.readByte();
	UserInfo.cbMasterOrder = packet.readByte();
	//packet.readByte();

	//用户状态
	UserInfo.wTableID = packet.read2Byte();
	UserInfo.wChairID = packet.read2Byte();
	UserInfo.cbUserStatus = packet.readByte();

	//用户积分
	UserInfo.lScore = packet.read8Byte();
	UserInfo.lGrade = packet.read8Byte();
	UserInfo.lInsure = packet.read8Byte();

	UserInfo.dwWinCount = packet.read4Byte();
	UserInfo.dwLostCount = packet.read4Byte();
	UserInfo.dwDrawCount = packet.read4Byte();
	UserInfo.dwFleeCount = packet.read4Byte();
	UserInfo.dwUserMedal = packet.read4Byte();
	UserInfo.dwExperience = packet.read4Byte();
	UserInfo.lLoveLiness = packet.read4Byte();

	packet.read4Byte();
	packet.read4Byte();
	packet.read4Byte();
	packet.read4Byte();

	UserInfo.cbUserType = packet.readByte();

	//扩展信息
	while (dataSize>packet.getPosition())
	{
		word wDataSize = packet.read2Byte();
		word wDataDescribe = packet.read2Byte();

		if (wDataDescribe == 0) break;
		switch (wDataDescribe)
		{
			case DTP_GR_NICK_NAME:		//用户昵称
			{
				//READ_PACKET(UserInfo.szNickName);
				std::string str = packet.readString(wDataSize / 2);
				if (str.length() <= 0 || str == "" || str[0] == '\0')
				{
					str = "ID ";
					char szBuf[32] = { 0 };
					sprintf(szBuf, "%4d", UserInfo.dwGameID);
					str += szBuf;
					str += "**";
				}
				strncpy(UserInfo.szNickName, str.c_str(), countarray(UserInfo.szNickName) > str.length() ? str.length() : countarray(UserInfo.szNickName) - 2);
				break;
			}
			case DTP_GR_GROUP_NAME:		//用户社团
			{
				READ_PACKET(UserInfo.szGroupName);
				break;
			}
			case DTP_GR_UNDER_WRITE:	//个性签名
			{
				READ_PACKET(UserInfo.szUnderWrite);
				break;
			}
			case DTP_GR_ICON_URL:
			{
				READ_PACKET(UserInfo.szIconUrl);
				break;
			}
		}

	}

	//自定头像
	if (UserInfo.dwCustomID!=0L)
	{
		////加载头像
		//CCustomFaceManager * pCustomFaceManager=CCustomFaceManager::GetInstance();
		//bool bSuccess=pCustomFaceManager->LoadUserCustomFace(pUserInfoHead->dwUserID,pUserInfoHead->dwCustomID,CustomFaceInfo);

		////下载头像
		//if (bSuccess==false)
		//{
		//	pCustomFaceManager->LoadUserCustomFace(pUserInfoHead->dwUserID,pUserInfoHead->dwCustomID);
		//}
	}

	//变量定义
	bool bHideUserInfo=CServerRule::IsAllowAvertCheatMode(mServerAttribute.dwServerRule);
	bool bMySelfUserItem=pGlobalUserData->dwUserID==UserInfo.dwUserID;
	bool bMasterUserOrder=((UserInfo.cbMasterOrder>0)||((mMeUserItem!=0)&&(mMeUserItem->GetMasterOrder()>0)));

	//隐藏信息
	if (!((bHideUserInfo==false)||(bMySelfUserItem==true)||(bMasterUserOrder==true)))
	{
		//用户信息
		strncpy(UserInfo.szNickName,"游戏玩家",countarray(UserInfo.szNickName));
		//..
	}

	//激活用户
	IClientUserItem * pIClientUserItem=mUserManager->SearchUserByUserID(UserInfo.dwUserID);
	if (pIClientUserItem==0) 
		pIClientUserItem=mUserManager->ActiveUserItem(UserInfo,CustomFaceInfo);

	//获取对象
	CServerListData * pServerListData=CServerListData::shared();

	//人数更新
	if (pServerListData)
		pServerListData->SetServerOnLineCount(mServerAttribute.wServerID,mUserManager->GetActiveUserCount());

	//变量定义
	ASSERT(CParameterGlobal::shared()!=0);
	CParameterGlobal * pParameterGlobal=CParameterGlobal::shared();

	//好友提示
	if (((bHideUserInfo==false)&&(bMySelfUserItem==false))||(bMasterUserOrder==true))
	{
		if(pParameterGlobal->m_bNotifyFriendCome && pIClientUserItem->GetUserCompanion()==CP_FRIEND)
		{
			char szMessage[256]={0};
			sprintf(szMessage, "您的好友 [%s] 进来了！", pIClientUserItem->GetNickName());
			//提示消息
			if (mIChatSink)
				mIChatSink->InsertSystemChat(szMessage);
		}
	}

	return true;
}

//用户积分
bool CServerItem::OnSocketSubUserScore(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubUserScore 用户积分"));

	tagUserScore UserScore;
	memset(&UserScore, 0, sizeof(tagUserScore));

	PACKET_AIDE_DATA(data);
	dword dwUserID = packet.read4Byte();

	UserScore.lScore = packet.read8Byte();
	UserScore.lGrade = packet.read8Byte();
	UserScore.lInsure = packet.read8Byte();
	UserScore.dwWinCount = packet.read4Byte();
	UserScore.dwLostCount = packet.read4Byte();
	UserScore.dwDrawCount = packet.read4Byte();
	UserScore.dwFleeCount = packet.read4Byte();
	UserScore.dwUserMedal = packet.read4Byte();
	UserScore.dwExperience = packet.read4Byte();
	UserScore.lLoveLiness = packet.read4Byte();


	//寻找用户
	IClientUserItem * pIClientUserItem=mUserManager->SearchUserByUserID(dwUserID);

	//用户判断
	ASSERT(pIClientUserItem!=0);
	if (pIClientUserItem==0) return true;

	//变量定义
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//变量定义
	bool bMySelfUserItem=pGlobalUserData->dwUserID==dwUserID;
	bool bAvertCheatMode=CServerRule::IsAllowAvertCheatMode(mServerAttribute.dwServerRule);
	bool bMasterUserOrder=((pIClientUserItem->GetMasterOrder()>0)||(mMeUserItem->GetMasterOrder()>0));

	//更新用户
	if ((bAvertCheatMode==false)||(bMySelfUserItem==true)||(bMasterUserOrder==true))
	{
		mUserManager->UpdateUserItemScore(pIClientUserItem,&UserScore);
	}

	return true;
}

//用户状态
bool CServerItem::OnSocketSubUserStatus(void* data, int dataSize)
{
	PACKET_AIDE_DATA(data);
	dword dwUserID = packet.read4Byte();
	tagUserStatus UserStatus;
	UserStatus.wTableID = packet.read2Byte();
	UserStatus.wChairID = packet.read2Byte();
	UserStatus.cbUserStatus = packet.readByte();
	MELOG(MELOG_INFO, "flow->CServerItem::OnSocketSubUserStatus  %d, %d, %d, %d\n", dwUserID, UserStatus.wTableID, UserStatus.wChairID, UserStatus.cbUserStatus);

	//寻找用户
	IClientUserItem * pIClientUserItem=mUserManager->SearchUserByUserID(dwUserID);

	//用户判断
	ASSERT(pIClientUserItem!=0);
	if (pIClientUserItem==0) return true;

	//设置状态
	if (UserStatus.cbUserStatus==US_NULL) 
	{
		//删除用户
		mUserManager->DeleteUserItem(pIClientUserItem);

		//获取对象
		CServerListData * pServerListData=CServerListData::shared();

		//人数更新
		pServerListData->SetServerOnLineCount(mServerAttribute.wServerID,mUserManager->GetActiveUserCount());
	}
	else
	{
		//更新用户
		mUserManager->UpdateUserItemStatus(pIClientUserItem, &UserStatus);
	}
	MELOG(MELOG_INFO, "flow->CServerItem::OnSocketSubUserStatus  finish ! \n");
	return true;
}

//////////////////////////////////////////////////////////////////////////
//聊天信息
//用户聊天
bool CServerItem::OnSocketSubUserChat(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubUserChat 用户聊天"));

	if (mIChatSink==0)
		return true;

	PACKET_AIDE_DATA(data);
	word wChatLength = packet.read2Byte();
	dword dwChatColor = packet.read4Byte();
	dword dwSendUserID = packet.read4Byte();
	dword dwTargetUserID = packet.read4Byte();
	std::string str = packet.readString(wChatLength);

	dwChatColor = ((dwChatColor & 0xFF) << 16) | (dwChatColor >> 8);

	//获取用户
	IClientUserItem * pISendUserItem=mUserManager->SearchUserByUserID(dwSendUserID);
	if (pISendUserItem==0) return true;

	//消息过虑
	if (pISendUserItem!=mMeUserItem)
	{
		//社团变量
		dword dwUserGroupID=pISendUserItem->GetGroupID();
		dword dwMySelfGroupID=mMeUserItem->GetGroupID();

		//社团判断
		bool bSameGroup=false;
		if ((dwMySelfGroupID!=0L)&&(dwMySelfGroupID==dwUserGroupID)) bSameGroup=true;

		//变量定义
		byte cbUserCompanion=pISendUserItem->GetUserCompanion();
		CParameterGlobal * pParameterGlobal=CParameterGlobal::shared();

		//好友模式
		if ((pParameterGlobal->m_cbMessageMode==MESSAGE_MODE_FRIEND)&&(cbUserCompanion!=CP_FRIEND)&&(bSameGroup==false))
		{
			return true;
		}

		//厌恶模式
		if ((pParameterGlobal->m_cbMessageMode==MESSAGE_MODE_DETEST)&&(cbUserCompanion==CP_DETEST)&&(bSameGroup==false))
		{
			return true;
		}
	}

	//显示消息
	if (dwTargetUserID!=0L)
	{
		//获取用户
		IClientUserItem * pIRecvUserItem=mUserManager->SearchUserByUserID(dwTargetUserID);
		if (pIRecvUserItem==0) return true;

		mIChatSink->InsertUserChat(
			pISendUserItem->GetNickName(),
			pIRecvUserItem->GetNickName(),str.c_str(),dwChatColor);
	}
	else 
	{
		//显示消息
		mIChatSink->InsertUserChat(pISendUserItem->GetNickName(), str.c_str(),dwChatColor);
	}

	return true;
}

//用户表情
bool CServerItem::OnSocketSubExpression(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubExpression 用户表情"));

	if (mIChatSink==0)
		return true;
	PACKET_AIDE_DATA(data);
	word wItemIndex = packet.read2Byte();
	dword dwSendUserID = packet.read4Byte();
	dword dwTargetUserID = packet.read4Byte();

	//获取用户
	IClientUserItem * pISendUserItem=mUserManager->SearchUserByUserID(dwSendUserID);
	if (pISendUserItem==0) return true;

	//消息过虑
	if (pISendUserItem!=mMeUserItem)
	{
		//社团变量
		dword dwUserGroupID=pISendUserItem->GetGroupID();
		dword dwMySelfGroupID=mMeUserItem->GetGroupID();

		//社团判断
		bool bSameGroup=false;
		if ((dwMySelfGroupID!=0L)&&(dwMySelfGroupID==dwUserGroupID)) bSameGroup=true;

		//变量定义
		byte cbUserCompanion=pISendUserItem->GetUserCompanion();
		CParameterGlobal * pParameterGlobal=CParameterGlobal::shared();

		//好友模式
		if ((pParameterGlobal->m_cbMessageMode==MESSAGE_MODE_FRIEND)&&(cbUserCompanion!=CP_FRIEND)&&(bSameGroup==false))
		{
			return true;
		}

		//厌恶模式
		if ((pParameterGlobal->m_cbMessageMode==MESSAGE_MODE_DETEST)&&(cbUserCompanion==CP_DETEST)&&(bSameGroup==false))
		{
			return true;
		}
	}

	//公聊消息
	if (dwTargetUserID==0L)
	{
		mIChatSink->InsertExpression(pISendUserItem->GetNickName(), wItemIndex);
		return true;
	}

	//私聊消息
	if (dwTargetUserID!=0L)
	{
		//获取用户
		IClientUserItem * pIRecvUserItem=mUserManager->SearchUserByUserID(dwTargetUserID);
		if (pIRecvUserItem==0) return true;

		//显示消息
		mIChatSink->InsertExpression(pISendUserItem->GetNickName(),pIRecvUserItem->GetNickName(),wItemIndex);
	}

	return true;
}

//用户私聊
bool CServerItem::OnSocketSubWisperUserChat(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubWisperUserChat 用户私聊"));

	if (mIChatSink==0)
		return true;

	PACKET_AIDE_DATA(data);
	word wChatLength = packet.read2Byte();
	dword dwChatColor = packet.read4Byte();
	dword dwSendUserID = packet.read4Byte();
	dword dwTargetUserID = packet.read4Byte();
	std::string str = packet.readString(wChatLength);

	dwChatColor = ((dwChatColor & 0xFF) << 16) | (dwChatColor >> 8);

	//获取用户
	IClientUserItem * pISendUserItem=mUserManager->SearchUserByUserID(dwSendUserID);
	if (pISendUserItem==0) return true;

	//接收用户
	IClientUserItem * pIRecvUserItem=mUserManager->SearchUserByUserID(dwTargetUserID);
	if (pIRecvUserItem==0) return true;

	//消息过虑
	if (pISendUserItem!=mMeUserItem)
	{
		//社团变量
		dword dwUserGroupID=pISendUserItem->GetGroupID();
		dword dwMySelfGroupID=mMeUserItem->GetGroupID();

		//社团判断
		bool bSameGroup=false;
		if ((dwMySelfGroupID!=0L)&&(dwMySelfGroupID==dwUserGroupID)) bSameGroup=true;

		//变量定义
		byte cbUserCompanion=pISendUserItem->GetUserCompanion();
		CParameterGlobal * pParameterGlobal=CParameterGlobal::shared();

		//好友模式
		if ((pParameterGlobal->m_cbMessageMode==MESSAGE_MODE_FRIEND)&&(cbUserCompanion!=CP_FRIEND)&&(bSameGroup==false))
		{
			return true;
		}

		//厌恶模式
		if ((pParameterGlobal->m_cbMessageMode==MESSAGE_MODE_DETEST)&&(cbUserCompanion==CP_DETEST)&&(bSameGroup==false))
		{
			return true;
		}

		//屏蔽用户
		if(cbUserCompanion == CP_SHIELD) return true;
	}

	mIChatSink->InsertWhisperChat(pISendUserItem->GetNickName(), str.c_str(), dwChatColor, pISendUserItem == mMeUserItem);
	return true;
}

//私聊表情
bool CServerItem::OnSocketSubWisperExpression(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubWisperExpression 私聊表情"));

	if (mIChatSink==0)
		return true;
	PACKET_AIDE_DATA(data);
	word wItemIndex = packet.read2Byte();
	dword dwSendUserID = packet.read4Byte();
	dword dwTargetUserID = packet.read4Byte();

	//获取用户
	IClientUserItem * pISendUserItem=mUserManager->SearchUserByUserID(dwSendUserID);
	if (pISendUserItem==0) return true;

	//接收用户
	IClientUserItem * pIRecvUserItem=mUserManager->SearchUserByUserID(dwTargetUserID);
	if (pIRecvUserItem==0) return true;

	//消息过虑
	if (pISendUserItem!=mMeUserItem)
	{
		//社团变量
		dword dwUserGroupID=pISendUserItem->GetGroupID();
		dword dwMySelfGroupID=mMeUserItem->GetGroupID();

		//社团判断
		bool bSameGroup=false;
		if ((dwMySelfGroupID!=0L)&&(dwMySelfGroupID==dwUserGroupID)) bSameGroup=true;

		//变量定义
		byte cbUserCompanion=pISendUserItem->GetUserCompanion();
		CParameterGlobal * pParameterGlobal=CParameterGlobal::shared();

		//好友模式
		if ((pParameterGlobal->m_cbMessageMode==MESSAGE_MODE_FRIEND)&&(cbUserCompanion!=CP_FRIEND)&&(bSameGroup==false))
		{
			return true;
		}

		//厌恶模式
		if ((pParameterGlobal->m_cbMessageMode==MESSAGE_MODE_DETEST)&&(cbUserCompanion==CP_DETEST)&&(bSameGroup==false))
		{
			return true;
		}

		//屏蔽用户
		if(cbUserCompanion == CP_SHIELD) return true;
	}

	mIChatSink->InsertExpression(pISendUserItem->GetNickName(), pIRecvUserItem->GetNickName(), wItemIndex);

	return true;
}

//////////////////////////////////////////////////////////////////////////
//道具信息
//道具成功
bool CServerItem::OnSocketSubPropertySuccess(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubPropertySuccess 道具成功"));

	PACKET_AIDE_DATA(data);
	byte cbRequestArea = packet.readByte();
	word wItemCount = packet.read2Byte();
	word wPropertyIndex = packet.read2Byte();
	dword dwSourceUserID = packet.read4Byte();
	dword dwTargetUserID = packet.read4Byte();

	//获取用户
	IClientUserItem * pISendUserItem=mUserManager->SearchUserByUserID(dwSourceUserID);
	if (pISendUserItem==0) return true;

	//获取用户
	IClientUserItem * pTargetUserItem=mUserManager->SearchUserByUserID(dwTargetUserID);
	if (pTargetUserItem==0) return true;

	//使用范围
	if(cbRequestArea==PT_ISSUE_AREA_GAME)
	{
		PLAZZ_PRINTF(("恭喜您,游戏道具购买成功!\n"));
		//if (mIPropertySink)
		//	mIPropertySink->onPropertyBuySuccess(
		//		pPropertySuccess->wPropertyIndex,
		//		pPropertySuccess->wItemCount, 
		//		pPropertySuccess->dwSourceUserID,
		//		pPropertySuccess->dwTargetUserID);
		return true;
	}

	PLAZZ_PRINTF(("恭喜您,房间道具购买成功!\n"));

	////获取对象
	//ASSERT(CGamePropertyManager::GetInstance()!=0);
	//CGamePropertyManager * pGamePropertyManager=CGamePropertyManager::GetInstance();

	////寻找道具
	//ASSERT(pGamePropertyManager->GetPropertyItem(pPropertySuccess->wPropertyIndex)!=0);
	//CGamePropertyItem * pGamePropertyItem=pGamePropertyManager->GetPropertyItem(pPropertySuccess->wPropertyIndex);

	////道具处理
	//if (pGamePropertyItem!=0 && pGamePropertyItem->GetPropertyAttrib()->wPropertyType==PT_TYPE_PRESENT)
	//{
	//	//图片信息
	//	tagPropertyImage PropertyImage;
	//	pGamePropertyItem->GetImageInfo(PropertyImage);

	//	//播放动画
	//	if ((PropertyImage.pszFlash!=0)&&(PropertyImage.pszFlash[0]!=0))
	//	{
	//		//工作路径
	//		char szDirectory[MAX_PATH]=T_T("");
	//		CWHService::GetWorkDirectory(szDirectory,CountArray(szDirectory));

	//		//构造路径
	//		char szFlashPath[MAX_PATH]=T_T("");
	//		_sntprintf(szFlashPath,CountArray(szFlashPath),T_T("%s\\Property\\%s"),szDirectory,PropertyImage.pszFlash);

	//		try
	//		{
	//			//播放动画
	//			if (m_FlashControl.LoadMovieFile(szFlashPath)==false)
	//			{
	//				throw T_T("动画文件加载失败");
	//			}

	//			//动画控件
	//			CRect rcWindow;
	//			m_TableFrame.GetWindowRect(&rcWindow);
	//			m_FlashControl.SetPosition(rcWindow.left+(rcWindow.Width()-FALSH_MOVIE_CX)/2,rcWindow.top+(rcWindow.Height()-FALSH_MOVIE_CY)*2/5,FALSH_MOVIE_CX,FALSH_MOVIE_CY,SWP_NOSIZE);

	//			//播放动画
	//			m_FlashControl.PlayMovie();
	//			m_FlashControl.ShowControl(SW_SHOW);
	//		}
	//		catch (...)
	//		{
	//			ASSERT(FALSE);
	//		}
	//	}
	//}

	////道具提示
	//if(pGamePropertyItem->GetPropertyAttrib()->wPropertyType==PT_TYPE_PROPERTY)
	//{
	//	//变量定义
	//	char  szMessage[256]=T_T("");

	//	//获取提示
	//	if(pPropertySuccess->dwSourceUserID==mMeUserItem->GetUserID() && pPropertySuccess->dwSourceUserID!=pPropertySuccess->dwTargetUserID)
	//		_sntprintf(szMessage,CountArray(szMessage),T_T("恭喜您,道具购买成功!"));
	//	else
	//		pGamePropertyItem->GetNotifyMessage(pISendUserItem->GetNickName(),mMeUserItem->GetNickName(),pPropertySuccess->wItemCount,szMessage);

	//	//弹出消息
	//	CInformation Information;
	//	Information.ShowMessageBox(szMessage,MB_ICONINFORMATION);

	//	//更新喇叭
	//	if(m_pTrumpetItem!=0)  m_pTrumpetItem->UpdateControlSurface();
	//}

	return true;

	////效验参数
	//ASSERT(dataSize==sizeof(CMD_GR_S_PropertySuccess));
	//if (dataSize!=sizeof(CMD_GR_S_PropertySuccess)) return false;

	////变量定义
	//CMD_GR_S_PropertySuccess * pPropertySuccess=(CMD_GR_S_PropertySuccess *)data;

	////获取用户
	//IClientUserItem * pISendUserItem=mUserManager->SearchUserByUserID(pPropertySuccess->dwSourceUserID);
	//if (pISendUserItem==0) return true;

	////获取用户
	//IClientUserItem * pTargetUserItem=mUserManager->SearchUserByUserID(pPropertySuccess->dwTargetUserID);
	//if (pTargetUserItem==0) return true;

	////使用范围
	//if(pPropertySuccess->cbRequestArea==PT_ISSUE_AREA_GAME)
	//{
	//	_tprintf(T_T("恭喜您,游戏道具购买成功!\n"));
	//	//if (mIPropertySink)
	//	//	mIPropertySink->onPropertyBuySuccess(
	//	//		pPropertySuccess->wPropertyIndex,
	//	//		pPropertySuccess->wItemCount, 
	//	//		pPropertySuccess->dwSourceUserID,
	//	//		pPropertySuccess->dwTargetUserID);
	//	return true;
	//}

	//_tprintf(T_T("恭喜您,房间道具购买成功!\n"));

	//////获取对象
	////ASSERT(CGamePropertyManager::GetInstance()!=0);
	////CGamePropertyManager * pGamePropertyManager=CGamePropertyManager::GetInstance();

	//////寻找道具
	////ASSERT(pGamePropertyManager->GetPropertyItem(pPropertySuccess->wPropertyIndex)!=0);
	////CGamePropertyItem * pGamePropertyItem=pGamePropertyManager->GetPropertyItem(pPropertySuccess->wPropertyIndex);

	//////道具处理
	////if (pGamePropertyItem!=0 && pGamePropertyItem->GetPropertyAttrib()->wPropertyType==PT_TYPE_PRESENT)
	////{
	////	//图片信息
	////	tagPropertyImage PropertyImage;
	////	pGamePropertyItem->GetImageInfo(PropertyImage);

	////	//播放动画
	////	if ((PropertyImage.pszFlash!=0)&&(PropertyImage.pszFlash[0]!=0))
	////	{
	////		//工作路径
	////		char szDirectory[MAX_PATH]=T_T("");
	////		CWHService::GetWorkDirectory(szDirectory,CountArray(szDirectory));

	////		//构造路径
	////		char szFlashPath[MAX_PATH]=T_T("");
	////		_sntprintf(szFlashPath,CountArray(szFlashPath),T_T("%s\\Property\\%s"),szDirectory,PropertyImage.pszFlash);

	////		try
	////		{
	////			//播放动画
	////			if (m_FlashControl.LoadMovieFile(szFlashPath)==false)
	////			{
	////				throw T_T("动画文件加载失败");
	////			}

	////			//动画控件
	////			CRect rcWindow;
	////			m_TableFrame.GetWindowRect(&rcWindow);
	////			m_FlashControl.SetPosition(rcWindow.left+(rcWindow.Width()-FALSH_MOVIE_CX)/2,rcWindow.top+(rcWindow.Height()-FALSH_MOVIE_CY)*2/5,FALSH_MOVIE_CX,FALSH_MOVIE_CY,SWP_NOSIZE);

	////			//播放动画
	////			m_FlashControl.PlayMovie();
	////			m_FlashControl.ShowControl(SW_SHOW);
	////		}
	////		catch (...)
	////		{
	////			ASSERT(FALSE);
	////		}
	////	}
	////}

	//////道具提示
	////if(pGamePropertyItem->GetPropertyAttrib()->wPropertyType==PT_TYPE_PROPERTY)
	////{
	////	//变量定义
	////	char  szMessage[256]=T_T("");

	////	//获取提示
	////	if(pPropertySuccess->dwSourceUserID==mMeUserItem->GetUserID() && pPropertySuccess->dwSourceUserID!=pPropertySuccess->dwTargetUserID)
	////		_sntprintf(szMessage,CountArray(szMessage),T_T("恭喜您,道具购买成功!"));
	////	else
	////		pGamePropertyItem->GetNotifyMessage(pISendUserItem->GetNickName(),mMeUserItem->GetNickName(),pPropertySuccess->wItemCount,szMessage);

	////	//弹出消息
	////	CInformation Information;
	////	Information.ShowMessageBox(szMessage,MB_ICONINFORMATION);

	////	//更新喇叭
	////	if(m_pTrumpetItem!=0)  m_pTrumpetItem->UpdateControlSurface();
	////}

	//return true;
}

//道具失败
bool CServerItem::OnSocketSubPropertyFailure(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubPropertyFailure 道具失败"));

	//变量定义
	PACKET_AIDE_DATA(data);
	word wRequestArea = packet.read2Byte();
	int lErrorCode = packet.read4Byte();
	std::string str = packet.readString((dataSize-packet.getPosition())/2);
	
	//使用范围
	if(wRequestArea==PT_ISSUE_AREA_GAME)
	{
		PLAZZ_PRINTF(("游戏道具购买失败! [%d] %s \n"), lErrorCode, str.c_str());
		//if (mIPropertySink)
		//	mIPropertySink->onPropertyBuyFailure(
		//		pPropertyFailure->lErrorCode,
		//		pPropertyFailure->szDescribeString);
		return true;
	}

	PLAZZ_PRINTF(("房间道具购买失败! [%d] %s \n"), lErrorCode, str.c_str());

	return true;
	////变量定义
	//CMD_GR_PropertyFailure * pPropertyFailure=(CMD_GR_PropertyFailure *)data;
	//if(pPropertyFailure==0) return false;

	////使用范围
	//if(pPropertyFailure->wRequestArea==PT_ISSUE_AREA_GAME)
	//{
	//	_tprintf(T_T("游戏道具购买失败! [%d] %s \n"), pPropertyFailure->lErrorCode, pPropertyFailure->szDescribeString);
	//	//if (mIPropertySink)
	//	//	mIPropertySink->onPropertyBuyFailure(
	//	//		pPropertyFailure->lErrorCode,
	//	//		pPropertyFailure->szDescribeString);
	//	return true;
	//}

	//_tprintf(T_T("房间道具购买失败! [%d] %s \n"),
	//	pPropertyFailure->lErrorCode, 
	//	pPropertyFailure->szDescribeString);

	//return true;
}

//道具效应
bool CServerItem::OnSocketSubPropertyEffect(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubPropertyEffect 道具效应"));

	PACKET_AIDE_DATA(data);
	dword dwUserID = packet.read4Byte();
	byte cbMemberOrder = packet.readByte();

	//查找用户
	IClientUserItem * pISendUserItem=mUserManager->SearchUserByUserID(dwUserID);
	if(pISendUserItem==0) return true;

	//设置变量
	tagUserInfo * pUserInfo = pISendUserItem->GetUserInfo();
	pUserInfo->cbMemberOrder=cbMemberOrder;

	////更新信息
	//m_UserListControl.UpdateDataItem(pISendUserItem);

	return true;
	////参数校验
	//ASSERT(dataSize==sizeof(CMD_GR_S_PropertyEffect));
	//if(dataSize!=sizeof(CMD_GR_S_PropertyEffect))  return false;

	////变量定义
	//CMD_GR_S_PropertyEffect * pPropertyEffect=(CMD_GR_S_PropertyEffect *)data;
	//if(pPropertyEffect==0) return false;

	////查找用户
	//IClientUserItem * pISendUserItem=mUserManager->SearchUserByUserID(pPropertyEffect->wUserID);
	//if(pISendUserItem==0) return true;

	////设置变量
	//tagUserInfo * pUserInfo = pISendUserItem->GetUserInfo();
	//pUserInfo->cbMemberOrder=pPropertyEffect->cbMemberOrder;

	//////更新信息
	////m_UserListControl.UpdateDataItem(pISendUserItem);

	//return true;
}

//道具消息
bool CServerItem::OnSocketSubPropertyMessage(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubPropertyMessage 道具消息"));

	////效验参数
	//ASSERT(dataSize==sizeof(CMD_GR_S_PropertyMessage));
	//if (dataSize!=sizeof(CMD_GR_S_PropertyMessage)) return false;

	////校验数据
	//CMD_GR_S_PropertyMessage * pPropertyMessage = (CMD_GR_S_PropertyMessage *)data;
	//if(pPropertyMessage==0) return false;

	////获取对象
	//ASSERT(CGamePropertyManager::GetInstance()!=0);
	//CGamePropertyManager * pGamePropertyManager=CGamePropertyManager::GetInstance();

	////寻找道具
	//ASSERT(pGamePropertyManager->GetPropertyItem(pPropertyMessage->wPropertyIndex)!=0);
	//CGamePropertyItem * pGamePropertyItem=pGamePropertyManager->GetPropertyItem(pPropertyMessage->wPropertyIndex);
	//if(pGamePropertyItem==0) return true;

	////类型判断
	//if(pGamePropertyItem->GetPropertyAttrib()->wPropertyType==PT_TYPE_PROPERTY) return true;

	////获取用户
	//IClientUserItem * pISendUserItem=mUserManager->SearchUserItemByUserID(pPropertyMessage->dwSourceUserID);
	//if (pISendUserItem==0) return true;

	////获取用户
	//IClientUserItem * pIRecvUserItem=mUserManager->SearchUserItemByUserID(pPropertyMessage->dwTargerUserID);
	//if (pIRecvUserItem==0) return true;

	////提取信息
	//char szNotifyMessage[128]=T_T("");	
	//pGamePropertyItem->GetNotifyMessage(pISendUserItem->GetNickName(),pIRecvUserItem->GetNickName(),pPropertyMessage->wPropertyCount,szNotifyMessage);

	////插入消息
	//m_ChatMessage.InsertPromptString(szNotifyMessage);

	//if(IsGameClientReady())
	//{
	//	//构造结构
	//	IPC_GR_PropertyMessage  PropertyMessage;
	//	PropertyMessage.wPropertyIndex=pPropertyMessage->wPropertyIndex;
	//	PropertyMessage.wPropertyCount=pPropertyMessage->wPropertyCount;
	//	memcpy(PropertyMessage.szSourceNickName,pISendUserItem->GetNickName(),sizeof(PropertyMessage.szSourceNickName));
	//	memcpy(PropertyMessage.szTargerNickName,pIRecvUserItem->GetNickName(),sizeof(PropertyMessage.szTargerNickName));

	//	//发送数据
	//	m_ProcessManager.SendProcessData(IPC_CMD_GF_PROPERTY_INFO,IPC_SUB_GR_PROPERTY_MESSAGE,&PropertyMessage,sizeof(PropertyMessage));
	//}

	return true;
}

//道具喇叭
bool CServerItem::OnSocketSubPropertyTrumpet(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubPropertyTrumpet 道具喇叭"));

	PACKET_AIDE_DATA(data);
	word wPropertyIndex = packet.read2Byte();
	dword dwSendUserID = packet.read4Byte();
	dword TrumpetColor = packet.read4Byte();
	std::string szSendNickName = packet.readString(32);
	std::string szTrumpetContent = packet.readString(TRUMPET_MAX_CHAR);

	if (mIChatSink)
	{
		//if (wPropertyIndex == PROPERTY_ID_TRUMPET)
			mIChatSink->InsertUserTrumpet(szSendNickName.c_str(), szTrumpetContent.c_str(), TrumpetColor);

		//if (wPropertyIndex == PROPERTY_ID_TYPHON)
		//	mIChatSink->InsertUserTyphon(szSendNickName.c_str(), szTrumpetContent.c_str(), TrumpetColor);
	}
	
	////更新包裹
	//if(pSendTrumpet->dwSendUserID==mMeUserItem->GetUserID())
	//{
	//	//道具包裹
	//	tagPropertyPackage * pPropertyPackage=mMeUserItem->GetPropertyPackage();

	//	//更新包裹
	//	if(pSendTrumpet->wPropertyIndex==PROPERTY_ID_TRUMPET) --pPropertyPackage->wTrumpetCount;
	//	if(pSendTrumpet->wPropertyIndex==PROPERTY_ID_TYPHON) --pPropertyPackage->wTyphonCount;
	//	if(m_pTrumpetItem!=0) m_pTrumpetItem->UpdateControlSurface();
	//}

	//if(IsGameClientReady())
	//{
	//	//构造结构
	//	IPC_GR_PropertyTrumpet  PropertyTrumpet;
	//	PropertyTrumpet.dwSendUserID=pSendTrumpet->dwSendUserID;
	//	PropertyTrumpet.wPropertyIndex=pSendTrumpet->wPropertyIndex;
	//	PropertyTrumpet.TrumpetColor=pSendTrumpet->TrumpetColor;
	//	memcpy(PropertyTrumpet.szSendNickName,pSendTrumpet->szSendNickName,sizeof(PropertyTrumpet.szSendNickName));
	//	memcpy(PropertyTrumpet.szTrumpetContent,pSendTrumpet->szTrumpetContent,sizeof(PropertyTrumpet.szTrumpetContent));

	//	//发送数据
	//	m_ProcessManager.SendProcessData(IPC_CMD_GF_PROPERTY_INFO,IPC_SUB_GR_PROPERTY_TRUMPET,&PropertyTrumpet,sizeof(PropertyTrumpet));
	//}

	////变量定义
	//ASSERT(CParameterGlobal::shared()!=0);
	//CParameterGlobal * pParameterGlobal=CParameterGlobal::shared();

	////播放声音
	//if(pParameterGlobal->m_bAllowSound)
	//{
	//	//变量定义
	//	HINSTANCE hInstance = AfxGetInstanceHandle();
	//	bool bPlaying=false;

	//	////获取对象
	//	//CD3DSound * pD3DSound=CD3DSound::GetInstance();
	//	//if(pD3DSound)
	//	//{
	//	//	bPlaying = pD3DSound->PlaySound(hInstance, (pSendTrumpet->wPropertyIndex==PROPERTY_ID_TRUMPET)?T_T("BUGLE"):T_T("BUGLE_EX"), T_T("WAVE"), false);
	//	//}

	//	//系统播放
	//	if(!bPlaying)
	//	{
	//		HRSRC hResour=FindResource(hInstance,(pSendTrumpet->wPropertyIndex==PROPERTY_ID_TRUMPET)?T_T("BUGLE"):T_T("BUGLE_EX"),T_T("WAVE"));
	//		if (hResour!=0)
	//		{
	//			HGLOBAL hGlobal=LoadResource(hInstance,hResour);
	//			if (hGlobal!=0) 
	//			{
	//				//播放声音
	//				const char* pszMemory=(const char*)LockResource(hGlobal);
	//				BOOL bResult = ::PlaySound(pszMemory,hInstance,SND_ASYNC|SND_MEMORY|SND_NODEFAULT);

	//				//清理资源
	//				UnlockResource(hGlobal);
	//			}
	//			FreeResource(hGlobal);
	//		}
	//	}
	//}

	return true;
}

//喜报消息
bool CServerItem::OnSocketSubGladMessage(void* data, int dataSize)
{
	PACKET_AIDE_DATA(data);

	std::string sContent	= packet.readString(128);
	std::string sNickName	= packet.readString(32);
	std::string sNum		= packet.readString(16);

	dword colText = COL_N2G(packet.read4Byte());
	dword colName = COL_N2G(packet.read4Byte());
	dword colNum  = COL_N2G(packet.read4Byte());

	PLAZZ_PRINTF("=====================================\n");
	PLAZZ_PRINTF("NickName: %s", sNickName.c_str());
	PLAZZ_PRINTF("Content: %s", sContent.c_str());
	PLAZZ_PRINTF("Num: %s", sNum.c_str());

	if (mIStringMessageSink)
		mIStringMessageSink->InsertGladString(sContent.c_str(), sNickName.c_str(), sNum.c_str(), colText, colName, colNum);
	return true;
}

//低保信息
bool CServerItem::OnGameGuaranteeing(void *pData, int wDataSize)
{
	////变量定义
	//CMD_GR_GameGuaranteeing * pSystemMessage = (CMD_GR_GameGuaranteeing *)pData;
	//if (wDataSize != sizeof(CMD_GR_GameGuaranteeing)) return false;

	////
	//if (pSystemMessage)
	//{
	//	CGuaranteeingWin DlgGuaranteeingWin;
	//	CString		strCaption;						//信息标题
	//	CString		strString;						//信息标题
	//	CString		strString1;						//信息标题
	//	strCaption.Format(TEXT("恭喜您！获得 %I64d 两救济金！"), pSystemMessage->lScore);
	//	strString.Format(TEXT("%s"), pSystemMessage->szGuaranteeingInfo);
	//	strString1.Format(TEXT("每天可以领取 %d 次救助金，还剩 %d 次！"), pSystemMessage->cbTotalNumber, pSystemMessage->cbSurplusNumber);

	//	DlgGuaranteeingWin.ShowMessageBox(strCaption, strString, strString1);
	//}
	////
	return true;
}

//更新自定义房间信息
bool CServerItem::OnUpdateCustTInfo(void *pData, int wDataSize)
{
	tagCustomTableInfo customTableInfo;
	memset(&customTableInfo, 0, sizeof(tagCustomTableInfo));

	tagCustomTableInfo* lpRecvTableInfo = (tagCustomTableInfo*)pData;

	customTableInfo.cbExData = lpRecvTableInfo->cbExData;
	customTableInfo.cbCurRound = lpRecvTableInfo->cbCurRound;
	customTableInfo.cbMaxRound = lpRecvTableInfo->cbMaxRound;
	customTableInfo.wTableID = lpRecvTableInfo->wTableID;
	customTableInfo.wChairCount = lpRecvTableInfo->wChairCount;
	customTableInfo.dwCreateFlag = lpRecvTableInfo->dwCreateFlag;
	customTableInfo.dwCreateUser = lpRecvTableInfo->dwCreateUser;
	customTableInfo.wChairCount = lpRecvTableInfo->wChairCount;

	for (byte i = 0; i < customTableInfo.wChairCount; ++i)
	{
		customTableInfo.lChairScore[i] = lpRecvTableInfo->lChairScore[i];
	}

	//变量定义
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();

	//寻找用户
	IClientUserItem * pIClientUserItem = mUserManager->SearchUserByUserID(pGlobalUserData->dwUserID);

	//用户判断
	ASSERT(pIClientUserItem != 0);
	if (pIClientUserItem == 0) return true;
	mUserManager->UpdateUserCustomTableInfo(pIClientUserItem, customTableInfo);

	return true;
}
