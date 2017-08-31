#ifndef _CGPExchangeMission_H_
#define _CGPExchangeMission_H_
#include "../Plazz.h"

struct tagPay
{
	int		mBuyType;
	SCORE	mBuyCount;
	dword	mPayRMB;
	int		mPayType;
};

//////////////////////////////////////////////////////////////////////////
// 机器绑定修改提示
//////////////////////////////////////////////////////////////////////////
class IGPExchangeMissionSink
{
public:
	virtual ~IGPExchangeMissionSink(){}
	virtual void onGPExchangeResult(int lResultCode, const char* szDescription){}
	virtual void onGPShaerResult(const char* szDescription){}
	virtual void onGPPayCardResult(const char* szDescription){}
};

//////////////////////////////////////////////////////////////////////////
// 兑换道具
//////////////////////////////////////////////////////////////////////////
class CGPExchangeMission
	: public CSocketMission
{
public:
	CGPExchangeMission(const std::string& url, int port);
	// 设置回调接口
	void setMissionSink(IGPExchangeMissionSink* pIGPExchangeMissionSink);
	// 兑换道具
	void exchange(uint16 item);

	void pay(const tagPay& Pay);
	void payCard(const char* card, const char* pwd);

	void share();
	//////////////////////////////////////////////////////////////////////////
	// ISocketEngineSink
public:
	virtual void onEventTCPSocketLink();
	virtual void onEventTCPSocketShut();
	virtual void onEventTCPSocketError(int errorCode);
	virtual bool onEventTCPSocketRead(int main, int sub, void* data, int dataSize);
private:
	// 兑换结果
	bool onSubExchangeSuccess(void* data, int size);
	bool onSubPayResult(void* data, int size);
	bool onSubShareResult(void* data, int size);
	bool onSubPayCardResult(void* data, int size);

	bool sendExchangeItem();
	bool sendPay(const tagPay& Pay);
	bool sendShare();
	bool sendPayCard(const char* card, const char* pwd);
private:
	// 回调
	IGPExchangeMissionSink* mIGPExchangeMissionSink;
	// 任务类型
	uint8	mMissionType;
	uint8	mItem;
	tagPay  mPay;
	std::string mStrMBCard;
	std::string mStrMBPassword;
}; // CGPExchangeMission

#endif // _CGPExchangeMission_H_