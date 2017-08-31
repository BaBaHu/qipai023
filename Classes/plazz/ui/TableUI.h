#ifndef _TableUI_H_
#define _TableUI_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CoTableView.h"
USING_NS_CC;
USING_NS_CC_EXT;

class TableUI
	: public Layer
	, public TableViewDataSource
	, public TableViewDelegate
{
public:
	static TableUI* create(int width, int height, int x, int y);
	TableUI();
	~TableUI();

	void backToServerListScene();
	void setChairIcon(int nTable, int nChair, const char* icon);
	void setTableScrollOffset(int yOffset);
	void getTableScrollOffset();
public:
	void onEnter();
	void onExit();
	virtual void onEnterTransitionDidFinish();
private:
	bool init(int width, int height, int x, int y);
	void InsertTableView(CoTableView* view);
	//////////////////////////////////////////////////////////////////////////
	// TableViewDataSource
	//////////////////////////////////////////////////////////////////////////
public:
	virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
	virtual Size cellSizeForTable(TableView *table);
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(TableView *table);

	//////////////////////////////////////////////////////////////////////////
	// TableViewDelegate
	//////////////////////////////////////////////////////////////////////////
public:
	virtual void scrollViewDidScroll(ScrollView* view);
	virtual void scrollViewDidZoom(ScrollView* view);
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
	virtual void tableCellHighlight(TableView* table, TableViewCell* cell);
	virtual void tableCellUnhighlight(TableView* table, TableViewCell* cell);
	virtual void tableCellWillRecycle(TableView* table, TableViewCell* cell);

private:
	TableView*	mTableView;
	Size		mSize;
	Vec2		mPoint;
	Size		mCellSize;
	std::map<int, CoTableView*> mCoTableViews;
};

#endif // _TableUI_H_