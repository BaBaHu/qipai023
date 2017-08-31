#include "../server/CServerItem.h"
#include "CClientKernel.h"
#include "MELog.h"
//////////////////////////////////////////////////////////////////////////
//
int __gClentKernelRefCount = 0;
IClientKernel* __gClientKernel = 0;

IClientKernel* IClientKernel::create()
{
	if (__gClentKernelRefCount == 0)
	{
		__gClientKernel = new CClientKernel();
	}
	__gClentKernelRefCount++;

	PLAZZ_PRINTF("flow->IClientKernel::create ref:%d", __gClentKernelRefCount);

	return __gClientKernel;
}

void IClientKernel::destory()
{
	if (__gClentKernelRefCount > 0)
	{
		__gClentKernelRefCount--;
		if (__gClentKernelRefCount <= 0)
		{
			__gClentKernelRefCount = 0;
			delete __gClientKernel;
			__gClientKernel = 0;
		}
	}

	PLAZZ_PRINTF("flow->IClientKernel::destory ref:%d", __gClentKernelRefCount);
}

IClientKernel* IClientKernel::get()
{
	return __gClientKernel;
}

//////////////////////////////////////////////////////////////////////////
CClientKernel::CClientKernel() 
: mAllowLookon(false)
, mGameStatus(GAME_STATUS_FREE)
, mMeUserItem(0)
, mIClientKernelSink(0)
, mIChatSink(0)
, mIStringMessageSink(0)
{
	//时间信息
	m_wClockID=0L;
	m_nElapseCount=0L;
	m_wClockChairID=INVALID_CHAIR;
	memset(m_wUserClock, 0, sizeof(m_wUserClock));

	PLAZZ_PRINTF("flow->CClientKernel::CClientKernel");
	memset(&mUserAttribute,   0, sizeof(mUserAttribute));
	memset(&mGameAttribute,   0, sizeof(mGameAttribute));
	memset(&mServerAttribute, 0, sizeof(mServerAttribute));
	memset(&mCustTInfo, 0, sizeof(mCustTInfo));

	mUserManager  = new CGameUserManager();
	mUserManager->SetUserManagerSink(this);
	mTimerEngine.SetTimerEngineSink(this);
	gGlobalUnits.InitGlobalUnits();
}

CClientKernel::~CClientKernel()
{
	mUserManager->SetUserManagerSink(0);
	mTimerEngine.SetTimerEngineSink(0);
	mTimerEngine.StopService();
	SafeDelete(mUserManager);
	mUserManager  = 0;
	mIClientKernelSink=0;
	mIChatSink=0;
	mIStringMessageSink=0;
	gGlobalUnits.UnInitGlobalUnits();
	PLAZZ_PRINTF("flow->CClientKernel::~CClientKernel");
}

//////////////////////////////////////////////////////////////////////////
// IClientKernel
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//配置接口

//设置接口
bool CClientKernel::SetClientKernelSink(IClientKernelSink* pIClientKernelSink)
{
	PLAZZ_PRINTF("flow->CClientKernel::SetClientKernelSink 设置接口");
	mIClientKernelSink = pIClientKernelSink;
	return true;
}

//设置接口
bool CClientKernel::SetChatSink(IChatSink* pIChatSink)
{
	PLAZZ_PRINTF(("flow->CClientKernel::SetChatSink 设置接口"));
	mIChatSink = pIChatSink;
	return true;
}

//设置接口
bool CClientKernel::SetStringMessageSink(IStringMessageSink* pIStringMessageSink)
{
	PLAZZ_PRINTF(("flow->CClientKernel::SetStringMessageSink 设置接口"));
	mIStringMessageSink = pIStringMessageSink;
	return true;
}

