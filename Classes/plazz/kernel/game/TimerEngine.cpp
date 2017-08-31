#include "TimerEngine.h"
//宏定义
#define PULSE_TIMER					1000L								//脉冲时间
#define NO_TIME_LEAVE				dword(-1)							//忽略时间

TimerEngine::TimerEngine()
	: m_bService(false)
	, m_dwTimePass(0)
	, m_dwTimeLeave(NO_TIME_LEAVE)
	, m_dwTimerPulseSpace(PULSE_TIMER)
	, mITimerEngineSink(0)
{
}

TimerEngine::~TimerEngine()
{
	StopService();
}

void TimerEngine::SetTimerEngineSink(ITimerEngineSink* pITimerEngineSink)
{
	mITimerEngineSink = pITimerEngineSink;
}

void TimerEngine::StartService()
{
	StopService();
	m_bService = true;
	m_dwTimePass = 0;
	m_dwTimeLeave = NO_TIME_LEAVE;
	Director::getInstance()->getScheduler()->schedule(schedule_selector(TimerEngine::onTick), this, (m_dwTimerPulseSpace/1000.0f), false);
}

void TimerEngine::StopService()
{
	m_bService = false;
	StopTimers();
	Director::getInstance()->getScheduler()->unschedule(schedule_selector(TimerEngine::onTick), this);
}

void TimerEngine::StartTimer(word id)
{
	std::list<word>::iterator it = std::find(mTimerItemList.begin(), mTimerItemList.end(), id);
	
	if (it == mTimerItemList.end()) 
	{
		mTimerItemList.push_back(id);
	}

	m_dwTimePass = 0;
	m_dwTimeLeave = PULSE_TIMER;
}

void TimerEngine::StopTimer(word id)
{
	std::list<word>::iterator it = std::find(mTimerItemList.begin(), mTimerItemList.end(), id);
	if (it != mTimerItemList.end()) 
	{
		mTimerItemList.erase(it);

		if (mTimerItemList.empty())
		{
			m_dwTimePass = 0;
			m_dwTimeLeave = NO_TIME_LEAVE;
		}
	}
}

void TimerEngine::StopTimers()
{
	m_dwTimePass = 0;
	m_dwTimeLeave = NO_TIME_LEAVE;
	mTimerItemList.clear();
}

void TimerEngine::onTick(float dt)
{
	//倒计时间
	if (m_dwTimeLeave==NO_TIME_LEAVE)
	{
		//ASSERT(mTimerItemList.empty());
		return;
	}

	//效验状态
	//ASSERT(m_dwTimeLeave>=m_dwTimerPulseSpace);
	if (m_dwTimeLeave<m_dwTimerPulseSpace) m_dwTimeLeave=m_dwTimerPulseSpace;

	//减少时间
	m_dwTimePass+=m_dwTimerPulseSpace;
	m_dwTimeLeave-=m_dwTimerPulseSpace;

	//查询子项
	if (m_dwTimeLeave==0)
	{
		//发送通知
		if (mITimerEngineSink)
		{
			std::list<word>::iterator it = mTimerItemList.begin();
			std::list<word>::iterator itCur;

			for (; it != mTimerItemList.end();) {
				std::list<word>::iterator itCur = it++;
				mITimerEngineSink->OnTimerEngineTick(*itCur);
			}
		}
			
		//系统参数
		m_dwTimePass=0L;
		m_dwTimeLeave=PULSE_TIMER;
	}
}