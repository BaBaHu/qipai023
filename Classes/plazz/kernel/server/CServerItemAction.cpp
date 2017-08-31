#include "CServerItem.h"


//查找桌子
bool CServerItem::SearchGameTable(tagSearchTable & SearchTable)
{
	PLAZZ_PRINTF(("flow->CServerItem::SearchGameTable 查找桌子"));
	//变量定义
	word wNullCount=0;
	word wChairUser=mTableFrame.GetChairCount();
	word wMeTableID=mMeUserItem->GetTableID();

	//百人游戏
	if (CServerRule::IsAllowDynamicJoin(mServerAttribute.dwServerRule)==true)
	{
		if(mTableFrame.GetChairCount() >= MAX_CHAIR)
		{
			SearchTable.wResultTableID=0;
			SearchTable.wResultChairID=MAX_CHAIR;
			return true;
		}
	}

	//搜索桌子
	for (word i=0;i<mTableFrame.GetTableCount();i++)
	{
		//设置索引
		SearchTable.wResultTableID=(SearchTable.wStartTableID+i)%mTableFrame.GetTableCount();

		//搜索处理
		if (wMeTableID!=SearchTable.wResultTableID)
		{
			//获取桌子
			ITable * pITable=mTableFrame.GetTableItem(SearchTable.wResultTableID);

			//搜索过虑
			if (pITable->GetPlayFlag()==true) continue;
			if ((SearchTable.bFilterPass==true)&&(pITable->GetLockerFlag()==true)) continue;

			//寻找空位置
			wNullCount=pITable->GetNullChairCount(SearchTable.wResultChairID);

			//判断数目
			if (wNullCount>0)
			{
				//效验规则
				char strDescribe[256];
				if (EfficacyTableRule(SearchTable.wResultTableID,SearchTable.wResultChairID,false,strDescribe)==false)
				{
					continue;
				}

				//数目判断
				if ((SearchTable.bOneNull==true)&&(wNullCount==1)) return true;
				if ((SearchTable.bTwoNull==true)&&(wNullCount==2)) return true;
				if ((SearchTable.bNotFull==true)&&(wNullCount<wChairUser)) return true;
				if ((SearchTable.bAllNull==true)&&(wNullCount==wChairUser)) return true;
			}
		}
	}

	//设置数据
	SearchTable.wResultTableID=INVALID_TABLE;
	SearchTable.wResultChairID=INVALID_CHAIR;

	return false;
}

//快速加入
bool CServerItem::PerformQuickSitDown()
{
	PLAZZ_PRINTF("flow->CServerItem::PerformQuickSitDown 快速加入 ");
	mIsQuickSitDown=true;
	//return SendSocketData(MDM_GR_USER, SUB_GR_USER_CHAIR_REQ);
	//发送命令
	char szPassword[LEN_PASSWORD] = { 0 };
	return SendSitDownPacket(INVALID_TABLE, INVALID_CHAIR, szPassword);
} 

//更换位置
bool CServerItem::PerformChangeChair()
{
	PLAZZ_PRINTF(("flow->CServerItem::PerformChangeChair 更换位置 "));
	return SendSocketData(MDM_GR_USER, SUB_GR_USER_CHAIR_REQ);
} 

//执行刷新桌子
bool CServerItem::PerformRefreshTabe(word wTableIdx)
{
	PLAZZ_PRINTF("flow->CServerItem::PerformRefreshTabe 更新桌子 = %d",wTableIdx);
	return SendRefreshTabePacket(wTableIdx);
}

//
//bool CServerItem::PerformAutoJoin()
//{
//	//变量定义
//	tagSearchTable SearchTable;
//	zeromeory(&SearchTable,sizeof(SearchTable));
//
//	//搜索条件
//	SearchTable.bNotFull=true;
//	SearchTable.bOneNull=true;
//	SearchTable.bTwoNull=(mTableFrame.GetChairCount()!=2);
//	SearchTable.bAllNull=false;
//	SearchTable.bFilterPass=true;
//	
//	//搜索结果
//	SearchTable.wResultTableID=INVALID_TABLE;
//	SearchTable.wResultChairID=INVALID_CHAIR;
//	SearchTable.wStartTableID=0;
//
//	//搜索桌子
//	SearchGameTable(SearchTable);
//	mFindTableID=SearchTable.wResultTableID;
//
//	//搜索桌子
//	if (mFindTableID==INVALID_CHAIR)
//	{
//		//搜索条件
//		SearchTable.bAllNull=true;
//		SearchTable.bNotFull=true;
//		SearchTable.bOneNull=true;
//		SearchTable.bFilterPass=true;
//		SearchTable.bTwoNull=(mTableFrame.GetChairCount()!=2);
//
//		//搜索结果
//		SearchTable.wResultTableID=INVALID_TABLE;
//		SearchTable.wResultChairID=INVALID_CHAIR;
//		SearchTable.wStartTableID=mFindTableID+1;
//
//		//搜索桌子
//		SearchGameTable(SearchTable);
//		mFindTableID=SearchTable.wResultTableID;
//	}
//
//	//结果判断
//	if (mFindTableID!=INVALID_CHAIR)
//	{
//		//效验数据
//		ASSERT(SearchTable.wResultTableID!=INVALID_TABLE);
//		ASSERT(SearchTable.wResultChairID!=INVALID_CHAIR);
//
//		//设置数据
//		word wChairID=SearchTable.wResultChairID;
//		mTableFrame.VisibleTable(mFindTableID);
//		mTableFrame.FlashGameChair(mFindTableID,wChairID);
//
//		//自动坐下
//		CParameterGlobal * pParameterGlobal=CParameterGlobal::shared();
//		if (pParameterGlobal->m_bAutoSitDown==true) PerformSitDownAction(mFindTableID,wChairID,true);
//	}
//	else
//	{
//		//提示消息
//		if (mIStringMessageSink)
//			mIStringMessageSink->InsertPromptString("抱歉，现在暂时没有可以加入的游戏桌，请稍后再次尝试！", DLG_MB_OK);
//	}
//
//	return false;
//}


