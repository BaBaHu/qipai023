#ifndef _PAYUI_H_
#define _PAYUI_H_

#include "cocos2d.h"
#include "../plazz/GPMission.h"
#include "../../JniCross/IOSiAP_Bridge.h"
USING_NS_CC;

//充值
class PayUI : public Ref, IGPExchangeMissionSink
{
public:
	PayUI();
	~PayUI();
	static PayUI* create(std::string strIp, int iPort);

	void exchange(int item);
    void payIpa(const char* proId);
	void pay(int nBuyType, long long lBuyCount, unsigned int mPayRMB, int nPayType);
	void payCard(const char* card, const char* pwd);
	void share();
	//回调函数
public:
	virtual void onGPExchangeResult(int lResultCode, const char* szDescription);
	virtual void onGPShaerResult(const char* szDescription);
	virtual void onGPPayCardResult(const char* szDescription);
private:
	bool init(std::string strIp, int iPort);
private:
	// mission
	CGPExchangeMission	mExchangeMission;
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    IOSiAP_Bridge*      m_bridge;
	#endif
};

#endif // _BANKUI_H_
