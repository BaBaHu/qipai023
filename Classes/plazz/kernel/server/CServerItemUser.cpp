#include "CServerItem.h"
#include "MELog.h"
//////////////////////////////////////////////////////////////////////////
//用户接口

//自己位置
word CServerItem::GetMeChairID()
{
	if (mMeUserItem == 0) return INVALID_CHAIR;
	return mMeUserItem->GetChairID();
}

//自己位置
IClientUserItem * CServerItem::GetMeUserItem()
{
	return mMeUserItem;
}

//游戏用户
IClientUserItem * CServerItem::GetTableUserItem(word wChairID)
{
	return mUserManager->EnumUserItem(wChairID);
}

//查找用户
IClientUserItem * CServerItem::SearchUserByUserID(dword dwUserID)
{
	return mUserManager->SearchUserByUserID(dwUserID);
}

//查找用户
IClientUserItem * CServerItem::SearchUserByGameID(dword dwGameID)
{
	return mUserManager->SearchUserByGameID(dwGameID);
}

//查找用户
IClientUserItem * CServerItem::SearchUserByNickName(const char* szNickName)
{
	return mUserManager->SearchUserByNickName(szNickName);
}

//获取桌子信息
ITableFrame * CServerItem::GetTableFrame()
{
	return &mTableFrame;
}

//设置手机用户
void CServerItem::SetMobileUser(bool bMobile)
{
	m_MobileUser = bMobile;
}

//获取手机用户
bool CServerItem::GetMobileUser()
{
	return m_MobileUser;
}

//////////////////////////////////////////////////////////////////////////
// IUserManagerSink
//////////////////////////////////////////////////////////////////////////
void CServerItem::OnUserItemAcitve(IClientUserItem* pIClientUserItem)
{
	MELOG(MELOG_INFO, "flow->CServerItem::OnUserItemAcitve :%s \n", pIClientUserItem->GetNickName());
	//判断自己
	if (mMeUserItem==0)
	{
		mMeUserItem=pIClientUserItem;
	}
	
	//设置桌子
	byte cbUserStatus=pIClientUserItem->GetUserStatus();
	if ((cbUserStatus>=US_SIT)&&(cbUserStatus!=US_LOOKON))
	{
		word wTableID=pIClientUserItem->GetTableID();
		word wChairID=pIClientUserItem->GetChairID();
		mTableFrame.SetClientUserItem(wTableID,wChairID,pIClientUserItem);
	}

	//提示信息
	CParameterGlobal * pParameterGlobal=CParameterGlobal::shared();
	if ((pParameterGlobal->m_bNotifyUserInOut==true)&&(mServiceStatus==ServiceStatus_ServiceIng))
	{
		if (mIStringMessageSink)
			mIStringMessageSink->InsertUserEnter(pIClientUserItem->GetNickName());
	}

	if (mIServerItemSink)
		mIServerItemSink->OnGRUserEnter(pIClientUserItem);
	MELOG(MELOG_INFO, "flow->CServerItem::OnUserItemAcitve finish:%s \n", pIClientUserItem->GetNickName());
}

void CServerItem::OnUserItemDelete(IClientUserItem* pIClientUserItem)
{
	MELOG(MELOG_INFO, "flow->CServerItem::OnUserItemDelete :%s \n", pIClientUserItem->GetNickName());
	//变量定义
	word wLastTableID=pIClientUserItem->GetTableID();
	word wLastChairID=pIClientUserItem->GetChairID();
	dword dwLeaveUserID=pIClientUserItem->GetUserID();
	tagUserInfo * pMeUserInfo=mMeUserItem->GetUserInfo();

	//变量定义
	ASSERT(CParameterGlobal::shared());
	CParameterGlobal * pParameterGlobal=CParameterGlobal::shared();

	//离开处理
	if ((wLastTableID!=INVALID_TABLE)&&(wLastChairID!=INVALID_CHAIR))
	{
		//获取用户
		IClientUserItem * pITableUserItem=mTableFrame.GetClientUserItem(wLastTableID,wLastChairID);
		if (pITableUserItem==pIClientUserItem) mTableFrame.SetClientUserItem(wLastTableID,wLastChairID,0);

		//离开通知
		if ((pIClientUserItem==mMeUserItem)||(wLastTableID==pMeUserInfo->wTableID))
		{
			tagUserStatus UserStatus;
			UserStatus.cbUserStatus=US_NULL;
			UserStatus.wTableID=INVALID_TABLE;
			UserStatus.wChairID=INVALID_CHAIR;

			if (IClientKernel::get())
				IClientKernel::get()->OnGFUserStatus(pIClientUserItem->GetUserID(), UserStatus);
		}
	}

	if (mIServerItemSink)
		mIServerItemSink->OnGRUserDelete(pIClientUserItem);

	//提示信息
	if ((pParameterGlobal->m_bNotifyUserInOut==true)&&(mServiceStatus==ServiceStatus_ServiceIng))
	{
		if (mIStringMessageSink)
			mIStringMessageSink->InsertUserLeave(pIClientUserItem->GetNickName());
	}
	MELOG(MELOG_INFO, "flow->CServerItem::OnUserItemDelete finish:%s \n", pIClientUserItem->GetNickName());
}

