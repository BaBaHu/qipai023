#include "CoChairView.h"
#include "MTNotification.h"
#include "../kernel/user/IClientUserItem.h"
#include "MECallBackListenerHelper.h"

USING_NS_CC;
USING_NS_CC_EXT;

//////////////////////////////////////////////////////////////////////////
CoChairView::CoChairView()
{
	mChairSprite = nullptr;
}

CoChairView::~CoChairView()
{
}

CoChairView * CoChairView::create(int nChair)
{
	CoChairView * ret = new (std::nothrow) CoChairView();
	if (ret && ret->init(nChair))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool CoChairView::init(int nChair)
{
	do 
	{
		mTableData = 0;
		mChair = INVALID_CHAIR;
		CC_BREAK_IF(!Node::init());
		char buf[126] = { 0 };
		sprintf(buf, "chair%d.png", nChair);
		mCoChairView = ui::Button::create(buf, buf, buf, ui::Widget::TextureResType::PLIST);
		mCoChairView->addTouchEventListener(CC_CALLBACK_2(CoChairView::onChairClick, this));
		addChild(mCoChairView);

		mLbId = LabelEx::create("0", "Arial", 35);
		mLbId->setColor(Color3B(0, 255, 255));
		mLbId->setPosition(Point(0,-70));
		addChild(mLbId);
		mLbId->setString("");
		return true;
	} while (0);

	return false;
}

void CoChairView::setData(ITable* table, word wChair)
{
	mTableData = table;
	mChair = wChair;
	if (table->GetClientUserItem(wChair) != 0)
	{
		mLbId->setString(table->GetClientUserItem(wChair)->GetNickName());

		if (mTableData != 0 && mChair != INVALID_CHAIR)
		{
			if (mTableData->GetClientUserItem(mChair) != 0)
			{
				if (table->GetClientUserItem(wChair)->GetUserType() == 0)
				{
					int index = table->GetClientUserItem(wChair)->GetFaceID() % 20 + 1;
					char buf[126] = { 0 };
					sprintf(buf, "s_%d.png", index);
					if (!mChairSprite)
					{
						mChairSprite = Sprite::createWithSpriteFrameName(buf);
						Size size = mCoChairView->getContentSize();
						mChairSprite->setPosition(Point(size.width / 2, size.height / 2));
						mCoChairView->addChild(mChairSprite);
					}
				}
				else
				{
					if (!mChairSprite)
					{
						mChairSprite = Sprite::createWithSpriteFrameName("usericon.png");
						Size size = mCoChairView->getContentSize();
						mChairSprite->setPosition(Point(size.width / 2, size.height / 2));
						mChairSprite->setContentSize(Size(138, 138));
						mCoChairView->addChild(mChairSprite);
					}

					int ret = 0;
					do
					{
						LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onUserIconBack");
						CC_BREAK_IF(0 == nLuaHandler);
						LuaEngine* pEngine = LuaEngine::getInstance();
						LuaStack* pStack = pEngine->getLuaStack();
						lua_State *tolua_s = pStack->getLuaState();
						lua_settop(tolua_s, 0);
						pStack->pushInt(table->GetTableID() );
						pStack->pushInt(wChair);
						pStack->pushString( table->GetClientUserItem(wChair)->GetIconUrl() );
						ret = pStack->executeFunctionByHandler(nLuaHandler, 3);
					} while (0);
				}
			}
		}
	}
	else
	{
		mLbId->setString("");
		if (mChairSprite)
		{
			mChairSprite->removeFromParent();
			mChairSprite = nullptr;
		}
	}
}

void  CoChairView::setChairIcon(const char* icon)
{
	if (mChairSprite)
	{
		mChairSprite->removeFromParent();
		mChairSprite = nullptr;
	}
	if (strcmp(icon, "") == 0)
		mChairSprite = Sprite::createWithSpriteFrameName("s_1.png");
	else
		mChairSprite = Sprite::create(icon);

	Size size = mCoChairView->getContentSize();
	mChairSprite->setPosition(Point(size.width / 2, size.height / 2));

	Size s = mChairSprite->getContentSize();
	float nScale = 138.0 / s.width;
	mChairSprite->setScale(nScale);
	mCoChairView->addChild(mChairSprite);
}

void CoChairView::onChairClick(Ref *pSender, ui::Widget::TouchEventType type)
{
	ui::Button* butten = (ui::Button*)pSender;
	unsigned int tag = butten->getTag();
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	case ui::Widget::TouchEventType::ENDED:
	{
		onChair();
		break;
	}
	case ui::Widget::TouchEventType::CANCELED:
		break;
	}
}

void CoChairView::onChair()
{
	//TODO
	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onSitDownClickBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushInt(mTableData->GetTableID());
		pStack->pushInt(mChair);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 2);
	} while (0);

	G_NOTIFY("CHAIR_SIT_DOWN", MTData::create(mTableData->GetTableID(), mChair));
}