//执行旁观
bool CServerItem::PerformLookonAction(word wTableID, word wChairID)
{
	PLAZZ_PRINTF(("flow->CServerItem::PerformLookonAction 执行旁观"));

	if (!IsService())
		return false;

	//效验数据
	ASSERT(wTableID!=INVALID_TABLE);
	ASSERT(wChairID!=INVALID_CHAIR);

	//状态过滤
	if (mServiceStatus!=ServiceStatus_ServiceIng) return false;
	if ((mReqTableID==wTableID)&&(mReqChairID==wChairID)) return false;

	//自己状态
	if (mMeUserItem->GetUserStatus()>=US_PLAYING)
	{
		CGDialog("系统提示", 4, CGDLG_MB_OK, nullptr, nullptr);
		return false;
	}

	//权限判断
	if (CUserRight::CanLookon(mUserAttribute.dwUserRight)==false)
	{
		CGDialog("系统提示", 5, CGDLG_MB_OK, nullptr, nullptr);
		return false;
	}

	//清理界面
	if ((mReqTableID!=INVALID_TABLE)&&(mReqChairID!=INVALID_CHAIR)&&(mReqChairID!=MAX_CHAIR))
	{
		IClientUserItem * pIClientUserItem=mTableFrame.GetClientUserItem(mReqTableID,mReqChairID);
		if (pIClientUserItem==mMeUserItem) mTableFrame.SetClientUserItem(mReqTableID,mReqChairID,0);
	}

	//设置变量
	mReqTableID=wTableID;
	mReqChairID=wChairID;
	mFindTableID=INVALID_TABLE;

	//设置界面
	mTableFrame.VisibleTable(wTableID);

	PLAZZ_PRINTF("CServerItem::PerformLookonAction send\n");
	//发送命令
	SendLookonPacket(wTableID,wChairID);

	return true;
}

//执行起立
bool CServerItem::PerformStandUpAction(word wTableID, word wChairID)
{
	PLAZZ_PRINTF(("flow->CServerItem::PerformStandUpAction 执行起立 "));

	if (!IsService())
		return false;

	//效验数据
	ASSERT(wTableID!=INVALID_TABLE);
	ASSERT(wChairID!=INVALID_CHAIR);

	//状态过滤
	if (mServiceStatus!=ServiceStatus_ServiceIng) return false;
	if ((mReqTableID==wTableID)&&(mReqChairID==wChairID)) return false;

	//自己状态
	if (mMeUserItem->GetUserStatus()>=US_PLAYING)
	{
		CGDialog("系统提示", 4, CGDLG_MB_OK, nullptr, nullptr);
		return false;
	}

	//设置变量
	mReqTableID=INVALID_TABLE;
	mReqChairID=INVALID_CHAIR;
	mFindTableID=INVALID_TABLE;

	//设置界面
	mTableFrame.VisibleTable(wTableID);

	PLAZZ_PRINTF("CServerItem::PerformStandUpAction send\n");
	//发送命令
	SendStandUpPacket(wTableID,wChairID,FALSE);

	return true;
}

