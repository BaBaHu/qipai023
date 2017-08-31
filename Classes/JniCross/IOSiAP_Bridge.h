//
//  IOSiAP_Bridge.h
//  LongChengDaRen
//
//  Created by 白白 on 14-11-11.
//
//
#include "cocos2d.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#pragma once

#import "IOSiAP.h"
class IOSiAP_Bridge : public IOSiAPDelegate
{
public:
    IOSiAP_Bridge();
    ~IOSiAP_Bridge();
    IOSiAP *iap;
    int productID;
    std::string productIDStr;
    void requestProducts(const char* idStr);
    virtual void onRequestProductsFinish(void);
    virtual void onRequestProductsError(int code);
    virtual void onPaymentEvent(std::string &identifier, std::string &receipt, IOSiAPPaymentEvent event, int quantity);
};

#endif
