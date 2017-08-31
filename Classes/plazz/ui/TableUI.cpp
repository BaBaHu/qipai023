#include "TableUI.h"
#include "MTNotification.h"

#include "../kernel/server/IServerItem.h"
#include "MELog.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define TAG_CHEAT			1
#define TAG_HUNDRED			2
#define TAG_BACK			3

TableUI::TableUI()
{
	mCoTableViews.clear();
}

TableUI::~TableUI()
{
	mCoTableViews.clear();
}

TableUI* TableUI::create(int width, int height, int x, int y)
{
	TableUI *pRet = new TableUI();
	if (pRet && pRet->init(width, height, x, y))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

//初始化方法
bool TableUI::init(int width, int height, int x, int y)
{
	log("TableUI::init: %d, %d, %d, %d", width, height, x, y);
	do 
	{
		CC_BREAK_IF(!Layer::init());
		mTableView = 0;
		mSize = Size(width, height);
		mPoint = Vec2(x, y);
		mCellSize = Size(width, height);
		setContentSize(mSize);
		dword dwServerRule = IServerItem::get()->GetServerAttribute().dwServerRule;
		if (CServerRule::IsAllowQuickMode(dwServerRule))
		{// 快速模式
			
		}
		else if (CServerRule::IsAllowAvertCheatMode(dwServerRule))
		{// 防作弊模式
 
		}
		else if (IServerItem::get()->GetTableFrame()->GetChairCount() == MAX_CHAIR)
		{// 百人模式

		}
		else
		{// 一般模式
			
			/*mTableView = TableView::create(this, mSize);
			mTableView->setDirection(TableView::Direction::VERTICAL);
			mTableView->setPosition(Point(x, y));
			mTableView->setDelegate(this);
			mTableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
			addChild(mTableView);*/
		}  
		return true;
	} while (0);

	return false;
}

void TableUI::onEnter()
{
	Layer::onEnter();
}

void TableUI::onExit()
{
	Layer::onExit();
}

void TableUI::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();

	mTableView = TableView::create(this, mSize);
	mTableView->setDirection(TableView::Direction::VERTICAL);
	mTableView->setPosition(mPoint);
	mTableView->setDelegate(this);
	mTableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	addChild(mTableView);

	//if (mTableView != 0)
	//	mTableView->reloadData();
}
//////////////////////////////////////////////////////////////////////////
// TableViewDataSource
//////////////////////////////////////////////////////////////////////////
Size TableUI::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return cellSizeForTable(table);
}

Size TableUI::cellSizeForTable(TableView *table)
{
	int nKind = DF::shared()->GetGameKindID();
	if (nKind == 351)
	{
		mCellSize =Size(mSize.width, mSize.height / 2);
	}
	else if (nKind == 301 || nKind == 302 || nKind == 350)
	{
		mCellSize =Size(mSize.width, mSize.height - 150);
	}
	return mCellSize;
}

TableViewCell* TableUI::tableCellAtIndex(TableView *table, ssize_t rowIdx)
{
	log("tableCellAtIndex rowIdx:%d", rowIdx);
	TableViewCell *pCell = table->dequeueCell();

	int y = 0;
	int nKind = DF::shared()->GetGameKindID();
	if (nKind == 351)
	{
		y = mSize.height / 3;
	}
	else if (nKind == 301 || nKind == 302 || nKind == 350)
	{
		y = mSize.height / 2;
	}
	if (!pCell) {  

		pCell = new TableViewCell();  
		pCell->autorelease();  

		CoTableView* view = CoTableView::create();
		view->setTag(1);
		view->setPosition(Point(mSize.width/2 - 4*view->getContentSize().width,y));
		pCell->addChild(view);

		CoTableView* view1 = CoTableView::create();
		view1->setTag(2);
		view1->setPosition(Point(mSize.width/2, y));
		pCell->addChild(view1);  

		CoTableView* view2 = CoTableView::create();
		view2->setTag(3);
		view2->setPosition(Point(mSize.width/2 + 4*view2->getContentSize().width, y));
		pCell->addChild(view2);
		
	}
	int tableCount = IServerItem::get()->GetTableFrame()->GetTableCount();
	ITable* tableData = IServerItem::get()->GetTableFrame()->GetTableItem(rowIdx * 3);
	CoTableView* view =(CoTableView*)pCell->getChildByTag(1);
	view->setTableData(tableData);
	InsertTableView(view);

	tableData = IServerItem::get()->GetTableFrame()->GetTableItem(rowIdx * 3 + 1);
	view =(CoTableView*)pCell->getChildByTag(2);
	view->setVisible(true);
	view->setTableData(tableData);
	InsertTableView(view);

	tableData = IServerItem::get()->GetTableFrame()->GetTableItem(rowIdx * 3 + 2);
	view = (CoTableView*)pCell->getChildByTag(3);
	view->setVisible(true);
	view->setTableData(tableData);
	InsertTableView(view);

	return pCell;   
}

void TableUI::InsertTableView(CoTableView* view)
{
	ITable* table = view->getTableData();
	if (table)
	{
		mCoTableViews[table->GetTableID()] = view;
	}
}

ssize_t TableUI::numberOfCellsInTableView(TableView *table)
{
	//log("table num:%d",IServerItem::get()->GetTableFrame()->GetTableCount());
	if(IServerItem::get()->GetTableFrame()->GetTableCount()%3==0)
		return IServerItem::get()->GetTableFrame()->GetTableCount()/3;
	return IServerItem::get()->GetTableFrame()->GetTableCount()/3+1;
}

void TableUI::setTableScrollOffset(int yOffset)
{
	if (mTableView)
	{
		mTableView->setContentOffset(Vec2(0, yOffset));
	}
}

void TableUI::getTableScrollOffset()
{

}

//////////////////////////////////////////////////////////////////////////
// TableViewDelegate
//////////////////////////////////////////////////////////////////////////
void TableUI::scrollViewDidScroll(ScrollView* view)
{
	//auto off = view->getContentOffset();
	//log("cur table scroll offset x = %f,  y = %f, %d, %d", off.x, off.y);
}

void TableUI::scrollViewDidZoom(ScrollView* view)
{
}

void TableUI::tableCellTouched(TableView* table, TableViewCell* cell)
{
	CCLOG("cell touched at index: %ld", cell->getIdx());
}

void TableUI::tableCellHighlight(TableView* table, TableViewCell* cell)
{
}

void TableUI::tableCellUnhighlight(TableView* table, TableViewCell* cell)
{
}

void TableUI::tableCellWillRecycle(TableView* table, TableViewCell* cell)
{
	CCLOG("tableCellWillRecycle: %ld", cell->getIdx());
}

void TableUI::backToServerListScene()
{
	IServerItem::get()->SendSocketData(MDM_GR_LOGON, SUB_GR_MOBILE_CLOSE);
	MELOG(MELOG_INFO, "TableUI::backToServerListScene .......................\n");
	G_NOTIFY("BACK_TO_SERVER_LIST", 0);
}

void TableUI::setChairIcon(int nTable, int nChair, const char* icon)
{
	std::map<int, CoTableView*>::iterator it = mCoTableViews.find(nTable);
	if (it != mCoTableViews.end() && it->second)
	{
		it->second->setChairIcon(nChair, icon);
	}
}