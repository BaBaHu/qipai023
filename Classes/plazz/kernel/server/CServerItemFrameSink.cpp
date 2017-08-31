#include "CServerItem.h"

//////////////////////////////////////////////////////////////////////////
// 框架消息

//游戏已准备好
void CServerItem::OnGFGameReady()
{
	PLAZZ_PRINTF(("flow->CServerItem::OnGFGameReady 游戏已准备好 "));

	//变量定义
	word wTableID=mMeUserItem->GetTableID();
	word wChairID=mMeUserItem->GetChairID();

	////房间配置
	//if (bAlreadyExist==false)
	//{
	//	//获取等级
	//	tagLevelItem LevelItem[64];
	//	byte cbLevelCount=(byte)m_GameLevelParserModule->GetGameLevelItem(LevelItem,CountArray(LevelItem));

	//	//发送配置
	//	m_ProcessManager.SendLevelInfo(LevelItem,cbLevelCount);
	//	m_ProcessManager.SendColumnInfo(m_ColumnItem,m_cbColumnCount);
	//	m_ProcessManager.SendPropertyInfo(m_PropertyInfo,m_cbPropertyCount);		
	//}

	mUserAttribute.wChairID = wChairID;
	mUserAttribute.wTableID = wTableID;
	//房间信息
	IClientKernel::get()->OnGFConfigServer(mUserAttribute, mServerAttribute);

	//发送用户
	if ((wTableID!=INVALID_TABLE)&&(wChairID!=INVALID_CHAIR))
	{
		//变量定义
		word wEnumIndex=0;
		
		//发送玩家
		while (true)
		{
			//获取用户
			IClientUserItem * pIClientUserItem=mUserManager->EnumUserItem(wEnumIndex++);
			if (pIClientUserItem==0) break;

			//发送判断
			if (pIClientUserItem->GetTableID()!=wTableID) continue;
			if (pIClientUserItem->GetUserStatus()==US_LOOKON) continue;

			//发送用户
			IClientKernel::get()->OnGFUserEnter(pIClientUserItem);
		};

		//旁观用户
		wEnumIndex=0;
		while (true)
		{
			//获取用户
			IClientUserItem * pIClientUserItem=mUserManager->EnumUserItem(wEnumIndex++);
			if (pIClientUserItem==0) break;

			//发送判断
			if (pIClientUserItem->GetTableID()!=wTableID) continue;
			if (pIClientUserItem->GetUserStatus()!=US_LOOKON) continue;

			//发送用户
			IClientKernel::get()->OnGFUserEnter(pIClientUserItem);
		};
	}

	//配置完成
	IClientKernel::get()->OnGFConfigFinish();
	
	mIsGameReady = true;
}

//游戏关闭
void CServerItem::OnGFGameClose(const std::string& sInfo, bool bExitGame)
{
	PLAZZ_PRINTF("flow->CServerItem::OnGFGameClose 游戏关闭 bExitGame= %d", bExitGame);
	//效验状态
	ASSERT(mMeUserItem!=0);
	if (mMeUserItem==0) return ;
	mExitInfo = sInfo;
	mIsGameReady = false;

	//变量定义
	word wTableID=mMeUserItem->GetTableID();
	word wChairID=mMeUserItem->GetChairID();
	byte cbUserStatus=mMeUserItem->GetUserStatus();
	mUserAttribute.wChairID = INVALID_CHAIR;
	mUserAttribute.wTableID = INVALID_TABLE;

	//退出游戏
	if ((wTableID != INVALID_TABLE) && (mServiceStatus == ServiceStatus_ServiceIng) && bExitGame)
	{
		SendStandUpPacket(wTableID,wChairID,TRUE);
	}

	mTableFrame.SetTableStatus(false);
}

//恢复游戏
bool CServerItem::OnRecoveryGame()
{
	if (IClientKernel::get() == 0)
	{
		////启动进程
		//if (!mIServerItemSink)
		//{
		//	if (mIServerItemSink)
		//		mIServerItemSink->OnGFGameClose("create failed", true);
		//	return false;
		//}

		IClientKernelSink* kernelSink = mIServerItemSink->CreateKernelSink();
		if (!kernelSink)
		{
			if (mIServerItemSink)
				mIServerItemSink->OnGFGameClose("kernel sink had not set", true);
			return false;
		}

		IClientKernel* kernel = IClientKernel::create();
		if (kernel == 0)
		{
			if (mIServerItemSink)
				mIServerItemSink->OnGFGameClose("kernel create failed", true);
			return false;
		}
		kernel->SetClientKernelSink(kernelSink);

		if (!kernel->Init())
		{
			IClientKernel::destory();
			if (mIServerItemSink)
				mIServerItemSink->OnGFGameClose("kernel init failed", true);
			return false;
		}
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
// Socket消息

// 发送数据
bool CServerItem::GFSendData(int main, int sub, void* data, int size)
{
	return SendSocketData(main, sub, data, size);
}