//内核配置
bool CClientKernel::Init()
{
	PLAZZ_PRINTF(("flow->CClientKernel::Init 内核初始化 "));
	//mSocketEngine->setTCPValidate(true);
	mGameAttribute.wKindID			= DF::shared()->GetGameKindID();
	mGameAttribute.dwClientVersion	= DF::shared()->GetGameVersion();
	mGameAttribute.wChairCount		= DF::shared()->GetGamePlayer();
	
	DF::shared()->GetGameName(mGameAttribute.szGameName);
	//时间引擎
	mTimerEngine.StartService();
	if (IServerItem::get())
		IServerItem::get()->OnGFGameReady();
	return true;
}

bool CClientKernel::Intermit(const std::string& sInfo, bool bExitGame)
{
	PLAZZ_PRINTF("flow->CClientKernel::Intermit 关闭游戏 bExitGame= %d", bExitGame);
	if (mIClientKernelSink!=0)
		mIClientKernelSink->CloseGameClient();
	if (IServerItem::get())
		IServerItem::get()->OnGFGameClose(sInfo, bExitGame);
	IClientKernel::destory();
	return true;
}

//////////////////////////////////////////////////////////////////////////
//属性接口

//用户属性
tagUserAttribute * CClientKernel::GetUserAttribute()
{
	return &mUserAttribute;
}

//游戏属性
tagGameAttribute * CClientKernel::GetGameAttribute()
{
	return &mGameAttribute;
}

//房间属性
tagServerAttribute * CClientKernel::GetServerAttribute()
{
	return &mServerAttribute;
}

//自定义房间属性
tagCustomTableInfo* CClientKernel::GetCustomTableInfo()
{ 
	return &mCustTInfo; 
}

//////////////////////////////////////////////////////////////////////////
//模式接口

//单机模式
bool CClientKernel::IsSingleMode()
{
	return false;
}

//旁观状态
bool CClientKernel::IsLookonMode()
{
	if (mMeUserItem == 0) return true;
	return mMeUserItem->GetUserStatus() == US_LOOKON;
}

//允许状态
bool CClientKernel::IsAllowLookon()
{
	return mAllowLookon;

}

//////////////////////////////////////////////////////////////////////////
//状态接口

//获取状态
byte CClientKernel::GetGameStatus()
{
	return mGameStatus;
}

//设置状态
void CClientKernel::SetGameStatus(byte cbGameStatus)
{
	mGameStatus = cbGameStatus;
}


//////////////////////////////////////////////////////////////////////////
//用户接口

//自己位置
word CClientKernel::GetMeChairID()
{
	if (mMeUserItem == 0) return INVALID_CHAIR;
	return mMeUserItem->GetChairID();
}

//自己位置
IClientUserItem * CClientKernel::GetMeUserItem()
{
	return mMeUserItem;
}

//游戏用户
IClientUserItem * CClientKernel::GetTableUserItem(word wChairID)
{
	return mUserManager->GetTableUserItem(wChairID);
}

//游戏视图用户
IClientUserItem * CClientKernel::GetViewUserItem(word wChariID)
{
	return GetTableUserItem(SwitchViewChairID(wChariID));
}
//查找用户
IClientUserItem * CClientKernel::SearchUserByUserID(dword dwUserID)
{
	return mUserManager->SearchUserByUserID(dwUserID);
}

//查找用户
IClientUserItem * CClientKernel::SearchUserByGameID(dword dwGameID)
{
	return mUserManager->SearchUserByGameID(dwGameID);
}

//查找用户
IClientUserItem * CClientKernel::SearchUserByNickName(const char* szNickName)
{
	return mUserManager->SearchUserByNickName(szNickName);
}

//旁观用户
IClientUserItem * CClientKernel::EnumLookonUserItem(word wEnumIndex)
{
	return mUserManager->EnumLookonUserItem(wEnumIndex);
}


//////////////////////////////////////////////////////////////////////////
//网络接口

//发送函数
bool CClientKernel::SendSocketData(word wSubCmdID)
{
	return SendSocketData(MDM_GF_GAME, wSubCmdID, 0, 0);
}

//发送函数
bool CClientKernel::SendSocketData(word wSubCmdID, void * data, word dataSize)
{
	return SendSocketData(MDM_GF_GAME, wSubCmdID, data, dataSize);
}



