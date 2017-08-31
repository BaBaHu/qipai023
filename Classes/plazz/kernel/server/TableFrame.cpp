#include "../../Plazz.h"
#include "TableFrame.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CTable::CTable()
{
	//组件接口
	mITableFrame=0;
	mITableListener=0;

	//桌子标志
	mIsLocker		= false;
	mIsPlaying		= false;
	mIsFocusFrame	= false;

	//桌子状态
	mWatchCount		= 0;
	mTableOwnerID	= 0;

	//属性变量
	mTableID		= 0;
	mChairCount		= 0;
	
	zeromemory(mIClientUserItem, sizeof(mIClientUserItem));
	return;
}

//析构函数
CTable::~CTable()
{
}

//空椅子数
word CTable::GetNullChairCount(word & wNullChairID)
{
	//设置变量
	wNullChairID=INVALID_CHAIR;

	//寻找位置
	word wNullCount=0;
	for (word i=0;i<mChairCount;i++)
	{
		if (mIClientUserItem[i]==0)
		{
			//设置数目
			wNullCount++;

			//设置结果
			if (wNullChairID==INVALID_CHAIR) wNullChairID=i;
		}
	}

	return wNullCount;
}

//配置函数
void CTable::InitTable(word wTableID, word wChairCount, ITableFrame * pITableFrame)
{
	//设置属性
	mTableID=wTableID;
	mChairCount=wChairCount;

	//设置接口
	mITableFrame=pITableFrame;
	return;
}

//设置结果
void CTable::SetTableListener(ITableListener* listener)
{
	mITableListener = listener;
}

//获取用户
IClientUserItem * CTable::GetClientUserItem(word wChairID)
{
	//效验参数
	ASSERT(wChairID<mChairCount);
	if (wChairID>=mChairCount) return 0;

	//获取用户
	return mIClientUserItem[wChairID];
}

//设置信息
bool CTable::SetClientUserItem(word wChairID, IClientUserItem * pIClientUserItem)
{
	//效验参数
	ASSERT(wChairID<mChairCount);
	if (wChairID>=mChairCount) return false;

	//设置用户
	mIClientUserItem[wChairID]=pIClientUserItem;

	// 桌子界面
	if (mITableListener)
		mITableListener->TableClientUserItem(wChairID, mIClientUserItem[wChairID]);

	//更新界面
	mITableFrame->UpdateTable(mTableID);
	return true;
}

//桌子状态 
void CTable::SetTableStatus(bool bPlaying, bool bLocker)
{
	//设置标志
	if ((mIsLocker!=bLocker)||(mIsPlaying!=bPlaying))
	{
		//设置变量
		mIsLocker=bLocker; 
		mIsPlaying=bPlaying;

		// 桌子界面
		if (mITableListener)
			mITableListener->TableTableStatus(mIsPlaying, mIsLocker);

		//更新界面
		mITableFrame->UpdateTable(mTableID);
	}

	return;
}

//焦点框架
void CTable::SetFocusFrame(bool bFocusFrame)
{
	//设置标志
	if (mIsFocusFrame!=bFocusFrame)
	{
		//设置变量
		mIsFocusFrame=bFocusFrame;

		//更新界面
		mITableFrame->UpdateTable(mTableID);
	}

	return;
}
//////////////////////////////////////////////////////////////////////////////////

//构造函数
CTableFrame::CTableFrame()
{
	//属性变量
	mTableCount=0;
	mChairCount=0;
	mServerRule=0;
	mServerType=0;

	//比赛变量
	mMatchTotalUser=0;
	mMatchWaittingCount=0;
	mMatchStatus=MS_NULL;
	return;
}

//析构函数
CTableFrame::~CTableFrame()
{
	//删除桌子
	for (int i=0, l = (int)mTableArray.size(); i<l ;i++)
	{
		CTable * pTable=mTableArray[i];
		if (pTable!=0) 
			SafeDelete(pTable);
	}

	//删除数组
	mTableArray.clear();

	return;
}


//配置函数
bool CTableFrame::ConfigTableFrame(word wTableCount, word wChairCount, dword dwServerRule, word wServerType, word wServerID)
{
	//效验参数
	ASSERT(wChairCount<=MAX_CHAIR);
	
	//设置变量
	mTableCount=wTableCount;
	mChairCount=wChairCount;
	mServerRule=dwServerRule;
	mServerType=wServerType;
	mTableArray.resize(mTableCount);
	zeromemory(&mTableArray[0],mTableCount*sizeof(CTable *));

	//创建桌子
	for (word i=0;i<mTableCount;i++)
	{
		mTableArray[i]=new CTable;
		mTableArray[i]->InitTable(i,wChairCount,this);
	}


	return true;
}