void CServerItem::OnUserFaceUpdate(IClientUserItem * pIClientUserItem)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnUserFaceUpdate 用户头像更新:%s"), pIClientUserItem->GetNickName());
	//变量定义
	tagUserInfo * pUserInfo=pIClientUserItem->GetUserInfo();
	tagCustomFaceInfo * pCustomFaceInfo=pIClientUserItem->GetCustomFaceInfo();

	if (mIServerItemSink)
		mIServerItemSink->OnGRUserUpdate(pIClientUserItem);

	//更新桌子
	if ((pUserInfo->wTableID!=INVALID_TABLE)&&(pUserInfo->cbUserStatus!=US_LOOKON))
	{
		mTableFrame.UpdateTable(pUserInfo->wTableID);
	}

	//更新游戏
	if ((pUserInfo->wTableID!=INVALID_TABLE)&&(mMeUserItem->GetTableID()==pUserInfo->wTableID))
	{
		if (IClientKernel::get())
			IClientKernel::get()->OnGFUserCustomFace(pUserInfo->dwUserID,pUserInfo->dwCustomID,*pCustomFaceInfo);
	}
}

void CServerItem::OnUserItemUpdate(IClientUserItem* pIClientUserItem, const tagUserScore& LastScore)
{
	MELOG(MELOG_INFO, "flow->CServerItem::OnUserItemUpdate score :%s \n", pIClientUserItem->GetNickName());

	//变量定义
	tagUserInfo * pUserInfo=pIClientUserItem->GetUserInfo();
	tagUserInfo * pMeUserInfo=mMeUserItem->GetUserInfo();
	
	// 房间通知
	if (pIClientUserItem==mMeUserItem)
	{
		//变量定义
		CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
		tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
		tagUserInsureInfo * pUserInsureData=pGlobalUserInfo->GetUserInsureInfo();

		//设置变量
		pUserInsureData->lUserScore = pUserInsureData->lUserScore + pIClientUserItem->GetUserScore()-LastScore.lScore;
		pUserInsureData->lUserInsure= pUserInsureData->lUserInsure + pIClientUserItem->GetUserInsure()-LastScore.lInsure;
		pGlobalUserData->dwUserMedal= pGlobalUserData->dwUserMedal + pIClientUserItem->GetUserMedal()-LastScore.dwUserMedal;
	}

	if (mIServerItemSink)
		mIServerItemSink->OnGRUserUpdate(pIClientUserItem);

	//游戏通知
	if ((pMeUserInfo->wTableID!=INVALID_TABLE)&&(pUserInfo->wTableID==pMeUserInfo->wTableID))
	{
		//变量定义
		tagUserScore UserScore;
		zeromemory(&UserScore,sizeof(UserScore));

		//设置变量
		UserScore.lScore=pUserInfo->lScore;
		UserScore.lGrade=pUserInfo->lGrade;
		UserScore.lInsure=pUserInfo->lInsure;
		UserScore.dwWinCount=pUserInfo->dwWinCount;
		UserScore.dwLostCount=pUserInfo->dwLostCount;
		UserScore.dwDrawCount=pUserInfo->dwDrawCount;
		UserScore.dwFleeCount=pUserInfo->dwFleeCount;
		UserScore.dwUserMedal=pUserInfo->dwUserMedal;
		UserScore.dwExperience=pUserInfo->dwExperience;
		UserScore.lLoveLiness=pUserInfo->lLoveLiness;

		//发送数据
		if (IClientKernel::get())
			IClientKernel::get()->OnGFUserScore(pUserInfo->dwUserID,UserScore);
	}
	MELOG(MELOG_INFO, "flow->CServerItem::OnUserItemUpdate score finish:%s \n", pIClientUserItem->GetNickName());
}

