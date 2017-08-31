#include "CoTableView.h"
#include "MTNotification.h"
#include "CoChairView.h"
#include "../Plazz.h"
USING_NS_CC;
USING_NS_CC_EXT;

//////////////////////////////////////////////////////////////////////////
CoTableView::CoTableView()
{
	mMapChairReadySprite.clear();
}

CoTableView::~CoTableView()
{
	setTableData(0);
}

//初始化方法
bool CoTableView::init()
{
	do 
	{
		mTableData = 0;
		CC_BREAK_IF(!Node::init());
		mTable = Sprite::createWithSpriteFrameName("table1.png");
		mTable->setPosition(Point(0,0));
		setContentSize(mTable->getContentSize());
		addChild(mTable);

		mLbTableNumber = Label::createWithBMFont("res/fonts/fnt_14.fnt", "0");
		int nKind = DF::shared()->GetGameKindID();
		if (nKind == 351)
		{
			mLbTableNumber->setPosition(Point(0, -mTable->getContentSize().height + 0));
		}
		else if (nKind == 301 || nKind == 302 || nKind == 350)
		{
			mLbTableNumber->setPosition(Point(0, -mTable->getContentSize().height - 180));
		}
		addChild(mLbTableNumber,5);
		return true;
	} while (0);

	return false;
}

void CoTableView::setTableData(ITable* tableData)
{
	if (mTableData)
		mTableData->SetTableListener(0);
	mTableData = tableData;
	if (mTableData)
	{
		mLbTableNumber->setString(toString(mTableData->GetTableID()+1));

		// 创建椅子
		if (mCoChairViews.empty())
		{
			Point chairPos[4];
			chairPos[0].x = -160;
			chairPos[0].y = 0;
			chairPos[1].x = 160;
			chairPos[1].y = 0;
			chairPos[2].x = 0;
			chairPos[2].y = 160;
			chairPos[3].x = 0;
			chairPos[3].y = -160;
			for (word i = 0; i<DF::shared()->GetGamePlayer(); i++)
			{
				CoChairView* chairView = CoChairView::create(i);
				chairView->setTag(i);
				chairView->setPosition(Point(chairPos[i].x, chairPos[i].y));
				chairView->setData(mTableData, i);
				mCoChairViews.push_back(chairView);
				addChild(chairView);
				updateUsersTableState(mTableData, i);
			}
		}
		else
		{
			for (unsigned int i = 0; i < mCoChairViews.size(); ++i)
			{
				CoChairView* chairView = mCoChairViews[i];
				chairView->setData(mTableData, i);
				updateUsersTableState(mTableData, i);
			}
		}
		// 设置桌子状态
		TableTableStatus(mTableData->GetPlayFlag(), mTableData->GetLockerFlag());
		// 设置监听
		mTableData->SetTableListener(this);
	}
}

ITable* CoTableView::getTableData()
{
	return mTableData;
}

//////////////////////////////////////////////////////////////////////////
// ITableListener
void CoTableView::TableClientUserItem(word wChairID, IClientUserItem* pIClientUserItem)
{
	if (mCoChairViews.size() > wChairID)
	{
		mCoChairViews[wChairID]->setData(mTableData, wChairID);
		updateUsersTableState(mTableData, wChairID);
	}
}

void CoTableView::TableTableStatus(bool bPlaying, bool bLocker)
{
	char buf[126]={0};
	sprintf(buf, "table%d.png", bPlaying ? 2 : 1);
	mTable->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(buf));

	if (bPlaying)
	{
		for (unsigned int i = 0; i < mCoChairViews.size(); ++i)
		{
			Sprite*	readySprite = nullptr;
			if (mMapChairReadySprite.find(i) != mMapChairReadySprite.end())
			{
				readySprite = mMapChairReadySprite[i];
			}
			if (readySprite)
			{
				readySprite->removeFromParent();
				readySprite = nullptr;
			}
		}
		mMapChairReadySprite.clear();
	}
}

void CoTableView::updateUsersTableState(ITable* table, word wChair)
{
	Sprite*	readySprite = nullptr;
	if (mMapChairReadySprite.find(wChair) != mMapChairReadySprite.end())
	{
		readySprite = mMapChairReadySprite[wChair];
	}

	if (table->GetClientUserItem(wChair) != 0)
	{
		byte cbUserStatus = table->GetClientUserItem(wChair)->GetUserStatus();
		if (cbUserStatus == US_READY)
		{
			Size size = getContentSize();
			if (!readySprite)
			{
				readySprite = Sprite::createWithSpriteFrameName("UserReady.png");
				if (wChair == 0)
				{
					readySprite->setPosition(Point(-size.width/2 + 20, 20));
				}
				else if (wChair == 1)
				{
					readySprite->setPosition(Point(size.width/2 - 20, 20));
				}
				else if (wChair == 2)
				{
					readySprite->setPosition(Point(0, size.height/2 - 20));
				}
				else if (wChair == 3)
				{
					readySprite->setPosition(Point(0, -size.height/2 + 20));
				}

				addChild(readySprite, 100);
				mMapChairReadySprite[wChair] = readySprite;
			}
			return;
		}
	}

	if (mMapChairReadySprite.find(wChair) != mMapChairReadySprite.end())
	{
		mMapChairReadySprite.erase(wChair);
	}
	if (readySprite)
	{
		readySprite->removeFromParent();
		readySprite = nullptr;
	}
}

void CoTableView::setChairIcon(int nChair, const char* icon)
{
	if (mCoChairViews[nChair])
	{
		mCoChairViews[nChair]->setChairIcon(icon);
	}
}