//获取用户
IClientUserItem * CTableFrame::GetClientUserItem(word wTableID, word wChairID)
{
	//获取桌子
	ASSERT(GetTableItem(wTableID)!=0);
	ITable * pITable=GetTableItem(wTableID);

	//获取用户
	if (pITable!=0)
	{
		return pITable->GetClientUserItem(wChairID);
	}

	return 0;
}

//设置信息
bool CTableFrame::SetClientUserItem(word wTableID, word wChairID, IClientUserItem * pIClientUserItem)
{
	ITable * pITable=GetTableItem(wTableID);
	if (pITable!=0) pITable->SetClientUserItem(wChairID,pIClientUserItem);
	return true;
}

//游戏标志
bool CTableFrame::GetPlayFlag(word wTableID)
{
	//获取桌子
	ASSERT(GetTableItem(wTableID)!=0);
	ITable * pITable=GetTableItem(wTableID);

	//获取标志
	if (pITable!=0)
	{
		return pITable->GetPlayFlag();
	}

	return false;
}

//密码标志
bool CTableFrame::GetLockerFlag(word wTableID)
{
	//获取桌子
	ASSERT(GetTableItem(wTableID)!=0);
	ITable * pITable=GetTableItem(wTableID);

	//获取标志
	if (pITable!=0)
	{
		return pITable->GetLockerFlag();
	}

	return false;
}

//焦点框架
void CTableFrame::SetFocusFrame(word wTableID, bool bFocusFrame)
{
	//获取桌子
	ASSERT(GetTableItem(wTableID)!=0);
	ITable * pITable=GetTableItem(wTableID);

	//设置标志
	if (pITable!=0) pITable->SetFocusFrame(bFocusFrame);

	return;
}


//桌子状态 
void CTableFrame::SetTableStatus(word wTableID, bool bPlaying, bool bLocker)
{
	//获取桌子
	ASSERT(GetTableItem(wTableID)!=0);
	ITable * pITable=GetTableItem(wTableID);

	//设置标志
	if (pITable!=0) pITable->SetTableStatus(bPlaying,bLocker);

	return;
}

//桌子状态 
void CTableFrame::SetTableStatus(bool bWaitDistribute)
{
	//m_bWaitDistribute=bWaitDistribute;
	return;
}

//桌子可视
bool CTableFrame::VisibleTable(word wTableID)
{
	//效验参数
	ASSERT(wTableID<mTableCount);
	if (wTableID>=mTableCount) return false;

	return true;
}

//闪动桌子
bool CTableFrame::FlashGameTable(word wTableID)
{
	//获取桌子
	ITable * pITable=GetTableItem(wTableID);

	//错误判断
	if (pITable==0)
	{
		ASSERT(FALSE);
		return false;
	}


	return true;
}

//闪动椅子
bool CTableFrame::FlashGameChair(word wTableID, word wChairID)
{
	//获取桌子
	ITable * pITable=GetTableItem(wTableID);

	//错误判断
	if (pITable==0)
	{
		ASSERT(FALSE);
		return false;
	}

	return true;
}

//更新桌子
bool CTableFrame::UpdateTable(word wTableID)
{
	//获取桌子
	ITable * pITable=GetTableItem(wTableID);
	if (pITable==0) return false;

	
	return true;
}

//获取桌子
ITable * CTableFrame::GetTableItem(word wTableID)
{
	//获取桌子
	if (wTableID!=INVALID_TABLE)
	{
		//效验参数
		ASSERT(wTableID<(int)mTableArray.size());
		if (wTableID>=(int)mTableArray.size()) 
			return 0;

		//获取桌子
		ITable * pITable=mTableArray[wTableID];

		return pITable;
	}

	return 0;
}

//空椅子数
word CTableFrame::GetNullChairCount(word wTableID, word & wNullChairID)
{
	//获取桌子
	ASSERT(GetTableItem(wTableID)!=0);
	ITable * pITable=GetTableItem(wTableID);

	//获取状态
	if (pITable!=0)
	{
		return pITable->GetNullChairCount(wNullChairID);
	}

	return 0;
}

//比赛状态
void CTableFrame::SetMatchStatus(byte cbMatchStatus)
{
	mMatchStatus=cbMatchStatus;
	//if(cbMatchStatus==MS_MATCHING)
	//{
	//	m_tStartTime=CTime::GetCurrentTime();
	//	SetTimer(IDI_TICK_TIMER,1000, 0);
	//	InvalidateRect(0);
	//}
	//else
	//{
	//	KillTimer(IDI_TICK_TIMER);
	//}
}

//////////////////////////////////////////////////////////////////////////////////
