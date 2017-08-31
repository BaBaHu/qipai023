//
//  IOSiAP_Bridge.cpp
//  LongChengDaRen
//
//  Created by 白白 on 14-11-11.
//
//

#include "IOSiAP_Bridge.h"
#include "cocos2d.h"
USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

IOSiAP_Bridge::IOSiAP_Bridge()
{
    iap = new IOSiAP();
    iap->delegate = this;
}

IOSiAP_Bridge::~IOSiAP_Bridge()
{
    delete iap;
}

void IOSiAP_Bridge:: requestProducts(const char* idStr)
{
    productIDStr = idStr;
    std::vector<std::string> product;
    product.push_back("com.yibo98.weishui_1001");
    //product.push_back("com.yibo98.weishui_2001");
	//把需要付费的道具的所有product id都放到容器里面传进去
    iap->requestProducts(product);

}

void IOSiAP_Bridge::onRequestProductsFinish(void)
{
    std::string identifier = productIDStr;

    //必须在onRequestProductsFinish后才能去请求iAP产品数据。
    IOSProduct *product = iap->iOSProductByIdentifier(identifier);
    // 然后可以发起付款请求。,第一个参数是由iOSProductByIdentifier获取的IOSProduct实例，第二个参数是购买数量
    iap->paymentWithProduct(product, 1);
}

void IOSiAP_Bridge::onRequestProductsError(int code)
{
    //这里requestProducts出错了，不能进行后面的所有操作。
    log("付款失败");

}

void IOSiAP_Bridge::onPaymentEvent(std::string &identifier, std::string &receipt, IOSiAPPaymentEvent event, int quantity)
{
    
    log("发送消息到服务端---");
    log("identifier = %s", identifier.c_str() );
    log("receipt = %s", receipt.c_str() );
    log("quantity = %d", quantity);

    /*GameIPABuyItemCompleteMsg iapResutMsg;
    sprintf_s(iapResutMsg.orderno, 128, "%s", appGetGlobal()->appleOrder.c_str());
    sprintf_s(iapResutMsg.payResult, 1024*5, "%s", identifier.c_str());
    
    CGameGlobal::getInstance()->sendMsg(&iapResutMsg);
    
    //appGetGlobal()->IapBuySuccess(&iapResutMsg);
    
    //IapPaySuccess(productIDStr.c_str(), identifier.c_str());
    
    CCLog("发送消息到服务端---");
    CCLog("iapResutMsg.orderno = %s", iapResutMsg.orderno);
    CCLog("iapResutMsg.payResult = %s", iapResutMsg.payResult);
    CCLog("iapResutMsg.payResult LENTH = %lu", strlen(iapResutMsg.payResult));
    
    LoadingPanel::hide();
 
    if (event == IOSIAP_PAYMENT_PURCHAED)
    {
        //付款成功了，可以吧金币发给玩家了。
		//根据传入的参数就能知道购买的是哪种类型的金币
//        switch (productID) {
//            case 6:
//                
//                break;
//            case 18:
//               
//                break;
//            case 50:
//               
//                break;
//            case 98:
//               
//                break;
//            default:
//                break;
//        }        
//        CCLog("付款成功");
        
        
        //将支付返回的结果信息传给服务端进行验证
        GameIPABuyItemCompleteMsg iapResutMsg;
        sprintf_s(iapResutMsg.orderno, 128, "%s", productIDStr.c_str());
        sprintf_s(iapResutMsg.payResult, 1024*5, "%s", identifier.c_str());
        
        //CGameGlobal::getInstance()->sendMsg(&iapResutMsg);
        
        //appGetGlobal()->IapBuySuccess(&iapResutMsg);
        
        IapPaySuccess(productIDStr.c_str(), identifier.c_str());
        
        CCLog("发送消息到服务端---");
        CCLog("iapResutMsg.orderno = %s", iapResutMsg.orderno);
        CCLog("iapResutMsg.payResult = %s", iapResutMsg.payResult);
        CCLog("iapResutMsg.payResult LENTH = %lu", strlen(iapResutMsg.payResult));
    }
    //其他状态依情况处理掉。
  */
}

#endif
