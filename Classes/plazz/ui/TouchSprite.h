#ifndef _TouchSprite_H_
#define _TouchSprite_H_

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;

class TouchSprite : public Sprite
{
public:
	 /**
     * Creates an empty sprite without texture. You can call setTexture method subsequently.
     *
     * @return An empty sprite object that is marked as autoreleased.
     */
    static Sprite* create();
    
    /**
     * Creates a sprite with an image filename.
     *
     * After creation, the rect of sprite will be the size of the image,
     * and the offset will be (0,0).
     *
     * @param   pszFileName The string which indicates a path to image file, e.g., "scene1/monster.png".
     * @return  A valid sprite object that is marked as autoreleased.
     */
    static Sprite* create(const char *pszFileName);
    
    /**
     * Creates a sprite with an image filename and a rect.
     *
     * @param   pszFileName The string wich indicates a path to image file, e.g., "scene1/monster.png"
     * @param   rect        Only the contents inside rect of pszFileName's texture will be applied for this sprite.
     * @return  A valid sprite object that is marked as autoreleased.
     */
    static Sprite* create(const char *pszFileName, const Rect& rect);
    
    /**
     * Creates a sprite with an exsiting texture contained in a Texture2D object
     * After creation, the rect will be the size of the texture, and the offset will be (0,0).
     *
     * @param   pTexture    A pointer to a Texture2D object.
     * @return  A valid sprite object that is marked as autoreleased.
     */
    static Sprite* createWithTexture(Texture2D *pTexture);
    
    /**
     * Creates a sprite with a texture and a rect.
     *
     * After creation, the offset will be (0,0).
     *
     * @param   pTexture    A pointer to an existing Texture2D object.
     *                      You can use a Texture2D object for many sprites.
     * @param   rect        Only the contents inside the rect of this texture will be applied for this sprite.
     * @return  A valid sprite object that is marked as autoreleased.
     */
    static Sprite* createWithTexture(Texture2D *pTexture, const Rect& rect);
    
    /**
     * Creates a sprite with an sprite frame.
     *
     * @param   pSpriteFrame    A sprite frame which involves a texture and a rect
     * @return  A valid sprite object that is marked as autoreleased.
     */
    static Sprite* createWithSpriteFrame(SpriteFrame *pSpriteFrame);
    
    /**
     * Creates a sprite with an sprite frame name.
     *
     * A SpriteFrame will be fetched from the SpriteFrameCache by pszSpriteFrameName param.
     * If the SpriteFrame doesn't exist it will raise an exception.
     *
     * @param   pszSpriteFrameName A null terminated string which indicates the sprite frame name.
     * @return  A valid sprite object that is marked as autoreleased.
     */
    static Sprite* createWithSpriteFrameName(const char *pszSpriteFrameName);
    
    /// @}  end of creators group
protected:
	TouchSprite();
	~TouchSprite();
	virtual bool init(void);
	virtual bool initWithTexture(Texture2D *texture);
	virtual bool initWithTexture(Texture2D *texture, const Rect& rect);
	virtual bool initWithTexture(Texture2D *texture, const Rect& rect, bool rotated);
	virtual bool initWithSpriteFrame(SpriteFrame *pSpriteFrame);
	virtual bool initWithSpriteFrameName(const std::string& spriteFrameName);
	virtual bool initWithFile(const std::string& filename);
	virtual bool initWithFile(const std::string& filename, const Rect& rect);

public:

	void setTouchZoom(bool isZoom);
	void setEnable(bool isEnable);
	void setSwallow(bool isSwallow);
	void setClickCallback(Ref* target, SEL_CallFuncN callback);
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
private:
	bool isTouchInside(Touch *pTouch);
private:
	bool		mIsTouch;
	Point		mPtTouch;
	bool		mIsZoom;
	bool		mIsEnable;
	bool		mIsSwallow;
	Ref*		mTarget;
	SEL_CallFuncN	mCallFunc;
	EventListenerTouchOneByOne* mTouchListener;
};

#endif // _TouchSprite_H_