void CServerItem::OnUserItemUpdate(IClientUserItem* pIClientUserItem, const tagUserStatus& LastStatus)
{
	MELOG(MELOG_INFO, "flow->CServerItem::OnUserItemUpdate status:%s \n", pIClientUserItem->GetNickName());
	//变量定义
	tagUserInfo * pUserInfo=pIClientUserItem->GetUserInfo();
	tagUserInfo * pMeUserInfo=mMeUserItem->GetUserInfo();
	word wNowTableID=pIClientUserItem->GetTableID(),wLastTableID=LastStatus.wTableID;
	word wNowChairID=pIClientUserItem->GetChairID(),wLastChairID=LastStatus.wChairID;
	byte cbNowStatus=pIClientUserItem->GetUserStatus(),cbLastStatus=LastStatus.cbUserStatus;

	if (mIServerItemSink)
		mIServerItemSink->OnGRUserUpdate(pIClientUserItem);

	//桌子离开
	if ((wLastTableID!=INVALID_TABLE)&&((wLastTableID!=wNowTableID)||(wLastChairID!=wNowChairID)))
	{
		IClientUserItem * pITableUserItem = mTableFrame.GetClientUserItem(wLastTableID,wLastChairID);
		if (pITableUserItem == pIClientUserItem) 
			mTableFrame.SetClientUserItem(wLastTableID,wLastChairID,0);
	}

	//桌子加入
	if ((wNowTableID!=INVALID_TABLE)&&(cbNowStatus!=US_LOOKON)&&((wNowTableID!=wLastTableID)||(wNowChairID!=wLastChairID)))
	{
		//厌恶判断（黑名单）
		if(pUserInfo->dwUserID != pMeUserInfo->dwUserID && cbNowStatus == US_SIT && pMeUserInfo->wTableID == wNowTableID)
		{
			//变量定义
			ASSERT(CParameterGlobal::shared()!=0);
			CParameterGlobal * pParameterGlobal=CParameterGlobal::shared();

			//厌恶玩家
			if (pParameterGlobal->m_bLimitDetest==true)
			{
				if (pIClientUserItem->GetUserCompanion()==CP_DETEST)
				{// 拒绝坐下
					PACKET_AIDE_SIZE(64);
					packet.write2Byte(wNowTableID);
					packet.write2Byte(wNowChairID);
					packet.write4Byte(pMeUserInfo->dwUserID);
					packet.write4Byte(pUserInfo->dwUserID);
					SendSocketData(MDM_GR_USER,SUB_GR_USER_REPULSE_SIT,packet.getBuffer(),packet.getPosition());
				}
			}
		}
		mTableFrame.SetClientUserItem(wNowTableID,wNowChairID,pIClientUserItem);
	}

	//桌子状态
	if ((mTableFrame.GetChairCount() < MAX_CHAIR)&&(wNowTableID!=INVALID_TABLE)&&(wNowTableID==wLastTableID)&&(wNowChairID==wLastChairID))
	{
		mTableFrame.SetClientUserItem(wNowTableID, wNowChairID, pIClientUserItem);
		mTableFrame.UpdateTable(wNowTableID);
	}

	//离开通知
	if ((wLastTableID!=INVALID_TABLE)&&((wNowTableID!=wLastTableID)||(wNowChairID!=wLastChairID)))
	{
		//游戏通知
		if ((pIClientUserItem==mMeUserItem)||(wLastTableID==pMeUserInfo->wTableID))
		{
			tagUserStatus UserStatus;
			UserStatus.wTableID=wNowTableID;
			UserStatus.wChairID=wNowChairID;
			UserStatus.cbUserStatus=cbNowStatus;
			if (IClientKernel::get())
				IClientKernel::get()->OnGFUserStatus(pUserInfo->dwUserID,UserStatus);
		}

		if (pIClientUserItem==mMeUserItem)
		{
			//设置变量
			mReqTableID=INVALID_TABLE;
			mReqChairID=INVALID_CHAIR;

			if (CServerRule::IsAllowQuickMode(mServerAttribute.dwServerRule))
			{//快速模式的
				IntermitConnect(true, true);
				if (mIServerItemSink)
					mIServerItemSink->OnGFServerClose("");
			}
			else
			{// 游戏关闭
				if (mIServerItemSink)
					mIServerItemSink->OnGFGameClose(mExitInfo, true);
			}
		}
		return;
	}

	//加入处理
	if ((wNowTableID!=INVALID_TABLE)&&((wNowTableID!=wLastTableID)||(wNowChairID!=wLastChairID)))
	{
		//自己判断
		if (mMeUserItem==pIClientUserItem)
		{
			//设置变量
			mReqTableID=INVALID_TABLE;
			mReqChairID=INVALID_CHAIR;

			if (IClientKernel::get()==0)
			{
				////启动进程
				IClientKernelSink* kernelSink = mIServerItemSink->CreateKernelSink();
				if (!kernelSink)
				{
					if (mIServerItemSink)
						mIServerItemSink->OnGFGameClose("kernel sink had not set", true);
					return;
				}

				IClientKernel* kernel = IClientKernel::create();

				if (kernel == 0)
				{
					if (mIServerItemSink)
						mIServerItemSink->OnGFGameClose("kernel create failed", true);
					return;
				}
				kernel->SetClientKernelSink(kernelSink);
				//kernel->SetStringMessageSink(kernelSink);

				if (!kernel->Init())
				{
					IClientKernel::destory();
					if (mIServerItemSink)
						mIServerItemSink->OnGFGameClose("kernel init failed", true);
					return;
				}
			}
		}

		//游戏通知
		if ((mMeUserItem!=pIClientUserItem)&&(pMeUserInfo->wTableID==wNowTableID))
		{
			ASSERT(wNowChairID!=INVALID_CHAIR);
			if (IClientKernel::get())
				IClientKernel::get()->OnGFUserEnter(pIClientUserItem);
		}

		return;
	}

	//状态改变
	if ((wNowTableID!=INVALID_TABLE)&&(wNowTableID==wLastTableID)&&(pMeUserInfo->wTableID==wNowTableID))
	{
		//游戏通知
		tagUserStatus UserStatus;
		UserStatus.wTableID=wNowTableID;
		UserStatus.wChairID=wNowChairID;
		UserStatus.cbUserStatus=cbNowStatus;

		if (IClientKernel::get())
			IClientKernel::get()->OnGFUserStatus(pUserInfo->dwUserID,UserStatus);
	}
	MELOG(MELOG_INFO, "flow->CServerItem::OnUserItemUpdate status finish:%s \n", pIClientUserItem->GetNickName());
}

