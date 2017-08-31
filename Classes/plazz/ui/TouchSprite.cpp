#include "TouchSprite.h"
#include "MTNotification.h"

//////////////////////////////////////////////////////////////////////////

Sprite* TouchSprite::createWithTexture(Texture2D *pTexture)
{
	TouchSprite *pobSprite = new TouchSprite();
	if (pobSprite && pobSprite->initWithTexture(pTexture))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

Sprite* TouchSprite::createWithTexture(Texture2D *pTexture, const Rect& rect)
{
	TouchSprite *pobSprite = new TouchSprite();
	if (pobSprite && pobSprite->initWithTexture(pTexture, rect))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

Sprite* TouchSprite::create(const char *pszFileName)
{
	TouchSprite *pobSprite = new TouchSprite();
	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

Sprite* TouchSprite::create(const char *pszFileName, const Rect& rect)
{
	TouchSprite *pobSprite = new TouchSprite();
	if (pobSprite && pobSprite->initWithFile(pszFileName, rect))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

Sprite* TouchSprite::createWithSpriteFrame(SpriteFrame *pSpriteFrame)
{
	TouchSprite *pobSprite = new TouchSprite();
	if (pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

Sprite* TouchSprite::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
	SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(pszSpriteFrameName);
#if COCOS2D_DEBUG > 0
	char msg[256] = {0};
	sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
	CCAssert(pFrame != NULL, msg);
#endif

	return createWithSpriteFrame(pFrame);
}

Sprite* TouchSprite::create()
{
	TouchSprite *pSprite = new TouchSprite();
	if (pSprite && pSprite->init())
	{
		pSprite->autorelease();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
TouchSprite::TouchSprite()
{
	mTarget = 0;
	mCallFunc = 0;
	mIsEnable = true;
	mIsZoom = false;
	mTouchListener = 0;
	mIsSwallow = true;
}

TouchSprite::~TouchSprite()
{
	_eventDispatcher->removeEventListener(mTouchListener);
}
bool TouchSprite::init(void)
{
	return Sprite::init();
}

bool TouchSprite::initWithTexture(Texture2D *texture)
{
	return Sprite::initWithTexture(texture);
}

bool TouchSprite::initWithTexture(Texture2D *texture, const Rect& rect)
{
	return Sprite::initWithTexture(texture, rect);
}

bool TouchSprite::initWithTexture(Texture2D *texture, const Rect& rect, bool rotated)
{
	return Sprite::initWithTexture(texture, rect, rotated);
}

bool TouchSprite::initWithSpriteFrame(SpriteFrame *pSpriteFrame)
{
	return Sprite::initWithSpriteFrame(pSpriteFrame);
}

bool TouchSprite::initWithSpriteFrameName(const std::string& spriteFrameName)
{
	return Sprite::initWithSpriteFrameName(spriteFrameName);
}

bool TouchSprite::initWithFile(const std::string& filename)
{
	return Sprite::initWithFile(filename);
}

bool TouchSprite::initWithFile(const std::string& filename, const Rect& rect)
{
	return Sprite::initWithFile(filename, rect);
}

void TouchSprite::setTouchZoom(bool isZoom)
{
	mIsZoom = isZoom;
}

void TouchSprite::setEnable(bool isEnable)
{
	mIsEnable = isEnable;
}


void TouchSprite::setSwallow(bool isSwallow)
{
	mIsSwallow = isSwallow;
	if (mTouchListener)
		mTouchListener->setSwallowTouches(mIsSwallow);
}

void TouchSprite::setClickCallback(Ref* target, SEL_CallFuncN callback)
{
	mTarget = target;
	mCallFunc = callback;
}

void TouchSprite::onEnterTransitionDidFinish()
{
	Sprite::onEnterTransitionDidFinish();

	if (mTouchListener == 0)
	{
		mTouchListener = EventListenerTouchOneByOne::create();//创建一个触摸监听

		mTouchListener->onTouchBegan = [&](Touch* touch, Event* event) {
			if (!isVisible() || !mIsEnable)
				return false;

			mIsTouch = isTouchInside(touch);

			if (mIsTouch)
				mPtTouch = touch->getLocation();

			return mIsTouch;
		};

		mTouchListener->onTouchMoved = [&](Touch* touch, Event* event){};

		mTouchListener->onTouchEnded = [&](Touch* touch, Event* event){
			if (mIsTouch)
			{
				mPtTouch = touch->getLocation() - mPtTouch;
				//log("end %.1f, %.1f %f", mPtTouch.x, mPtTouch.y, mPtTouch.getLengthSq());

				if (mPtTouch.getLengthSq() < 100)
				{
					if (mIsZoom)
					{
						this->runAction(Sequence::create(
							ScaleTo::create(0.05f, 1.1f),
							ScaleTo::create(0.01f, 1),
							nullptr));
					}

					if (mCallFunc && mTarget)
						(mTarget->*mCallFunc)(this);
				}
			}

			mIsTouch = false;
		};

		mTouchListener->setSwallowTouches(mIsSwallow);

		_eventDispatcher->addEventListenerWithSceneGraphPriority(mTouchListener ,this);
	}

}

void TouchSprite::onExit()
{
	Sprite::onExit();
}

bool TouchSprite::isTouchInside(Touch *pTouch)
{
	Point sLocalPos = convertToNodeSpace(pTouch->getLocation());  
	Rect sRC = Rect(
		getPositionX() - getContentSize().width * getAnchorPoint().x,  
		getPositionY() - getContentSize().height * getAnchorPoint().y,  
		getContentSize().width, 
		getContentSize().height);  


	sRC.origin = Point(0,0);  
	return sRC.containsPoint(sLocalPos);  
}