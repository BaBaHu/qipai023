#ifndef _CGPKefuMission_H_
#define _CGPKefuMission_H_
#include "../Plazz.h"

//////////////////////////////////////////////////////////////////////////
// 机器绑定修改提示
//////////////////////////////////////////////////////////////////////////
class IGPKefuMissionSink
{
public:
	virtual ~IGPKefuMissionSink(){}
	virtual void onGPKefuResult(const char* szDescription){}
};

//////////////////////////////////////////////////////////////////////////
// 兑换道具
//////////////////////////////////////////////////////////////////////////
class CGPKefuMission
	: public CSocketMission
{
public:
	CGPKefuMission(const std::string& url, int port);
	// 设置回调接口
	void setMissionSink(IGPKefuMissionSink* pIGPKefuMissionSink);
	// 道具
	void Kefu();
	//////////////////////////////////////////////////////////////////////////
	// ISocketEngineSink
public:
	virtual void onEventTCPSocketLink();
	virtual void onEventTCPSocketShut();
	virtual void onEventTCPSocketError(int errorCode);
	virtual bool onEventTCPSocketRead(int main, int sub, void* data, int dataSize);
private:
	// 默认结果
	bool onDefaultKefuResult();
	// 结果
	bool onSubKefuResult(void* data, int size);
	
private:
	// 回调
	IGPKefuMissionSink* mIGPKefuMissionSink;
}; // CGPKefuMission

#endif // _CGPKefuMission_H_