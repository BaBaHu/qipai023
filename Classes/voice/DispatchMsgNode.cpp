//
//  DispatchMsgNode.cpp
//  GameBase
//
//  Created by zjm on 16/9/1.
//
//

#include "DispatchMsgNode.h"
#include "YunVaSDK/YVTool.h"
using namespace cocos2d;
using namespace YVSDK;

bool DispatchMsgNode::init()
{
    isschedule = false;
    return  Node::init();
}

void DispatchMsgNode::startDispatch()
{
    if (isschedule) return;
    isschedule = true;
    Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
}
void DispatchMsgNode::stopDispatch()
{
    if (!isschedule) return;
    isschedule = false;
    Director::getInstance()->getScheduler()->unscheduleUpdate(this);
}
void DispatchMsgNode::update(float dt)
{
    YVTool::getInstance()->dispatchMsg(dt);
}
