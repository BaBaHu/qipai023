//
//  DispatchMsgNode.hpp
//  GameBase
//
//  Created by zjm on 16/9/1.
//
//

#ifndef DispatchMsgNode_h
#define DispatchMsgNode_h

#include <stdio.h>
#include "cocos2d.h"

class DispatchMsgNode : public cocos2d::Node
{
public:
    bool init();
    void startDispatch();
    void stopDispatch();
    void update(float dt);
    CREATE_FUNC(DispatchMsgNode);
private:
    bool isschedule;
    
};


#endif /* DispatchMsgNode_h */
