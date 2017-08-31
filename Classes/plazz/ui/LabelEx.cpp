#include "LabelEx.h"


LabelEx* LabelEx::create(const std::string& text, const std::string& font, float fontSzie)
{
	LabelEx* view = new LabelEx();
	if (view && view->init(text, font, fontSzie))
	{
		view->autorelease();
		return view;
	}

	delete view;
	return 0;
}

LabelEx* LabelEx::create(const std::string& text, const std::string& font, float fontSzie, const Size& size, TextHAlignment hAlignment, TextVAlignment vAlignment)
{
	LabelEx* view = new LabelEx();
	if (view && view->init(text, font, fontSzie, size, hAlignment, vAlignment))
	{
		view->autorelease();
		return view;
	}

	delete view;
	return 0;
}


LabelEx::LabelEx()
{

}

LabelEx::~LabelEx()
{

}


bool LabelEx::init(const std::string& text, const std::string& font, float fontSzie)
{
	do 
	{
		CC_BREAK_IF(!Node::init());
#if ((CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID && CC_TARGET_PLATFORM != CC_PLATFORM_IOS))
		mROutLine = Label::createWithSystemFont(text, font, fontSzie);
		mROutLine->setPosition(Point(1, -1));
		mROutLine->setColor(Color3B(0, 0, 0));
		addChild(mROutLine);
#endif //

		mText = Label::createWithSystemFont(text, font, fontSzie);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		mText->enableOutline(Color4B(0, 0, 0, 255), 1);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		mText->enableOutline(Color4B(255, 255, 255, 255), 1);
#endif
		addChild(mText);
		setContentSize(mText->getContentSize());
		this->setCascadeOpacityEnabled(true);
		this->setCascadeColorEnabled(true);
		return true;
	} while (0);
	return false;
}

bool LabelEx::init(const std::string& text, const std::string& font, float fontSzie, const Size& size, TextHAlignment hAlignment, TextVAlignment vAlignment)
{
	do 
	{
		CC_BREAK_IF(!Node::init());
#if ((CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID && CC_TARGET_PLATFORM != CC_PLATFORM_IOS))
		mROutLine = Label::createWithSystemFont(text, font, fontSzie, size, hAlignment, vAlignment);
		mROutLine->setPosition(Point(1, -1));
		mROutLine->setColor(Color3B(0, 0, 0));
		addChild(mROutLine);
#endif //

		mText = Label::createWithSystemFont(text, font, fontSzie, size, hAlignment, vAlignment);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		mText->enableOutline(Color4B(0, 0, 0, 255), 1);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		mText->enableOutline(Color4B(255, 255, 255, 255), 1);
#endif
		addChild(mText);
		setContentSize(mText->getContentSize());
		this->setCascadeOpacityEnabled(true);
		this->setCascadeColorEnabled(true);
		return true;
	} while (0);
	return false;
}


void LabelEx::setString(const std::string& text)
{
#if ((CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID && CC_TARGET_PLATFORM != CC_PLATFORM_IOS))
	mROutLine->setString(text);
#endif //
	mText->setString(text);
	setContentSize(mText->getContentSize());
}

void LabelEx::setStrokeColor(const Color3B& col, float size)
{
#if ((CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID && CC_TARGET_PLATFORM != CC_PLATFORM_IOS))
	mROutLine->setColor(col);
#else
	mText->enableOutline(Color4B(col.r, col.g, col.b, 255), size);
#endif //
}

void LabelEx::setColor(const Color3B& col)
{
	mText->setColor(col);
}

void LabelEx::setAnchorPoint(const Point& anchorPoint)
{
	//Node::setAnchorPoint(anchorPoint);
	mText->setAnchorPoint(anchorPoint);
#if ((CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID && CC_TARGET_PLATFORM != CC_PLATFORM_IOS))
	mROutLine->setAnchorPoint(anchorPoint);
#endif //
}

const Point& LabelEx::getAnchorPoint()
{
	return mText->getAnchorPoint();
}