//执行坐下
bool CServerItem::PerformSitDownAction(word wTableID, word wChairID, bool bEfficacyPass)
{
	PLAZZ_PRINTF(("flow->CServerItem::PerformSitDownAction 执行坐下 "));

	if (!IsService())
		return false;

	//状态过滤
	if (mServiceStatus!=ServiceStatus_ServiceIng) return false;
	if ((mReqTableID!=INVALID_TABLE)&&(mReqTableID==wTableID)) return false;
	if ((mReqChairID!=INVALID_CHAIR)&&(mReqChairID==wChairID)) return false;

	//自己状态
	if (mMeUserItem->GetUserStatus()>=US_PLAYING)
	{
		CGDialog("系统提示", 4, CGDLG_MB_OK, nullptr, nullptr);
		return false;
	}

	//权限判断
	if (CUserRight::CanPlay(mUserAttribute.dwUserRight)==false)
	{
		CGDialog("系统提示", 6, CGDLG_MB_OK, nullptr, nullptr);
		return false;
	}

	//桌子效验
	if ((wTableID!=INVALID_TABLE)&&(wChairID!=INVALID_CHAIR))
	{
		char strDescribe[256]={0};
		if ((wChairID!=MAX_CHAIR)&&(EfficacyTableRule(wTableID,wChairID,false,strDescribe)==false))
		{
			//CGDialog("系统提示", strDescribe, CGDLG_MB_OK, nullptr, nullptr);
			return false;
		}
	}

	//密码判断
	char szPassword[LEN_PASSWORD] = {0};
	if ((mMeUserItem->GetMasterOrder()==0)&&(bEfficacyPass==true)&&(wTableID!=INVALID_TABLE)&&(wChairID!=INVALID_CHAIR)&&(wChairID!=MAX_CHAIR))
	{
		//变量定义
		bool bLocker=mTableFrame.GetLockerFlag(wTableID);

		//密码判断
		if(bLocker)
		{
			CGDialog("系统提示", 7, CGDLG_MB_OK, nullptr, nullptr);

			////设置密码
			//CDlgTablePassword DlgTablePassword;
			//DlgTablePassword.SetPromptString(T_T("该桌已设置进入密码，请输入密码。"));
			//if (DlgTablePassword.DoModal()!=IDOK) return false;
			////设置密码
			//tstrcpyn(szPassword,DlgTablePassword.m_szPassword,CountArray(szPassword));

			//PLAZZ_PRINTF(("//TODO:该桌已设置进入密码，请输入密码。 未实现!!!!\n"));
			return false;
		}
	}

	//清理界面
	if ((mReqTableID!=INVALID_TABLE)&&(mReqChairID!=INVALID_CHAIR)&&(mReqChairID!=MAX_CHAIR))
	{
		IClientUserItem * pIClientUserItem=mTableFrame.GetClientUserItem(mReqTableID,mReqChairID);
		if (pIClientUserItem==mMeUserItem) mTableFrame.SetClientUserItem(mReqTableID,mReqChairID,0);
	}

	//设置界面
	if ((wChairID!=MAX_CHAIR)&&(wTableID!=INVALID_TABLE)&&(wChairID!=INVALID_CHAIR))
	{
		mTableFrame.VisibleTable(wTableID);
		mTableFrame.SetClientUserItem(wTableID,wChairID,mMeUserItem);
	}

	//设置变量
	mReqTableID=wTableID;
	mReqChairID=wChairID;
	mFindTableID=INVALID_TABLE;

	//发送命令
	SendSitDownPacket(wTableID,wChairID,szPassword);
	return true;
}

//执行购买
bool CServerItem::PerformBuyProperty(byte cbRequestArea,const char* pszNickName, word wItemCount, word wPropertyIndex)
{
	PLAZZ_PRINTF(("flow->CServerItem::PerformBuyProperty 执行购买 "));

	if (!IsService())
		return false;

	//PLAZZ_PRINTF(("//TODO:执行购买。 未实现!!!!\n"));
	return true;

	////变量定义
	//ASSERT(CGamePropertyManager::GetInstance()!=0);
	//CGamePropertyManager * pGamePropertyManager=CGamePropertyManager::GetInstance();

	////查找道具
	//ASSERT(pGamePropertyManager->GetPropertyItem(wPropertyIndex)!=0);
	//CGamePropertyItem * pGamePropertyItem=pGamePropertyManager->GetPropertyItem(wPropertyIndex);
	//if(pGamePropertyItem==0) return false;

	////查找用户
	//IClientUserItem * pIClientUserItem=m_PlazaUserManagerModule->SearchUserByNickName(pszNickName);

	////用户判断
	//if (pIClientUserItem==0)
	//{
	//	return false;
	//}

	////变量定义
	//CMD_GR_C_PropertyBuy PropertyBuy;
	//zeromemory(&PropertyBuy,sizeof(PropertyBuy));

	////设置变量
	//PropertyBuy.cbRequestArea=cbRequestArea;
	//PropertyBuy.wItemCount=wItemCount;
	//PropertyBuy.wPropertyIndex=wPropertyIndex;
	//PropertyBuy.dwTargetUserID=pIClientUserItem->GetUserID();
	//PropertyBuy.cbConsumeScore=FALSE;

	////发送消息
	//m_TCPSocketModule->SendData(MDM_GR_USER,SUB_GR_PROPERTY_BUY,&PropertyBuy,sizeof(PropertyBuy));

	//return true;
}
