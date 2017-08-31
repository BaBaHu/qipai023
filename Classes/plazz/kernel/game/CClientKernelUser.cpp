#include "CClientKernel.h"
#include "MELog.h"
//用户进入
void CClientKernel::OnGFUserEnter(IClientUserItem* pIClientUserItem)
{
	MELOG(MELOG_INFO, "flow->CClientKernel::OnGFUserEnter ... \n");

	//用户判断
	ASSERT(pIClientUserItem!=0);
	if (pIClientUserItem==0) return;

	ASSERT(mUserManager!=0);
	if (mUserManager)
		mUserManager->ActiveUserItem(
		*pIClientUserItem->GetUserInfo(),
		*pIClientUserItem->GetCustomFaceInfo(),
		pIClientUserItem->GetUserCompanion(),
		pIClientUserItem->GetUserNoteInfo());
}

//用户积分
void CClientKernel::OnGFUserScore(dword dwUserID, const tagUserScore& UserScore)
{
	MELOG(MELOG_INFO, "flow->CClientKernel::OnGFUserScore ... \n");

	//寻找用户
	IClientUserItem * pIClientUserItem=mUserManager->SearchUserByUserID(dwUserID);

	//用户判断
	ASSERT(pIClientUserItem!=0);
	if (pIClientUserItem==0) 
		return;

	ASSERT(mUserManager!=0);
	if (mUserManager)
		mUserManager->UpdateUserItemScore(pIClientUserItem,&UserScore);
}

//用户状态
void CClientKernel::OnGFUserStatus(dword dwUserID, const tagUserStatus& UserStatus)
{
	MELOG(MELOG_INFO, "flow->CClientKernel::OnGFUserStatus ... \n ");

	IClientUserItem* pIClientUserItem = mUserManager->SearchUserByUserID(dwUserID);

	//用户判断
	//ASSERT(pIClientUserItem!=0);
	if (pIClientUserItem==0) return;

	//状态定义
	byte cbUserStatus=UserStatus.cbUserStatus;

	//离开判断
	if ((cbUserStatus==US_NULL)||(cbUserStatus==US_FREE))
	{
		if (mMeUserItem==pIClientUserItem)
		{
			//设置变量
			mAllowLookon=false;
			mMeUserItem=0;
			mGameStatus=GAME_STATUS_FREE;
			zeromemory(&mUserAttribute,sizeof(mUserAttribute));

			//删除事件
			KillGameClock(0L);
			//重置时钟
			memset(m_wUserClock, 0, sizeof(m_wUserClock));

			//重置游戏
			if (mIClientKernelSink)
				mIClientKernelSink->ResetGameClient();

			//删除用户
			mUserManager->ResetUserItem();
		}
		else
		{
			//删除时间
			if (pIClientUserItem->GetUserStatus()!=US_LOOKON)
			{
				word wChairID=pIClientUserItem->GetChairID();
				if (m_wClockChairID==wChairID) KillGameClock(m_wClockID);
			}

			//删除用户
			mUserManager->DeleteUserItem(pIClientUserItem);
		}

		return;
	}

	ASSERT(mUserManager!=0);
	if (mUserManager)
		mUserManager->UpdateUserItemStatus(pIClientUserItem, &UserStatus);
}

//用户属性
void CClientKernel::OnGFUserAttrib(dword dwUserID, const tagUserAttrib& UserAttrib)
{
	PLAZZ_PRINTF(("flow->CClientKernel::OnGFUserAttrib 用户属性 "));

	//寻找用户
	IClientUserItem * pIClientUserItem=mUserManager->SearchUserByUserID(dwUserID);

	//用户判断
	ASSERT(pIClientUserItem!=0);
	if (pIClientUserItem==0) return ;

	ASSERT(mUserManager!=0);
	if (mUserManager)
		mUserManager->UpdateUserItemAttrib(pIClientUserItem,&UserAttrib);
}

//用户自定义头像
void CClientKernel::OnGFUserCustomFace(dword dwUserID, dword dwCustomID, const tagCustomFaceInfo& CustomFaceInfo)
{
	PLAZZ_PRINTF(("flow->CClientKernel::OnGFUserCustomFace 用户自定义头像 "));

	//寻找用户
	IClientUserItem * pIClientUserItem=mUserManager->SearchUserByUserID(dwUserID);

	//用户判断
	ASSERT(pIClientUserItem!=0);
	if (pIClientUserItem==0) return;

	ASSERT(mUserManager!=0);
	if (mUserManager)
		mUserManager->UpdateUserCustomFace(pIClientUserItem,dwCustomID,CustomFaceInfo);
}

//用户自定义桌子
void CClientKernel::OnGFUserCustomTable(dword dwUserID, const tagCustomTableInfo& CustomTableInfo)
{
	PLAZZ_PRINTF(("flow->CClientKernel::OnGFUserCustomTable 用户自定义桌子 "));

	//寻找用户
	IClientUserItem * pIClientUserItem = mUserManager->SearchUserByUserID(dwUserID);

	//用户判断
	ASSERT(pIClientUserItem != 0);
	if (pIClientUserItem == 0) return;

	for (word i = 0; i < MAX_CUSTOMTABLE_CHAIR; ++i)
		mCustTInfo.lChairScore[i] = CustomTableInfo.lChairScore[i];
	mCustTInfo.cbCurRound = CustomTableInfo.cbCurRound;
	if (CustomTableInfo.cbExData>0)
	{
		mCustTInfo.cbExData = CustomTableInfo.cbExData;
		mCustTInfo.dwCreateFlag = CustomTableInfo.dwCreateFlag;
		mCustTInfo.dwCreateUser = CustomTableInfo.dwCreateUser;
		mCustTInfo.cbMaxRound = CustomTableInfo.cbMaxRound;
		mCustTInfo.wChairCount = CustomTableInfo.wChairCount;
		mCustTInfo.wTableID = CustomTableInfo.wTableID;
	}

	ASSERT(mUserManager != 0);
	if (mUserManager)
		mUserManager->UpdateUserCustomTableInfo(pIClientUserItem, CustomTableInfo);
}