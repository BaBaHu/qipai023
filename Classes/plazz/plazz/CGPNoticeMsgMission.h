#ifndef _CGPNoticeMsgMission_H_
#define _CGPNoticeMsgMission_H_

#include "../Plazz.h"

class IGPMsgMissionSink
{
public:
	virtual ~IGPMsgMissionSink(){}
	virtual void onGPNotice(const char* szMessage){}
	virtual void onGPMsgError(int errorCode){}
};

class CGPNoticeMsgMission
	: public CSocketMission
{
public:
	CGPNoticeMsgMission(const std::string& url, int port);
	// 设置回调接口
	void setMissionSink(IGPMsgMissionSink* pIGPMsgMissionSink);
	void loginMsg();
private:
	bool sendLoginMsg();

	//////////////////////////////////////////////////////////////////////////
	// ISocketEngineSink
public:
	virtual void onEventTCPSocketLink();
	virtual void onEventTCPSocketShut();
	virtual void onEventTCPSocketError(int errorCode);
	virtual bool onEventTCPSocketRead(int main, int sub, void* data, int dataSize);
private:
	//////////////////////////////////////////////////////////////////////////
	// 登陆信息
	bool onSocketMainLogon(int sub, void* data, int size);
	// 聊天信息
	bool onSocketMainMsg(int sub, void* data, int size);
	
	//登录完成
	bool onSocketSubLogonFinish(void* data, int size);
	//喇叭消息
	bool onSocketSubBugle(void* data, int size);
	//系统消息
	bool onSocketSubMessage(void* data, int size);

private:
	// 回调
	IGPMsgMissionSink*					mIGPMsgMissionSink;
	// 任务类型
	uint8 mMissionType;
};

#endif //_CGPNoticeMsgMission_H_