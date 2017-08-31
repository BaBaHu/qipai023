#include "CClientKernel.h"
#include "MELog.h"
//�û�����
void CClientKernel::OnGFUserEnter(IClientUserItem* pIClientUserItem)
{
	MELOG(MELOG_INFO, "flow->CClientKernel::OnGFUserEnter ... \n");

	//�û��ж�
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

//�û�����
void CClientKernel::OnGFUserScore(dword dwUserID, const tagUserScore& UserScore)
{
	MELOG(MELOG_INFO, "flow->CClientKernel::OnGFUserScore ... \n");

	//Ѱ���û�
	IClientUserItem * pIClientUserItem=mUserManager->SearchUserByUserID(dwUserID);

	//�û��ж�
	ASSERT(pIClientUserItem!=0);
	if (pIClientUserItem==0) 
		return;

	ASSERT(mUserManager!=0);
	if (mUserManager)
		mUserManager->UpdateUserItemScore(pIClientUserItem,&UserScore);
}

//�û�״̬
void CClientKernel::OnGFUserStatus(dword dwUserID, const tagUserStatus& UserStatus)
{
	MELOG(MELOG_INFO, "flow->CClientKernel::OnGFUserStatus ... \n ");

	IClientUserItem* pIClientUserItem = mUserManager->SearchUserByUserID(dwUserID);

	//�û��ж�
	//ASSERT(pIClientUserItem!=0);
	if (pIClientUserItem==0) return;

	//״̬����
	byte cbUserStatus=UserStatus.cbUserStatus;

	//�뿪�ж�
	if ((cbUserStatus==US_NULL)||(cbUserStatus==US_FREE))
	{
		if (mMeUserItem==pIClientUserItem)
		{
			//���ñ���
			mAllowLookon=false;
			mMeUserItem=0;
			mGameStatus=GAME_STATUS_FREE;
			zeromemory(&mUserAttribute,sizeof(mUserAttribute));

			//ɾ���¼�
			KillGameClock(0L);
			//����ʱ��
			memset(m_wUserClock, 0, sizeof(m_wUserClock));

			//������Ϸ
			if (mIClientKernelSink)
				mIClientKernelSink->ResetGameClient();

			//ɾ���û�
			mUserManager->ResetUserItem();
		}
		else
		{
			//ɾ��ʱ��
			if (pIClientUserItem->GetUserStatus()!=US_LOOKON)
			{
				word wChairID=pIClientUserItem->GetChairID();
				if (m_wClockChairID==wChairID) KillGameClock(m_wClockID);
			}

			//ɾ���û�
			mUserManager->DeleteUserItem(pIClientUserItem);
		}

		return;
	}

	ASSERT(mUserManager!=0);
	if (mUserManager)
		mUserManager->UpdateUserItemStatus(pIClientUserItem, &UserStatus);
}

//�û�����
void CClientKernel::OnGFUserAttrib(dword dwUserID, const tagUserAttrib& UserAttrib)
{
	PLAZZ_PRINTF(("flow->CClientKernel::OnGFUserAttrib �û����� "));

	//Ѱ���û�
	IClientUserItem * pIClientUserItem=mUserManager->SearchUserByUserID(dwUserID);

	//�û��ж�
	ASSERT(pIClientUserItem!=0);
	if (pIClientUserItem==0) return ;

	ASSERT(mUserManager!=0);
	if (mUserManager)
		mUserManager->UpdateUserItemAttrib(pIClientUserItem,&UserAttrib);
}

//�û��Զ���ͷ��
void CClientKernel::OnGFUserCustomFace(dword dwUserID, dword dwCustomID, const tagCustomFaceInfo& CustomFaceInfo)
{
	PLAZZ_PRINTF(("flow->CClientKernel::OnGFUserCustomFace �û��Զ���ͷ�� "));

	//Ѱ���û�
	IClientUserItem * pIClientUserItem=mUserManager->SearchUserByUserID(dwUserID);

	//�û��ж�
	ASSERT(pIClientUserItem!=0);
	if (pIClientUserItem==0) return;

	ASSERT(mUserManager!=0);
	if (mUserManager)
		mUserManager->UpdateUserCustomFace(pIClientUserItem,dwCustomID,CustomFaceInfo);
}

//�û��Զ�������
void CClientKernel::OnGFUserCustomTable(dword dwUserID, const tagCustomTableInfo& CustomTableInfo)
{
	PLAZZ_PRINTF(("flow->CClientKernel::OnGFUserCustomTable �û��Զ������� "));

	//Ѱ���û�
	IClientUserItem * pIClientUserItem = mUserManager->SearchUserByUserID(dwUserID);

	//�û��ж�
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