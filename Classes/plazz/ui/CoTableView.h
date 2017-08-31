#ifndef _CoTableView_H_
#define _CoTableView_H_

#include "../kernel/server/ITableFrame.h"
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;

class CoChairView;

class CoTableView
	: public Node
	, public ITableListener
{
public:
	CREATE_FUNC(CoTableView);

public:
	CoTableView();
	~CoTableView();
	bool init();

	void setTableData(ITable* tableData);
	ITable* getTableData();
	void setChairIcon(int nChair, const char* icon);
	void updateUsersTableState(ITable* table, word wChair);
private:
	void onBtnClick(Ref* obj, Control::EventType e);
	//////////////////////////////////////////////////////////////////////////
	// ITableListener
public:
	virtual void TableClientUserItem(word wChairID, IClientUserItem* pIClientUserItem);
	virtual void TableTableStatus(bool bPlaying, bool bLocker);

private:
	Sprite*		mTable;
	Label*		mLbTableNumber;
	ITable*		mTableData;
	std::map<int, Sprite*> mMapChairReadySprite;
	std::vector<CoChairView*> mCoChairViews;
};

#endif // _CoTableView_H_