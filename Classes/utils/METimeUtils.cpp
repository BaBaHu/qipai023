#include "METimeUtils.h"
#include "cocos2d.h"
USING_NS_CC;

double METimeUtils::clock()
{
    timeval t;
    gettimeofday(&t, 0);
    return (t.tv_sec)  + t.tv_usec*0.000001;
}