//用户更新
void CServerItem::OnUserItemUpdate(IClientUserItem * pIClientUserItem, const tagUserAttrib & UserAttrib)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnUserItemUpdate 用户属性更新:%s"), pIClientUserItem->GetNickName());

	//变量定义
	word wMeTableID=mMeUserItem->GetTableID();
	word wUserTableID=pIClientUserItem->GetTableID();

	if (mIServerItemSink)
		mIServerItemSink->OnGRUserUpdate(pIClientUserItem);

	//通知游戏
	if ((wMeTableID!=INVALID_TABLE)&&(wMeTableID==wUserTableID))
	{
		//变量定义
		tagUserAttrib UserAttrib;
		UserAttrib.cbCompanion=pIClientUserItem->GetUserCompanion();

		//发送通知
		if (IClientKernel::get())
			IClientKernel::get()->OnGFUserAttrib(pIClientUserItem->GetUserID(),UserAttrib);
	}
}

//用户自定义桌子更新
void CServerItem::OnUserCustomTableUpdate(IClientUserItem* pIClientUserItem)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnUserCustomTableUpdate 用户自定义桌子更新:%s"), pIClientUserItem->GetNickName());
	//获取用户
	tagCustomTableInfo * pCustomTableInfo = pIClientUserItem->GetCustomTableInfo();
	if (mIServerItemSink)
		mIServerItemSink->OnGRUserUpdate(pIClientUserItem);

	//更新游戏
	if (pCustomTableInfo->wTableID != INVALID_TABLE)
	{ 
		if (IClientKernel::get())
			IClientKernel::get()->OnGFUserCustomTable(pIClientUserItem->GetUserID(), *pCustomTableInfo);
	}
}