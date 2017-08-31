#ifndef _TimerEngine_H_
#define _TimerEngine_H_

#include "../../df/types.h"

#include "cocos2d.h"
USING_NS_CC;

class ITimerEngineSink
{
public:
	virtual ~ITimerEngineSink(){};
	virtual void OnTimerEngineTick(word id) = 0;
};

class TimerEngine : public Ref
{
public:
	TimerEngine();
	~TimerEngine();
public:
	// 设置时间监听器
	void SetTimerEngineSink(ITimerEngineSink* pITimerEngineSink);

	// 开始服务
	void StartService();
	// 结束服务
	void StopService();

	// 设置时间
	void StartTimer(word id);
	// 停住时间
	void StopTimer(word id); 
	// 停住所有时间
	void StopTimers();
private:
	void onTick(float dt);

private:
	//状态变量
	bool				m_bService;					//运行标志
	dword				m_dwTimePass;				//经过时间
	dword				m_dwTimeLeave;				//倒计时间

	//配置定义
	dword				m_dwTimerPulseSpace;		//时间间隔

	std::list<word>		mTimerItemList;				//定时对象
	ITimerEngineSink*	mITimerEngineSink;			//定时回调

};
#endif // _TimerEngine_H_