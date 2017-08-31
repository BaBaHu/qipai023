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
	// ���ûص��ӿ�
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
	// ��½��Ϣ
	bool onSocketMainLogon(int sub, void* data, int size);
	// ������Ϣ
	bool onSocketMainMsg(int sub, void* data, int size);
	
	//��¼���
	bool onSocketSubLogonFinish(void* data, int size);
	//������Ϣ
	bool onSocketSubBugle(void* data, int size);
	//ϵͳ��Ϣ
	bool onSocketSubMessage(void* data, int size);

private:
	// �ص�
	IGPMsgMissionSink*					mIGPMsgMissionSink;
	// ��������
	uint8 mMissionType;
};

#endif //_CGPNoticeMsgMission_H_