//发送函数
bool CClientKernel::SendSocketData(word wMainCmdID, word wSubCmdID)
{
	return SendSocketData(wMainCmdID, wSubCmdID, 0, 0);
}

//发送函数
bool CClientKernel::SendSocketData(word wMainCmdID, word wSubCmdID, void * data, word dataSize)
{
	if (!IServerItem::get())
		return false;

	return IServerItem::get()->GFSendData(wMainCmdID, wSubCmdID, (unsigned char*)data, dataSize);
}

//////////////////////////////////////////////////////////////////////////
//功能接口
//发送进入场景
bool CClientKernel::SendGameOption()
{
	PLAZZ_PRINTF(("flow->CClientKernel::SendGameOption 发送游戏配置(进入场景)"));
	//发送场景消息
	//变量定义
	PACKET_AIDE_SIZE(512);
	packet.writeByte(gGlobalUnits.m_bAllowLookon);
	packet.write4Byte(DF::shared()->GetFrameVersion());
	packet.write4Byte(mGameAttribute.dwClientVersion);


	//发送数据
	return SendSocketData(MDM_GF_FRAME,SUB_GF_GAME_OPTION, packet.getBuffer(), packet.getPosition());
}

//发送准备
bool CClientKernel::SendUserReady(void * data, word dataSize)
{
	PLAZZ_PRINTF(("flow->CClientKernel::SendUserReady 发送准备 "));
	if (mMeUserItem == 0) return false;
	return SendSocketData(MDM_GF_FRAME, SUB_GF_USER_READY, data, dataSize);
}

//旁观控制
bool CClientKernel::SendUserLookon(dword dwUserID, bool bAllowLookon)
{
	PLAZZ_PRINTF(("flow->CClientKernel::SendUserLookon 旁观控制 "));

	if (!IsLookonMode()) {
		PACKET_AIDE_SIZE(6);
		packet.write4Byte(dwUserID);
		packet.writeByte(bAllowLookon?1:0);
		return SendSocketData(MDM_GF_FRAME, SUB_GF_LOOKON_CONFIG, packet.getBuffer(), packet.getPosition());
	}
	return true;
}

//发送表情
bool CClientKernel::SendUserExpression(dword dwTargetUserID, word wItemIndex)
{
	PLAZZ_PRINTF(("flow->CClientKernel::SendUserExpression 发送表情 "));
	//变量定义
	PACKET_AIDE_SIZE(6);
	packet.write2Byte(wItemIndex);
	packet.write4Byte(dwTargetUserID);
	//发送命令
	SendSocketData(MDM_GF_FRAME,SUB_GF_USER_EXPRESSION, packet.getBuffer(), packet.getPosition());
	return true;
}

//发送聊天
bool CClientKernel::SendUserChatMessage(dword dwTargetUserID, const char* pszChatString, dword crColor)
{
	PLAZZ_PRINTF(("flow->CClientKernel::SendUserChatMessage 发送聊天 "));
	if (mMeUserItem == 0) return false;

	//const unsigned short* ucs2 = u8_2(pszChatString);
	//int ucs2len = ucs2_len(ucs2);
	//PACKET_AIDE_SIZE(512);
	//packet.writeByte(ucs2len);
	//packet.write4Byte((crColor<<8)|(crColor>>24&0xff));
	//packet.write4Byte(dwTargetUserID);
	//packet.writeUTF16(ucs2, ucs2len);
	std::string u2 = u2l(pszChatString);
	int ucs2len = u2len(u2);
	PACKET_AIDE_SIZE(512);
	packet.writeByte(ucs2len);
	packet.write4Byte((crColor<<8)|(crColor>>24&0xff));
	packet.write4Byte(dwTargetUserID);
	packet.writeString(u2, ucs2len);
	return SendSocketData(MDM_GF_FRAME, SUB_GF_USER_CHAT, packet.getBuffer(), packet.getPosition());
}

