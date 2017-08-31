#include "MEResolution.h"
#include "cocos2d.h"
#include "MELog.h"

USING_NS_CC;

int MEResolution::s_screenWidth = 1920;
int MEResolution::s_screenHeight= 1080;
int MEResolution::s_designWidth = 1920;
int MEResolution::s_designHeight= 1080;


void MEResolution::adjustResolution()
{ 
	auto glview = Director::getInstance()->getOpenGLView();
	if(!glview)
		return;
	//获取屏幕分辨率
	CCSize frameSize = glview->getFrameSize();
    CCSize lsSize = CCSizeMake(s_designWidth, s_designHeight);
    float scaleX = (float) frameSize.width / lsSize.width;
    float scaleY = (float) frameSize.height / lsSize.height;
    float scale = MAX(scaleX, scaleY);
    if(scaleX < scaleY)
    	 glview->setDesignResolutionSize(lsSize.width, lsSize.height, kResolutionFixedWidth);
    else
		 glview->setDesignResolutionSize(lsSize.width, lsSize.height, kResolutionFixedHeight);

	CCSize winSize = Director::getInstance()->getWinSize();
	CCSize visibleSize = Director::getInstance()->getVisibleSize();
	CCPoint visibleOrigin = Director::getInstance()->getVisibleOrigin();

	MELOG(MELOG_INFO,"FrameSize: width[%f], height[%f] \n", frameSize.width, frameSize.height);
	MELOG(MELOG_INFO,"WinSize: width[%f], height[%f] \n", winSize.width, winSize.height);
	MELOG(MELOG_INFO,"VisibleSize: width[%f], height[%f] \n", visibleSize.width,	visibleSize.height);
	MELOG(MELOG_INFO,"VisibleOrigin: x[%f], y[%f] \n", visibleOrigin.x, visibleOrigin.y);
	MELOG(MELOG_INFO,"XScale: %f, YScale: %f \n", glview->getScaleX(),glview->getScaleY());
}

void MEResolution::setResolutionRect(int designWidth, int designHeight, int screenWidth, int screenHeight)
{
	MELOG(MELOG_INFO,"setResolutionRect ########### designWidth = %d, designHeight = %d, screenWidth = %d, screenHeight = %d \n",designWidth, designHeight,screenWidth, screenHeight );
	auto glview = Director::getInstance()->getOpenGLView();
	if(!glview)
		return;
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	glview->setFrameSize(screenWidth, screenHeight);
	//glview->setDesignResolutionSize(designWidth, designHeight, kResolutionNoBorder);
//#else
#endif
	MEResolution::adjustResolution();
//#endif
}

void MEResolution::setDefaultRect()
{
	setResolutionRect(s_designWidth, s_designHeight, s_screenWidth, s_screenHeight);
}