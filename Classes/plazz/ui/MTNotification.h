#ifndef _MTNotification_H_
#define _MTNotification_H_

#include "cocos2d.h"
#include <mutex>

USING_NS_CC;

class MTData : public Ref
{
public:
	static MTData* create(unsigned int data1 = 0, unsigned int data2 = 0, unsigned int data3 = 0, 
		const std::string& str1 = "", const std::string& str2 = "", const std::string& str3 = "")
	{
		MTData* dat = new MTData();
		if (dat && dat->init(data1, data2, data3, str1, str2, str3))
		{
			dat->autorelease();
			return dat;
		}
		delete dat;
		return 0;
	}
	void* mPData;
	unsigned int mData1;
	unsigned int mData2;
	unsigned int mData3;
	std::string  mStr1;
	std::string  mStr2;
	std::string  mStr3;
private:
	MTData(){}
	~MTData(){}

	bool init(unsigned int data1, unsigned int data2, unsigned int data3,
		const std::string& str1, const std::string& str2, const std::string& str3)
	{
		mData1 = data1;
		mData2 = data2;
		mData3 = data3;
		mStr1  = str1;
		mStr2  = str2;
		mStr3  = str3;
		return true;
	}
};

//////////////////////////////////////////////////////////////////////////
class MTNotificationImp;

class MTNotification
	: public Ref
{
public:
	static MTNotification*	msInstance;
public:
	static MTNotification* shared();
	static void purge();

public:
	MTNotification();
	~MTNotification();
	void postNotify(const std::string& name, Ref* obj);
	void post(float dt);
private:
	struct MTNotifyData
	{
		std::string			name;
		Ref*	obj;
	}; // MTNotifyData

private:
	MTNotificationImp*	mImp;

	std::mutex mDataMutex;
	std::list<MTNotifyData> mDataQueues1;
	std::list<MTNotifyData> mDataQueues2;
	std::list<MTNotifyData>* mReceiveQueue;
	std::list<MTNotifyData>* mNotifyQueue;

};


#define G_NOTIFY(name, obj)				NotificationCenter::getInstance()->postNotification(name, obj)
#define G_NOTIFY_REG(name, callfuncO)	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(callfuncO), name, 0)
#define G_NOTIFY_UNREG(name)			NotificationCenter::getInstance()->removeObserver(this, name)

#define G_NOTIFY_SAFE(name, obj)		MTNotification::shared()->postNotify(name, obj)

#endif // _MTNotification_H_