//////////////////////////////////////////////////////////////////////////
// 时钟接口
//获取用户时间
word CClientKernel::GetUserClock(word wChairID)
{
	//效验参数
	ASSERT(wChairID<MAX_CHAIR);
	if (wChairID >= MAX_CHAIR) return 0;

	//获取时间
	return m_wUserClock[wChairID];
}

//设置用户时间
void CClientKernel::SetUserClock(word wChairID, word wUserClock)
{
	//设置变量
	if (wChairID == INVALID_CHAIR)
	{
		for (word i=0;i<MAX_CHAIR;i++)
		{
			m_wUserClock[i]=wUserClock;
		}
	}
	else
	{
		m_wUserClock[wChairID] = wUserClock;
	}

	//更新界面
	if (mIClientKernelSink != NULL) mIClientKernelSink->OnEventUserClock(wChairID, wUserClock);

	return;
}

//时钟标识
uint CClientKernel::GetClockID()
{
	return m_wClockID;
}

//时钟位置
word CClientKernel::GetClockChairID()
{
	return m_wClockChairID;
}

//删除时钟
void CClientKernel::KillGameClock(word wClockID)
{
	//效验状态
	ASSERT(mIClientKernelSink!=NULL);

	//逻辑处理
	if ((m_wClockID!=0)&&((m_wClockID==wClockID)||(wClockID==0)))
	{
		//设置界面
		mTimerEngine.StopTimer(m_wClockID);

		//事件通知
		if (m_wClockChairID!=INVALID_CHAIR)
		{
			ASSERT(m_wClockChairID<mGameAttribute.wChairCount);
			//删除用户时间
			if (m_wClockChairID!=INVALID_CHAIR)
			{
				SetUserClock(m_wClockChairID,0L);
			}
			else
			{
				SetUserClock(INVALID_CHAIR,0L);
			}

			if (mIClientKernelSink!=NULL) mIClientKernelSink->OnEventGameClockKill(m_wClockChairID);
		}

		//设置变量
		m_wClockID=0L;
		m_nElapseCount=0L;
		m_wClockChairID=INVALID_CHAIR;
	}

	return;
}

//设置时钟
void CClientKernel::SetGameClock(word wChairID, word wClockID, uint nElapse)
{
	//效验参数
	ASSERT(mIClientKernelSink!=NULL);

	//删除时间
	if (m_wClockID!=0L) KillGameClock(m_wClockID);

	//设置时间
	if ((wChairID<mGameAttribute.wChairCount)&&(nElapse>0L))
	{
		//设置变量
		m_wClockID=wClockID;
		m_nElapseCount=nElapse;
		m_wClockChairID=wChairID;

		//设置时间
		mTimerEngine.StartTimer(m_wClockID);
		//设置用户时间
		SetUserClock(m_wClockChairID, m_nElapseCount);
		//事件通知
		if (mIClientKernelSink!=NULL)
		{
			mIClientKernelSink->OnEventGameClockInfo(m_wClockChairID, m_nElapseCount, m_wClockID);
		}
	}

	return;
}

void CClientKernel::OnTimerEngineTick(word id)
{
	//效验参数
	ASSERT(mIClientKernelSink != NULL);

	//时间处理
	if ((m_wClockID==id)&&(m_wClockChairID!=INVALID_CHAIR))
	{
		//事件处理
		if (m_nElapseCount>0) m_nElapseCount--;
		//设置用户时间
		SetUserClock(m_wClockChairID,m_nElapseCount);
		bool bSuccess=mIClientKernelSink->OnEventGameClockInfo(m_wClockChairID,m_nElapseCount,m_wClockID);

		//删除处理
		if ((m_nElapseCount==0)||(bSuccess==false)) KillGameClock(m_wClockID);

		return;
	}
}

//////////////////////////////////////////////////////////////////////////
//辅助接口
//切换椅子
word CClientKernel::SwitchViewChairID(word wChairID)
{
	//return wChairID;
	//参数判断
	if (wChairID==INVALID_CHAIR) return INVALID_CHAIR;
	if (mUserAttribute.dwUserID==0L) return INVALID_CHAIR;

	//转换椅子
	word wChairCount=mGameAttribute.wChairCount;
	word wViewChairID=(wChairID+wChairCount*3/2-mUserAttribute.wChairID)%wChairCount;

	return wViewChairID;
}

