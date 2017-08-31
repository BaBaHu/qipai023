#ifndef _CoChairView_H_
#define _CoChairView_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../kernel/server/ITableFrame.h"
#include "LabelEx.h"
#include "ui/UIButton.h"

USING_NS_CC_EXT;
USING_NS_CC;

class CoChairView : public Node
{
public:
	static CoChairView * create( int nChair);
public:
	CoChairView();
	~CoChairView();
	
	void setData(ITable* table, word wChair);
	void setChairIcon(const char* icon);
private:
	void onChairClick(Ref *pSender, ui::Widget::TouchEventType type);
	void onChair();
	bool init(int nChair);
private:
	ui::Button*			mCoChairView;
	Sprite*				mChairSprite;
	LabelEx*			mLbId;
	ITable*				mTableData;
	word				mChair;
};

#endif // _CoChairView_H_