//////////////////////////////////////////////////////////////////////////
// IUserManagerSink
//////////////////////////////////////////////////////////////////////////
void CClientKernel::OnUserItemAcitve(IClientUserItem* pIClientUserItem)
{
	PLAZZ_PRINTF(("flow->CClientKernel::OnUserItemAcitve 用户激活 "));

	if (pIClientUserItem == 0) 
		return;
	if (mMeUserItem == 0 && mUserAttribute.dwUserID == pIClientUserItem->GetUserID()) 
	{
		mMeUserItem = pIClientUserItem;
		if (mIClientKernelSink)
			mIClientKernelSink->OnGFWaitTips(false);
	}

	if (mIClientKernelSink)
		mIClientKernelSink->OnEventUserEnter(pIClientUserItem, pIClientUserItem->GetUserStatus() == US_LOOKON);
}

void CClientKernel::OnUserItemDelete(IClientUserItem* pIClientUserItem)
{
	MELOG(MELOG_INFO, "flow->CClientKernel::OnUserItemDelete ...\n");

	if (pIClientUserItem == 0) 
		return;

	if (mIClientKernelSink)
		mIClientKernelSink->OnEventUserLeave(pIClientUserItem, pIClientUserItem->GetUserStatus() == US_LOOKON);
}


//用户更新
void CClientKernel::OnUserFaceUpdate(IClientUserItem* pIClientUserItem)
{
	PLAZZ_PRINTF(("flow->CClientKernel::OnUserFaceUpdate 用户头像更新"));

	if (pIClientUserItem == 0) 
		return;

	if (mIClientKernelSink)
		mIClientKernelSink->OnEventCustomFace(pIClientUserItem, pIClientUserItem->GetUserStatus() == US_LOOKON);

	return;
}

void CClientKernel::OnUserItemUpdate(IClientUserItem* pIClientUserItem, const tagUserScore& LastUserScore)
{
	PLAZZ_PRINTF(("flow->CClientKernel::OnUserItemUpdate 用户分数更新 "));

	if (pIClientUserItem == 0) 
		return;

	if (mIClientKernelSink)
		mIClientKernelSink->OnEventUserScore(pIClientUserItem, pIClientUserItem->GetUserStatus() == US_LOOKON);
}

void CClientKernel::OnUserItemUpdate(IClientUserItem* pIClientUserItem, const tagUserStatus& LastUserStatus)
{
	PLAZZ_PRINTF(("flow->CClientKernel::OnUserItemUpdate 用户状态更新 "));

	if (pIClientUserItem == 0) 
		return;

	if (mIClientKernelSink)
		mIClientKernelSink->OnEventUserStatus(pIClientUserItem, pIClientUserItem->GetUserStatus() == US_LOOKON);
}


//用户更新
void CClientKernel::OnUserItemUpdate(IClientUserItem* pIClientUserItem, const tagUserAttrib & UserAttrib)
{
	PLAZZ_PRINTF(("flow->CClientKernel::OnUserItemUpdate 用户属性更新 "));

	if (pIClientUserItem == 0) 
		return;

	if (mIClientKernelSink)
		mIClientKernelSink->OnEventUserAttrib(pIClientUserItem, pIClientUserItem->GetUserStatus() == US_LOOKON);
	return;
}

void CClientKernel::OnUserCustomTableUpdate(IClientUserItem* pIClientUserItem)
{
	PLAZZ_PRINTF(("flow->CClientKernel::OnUserCustomTableUpdate 用户自定义桌子更新 "));

	if (pIClientUserItem == 0)
		return;

	if (mIClientKernelSink)
		mIClientKernelSink->OnEventCustomTable(pIClientUserItem, pIClientUserItem->GetUserStatus() == US_LOOKON);
	return;
}
