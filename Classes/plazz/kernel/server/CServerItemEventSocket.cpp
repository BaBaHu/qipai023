#include "CServerItem.h"

//////////////////////////////////////////////////////////////////////////
// ISocketEngineSink
//////////////////////////////////////////////////////////////////////////
void CServerItem::onEventTCPSocketLink()
{
	PLAZZ_PRINTF("flow->CServerItem::onEventTCPSocketLink");
	SendLogonPacket();
}

void CServerItem::onEventTCPSocketShut()
{
	PLAZZ_PRINTF("flow->CServerItem::onEventTCPSocketShut");

	if (mServiceStatus != ServiceStatus_NetworkDown)
	{
		IntermitConnect(true, true);
		if (mIServerItemSink)
			mIServerItemSink->OnGFServerClose("");
	}
}

void CServerItem::onEventTCPSocketError(int errorCode)
{
	PLAZZ_PRINTF("flow->CServerItem::onEventTCPSocketError err:%d\n", errorCode);

	switch (errorCode)
	{
	case 10054:
		{
			if (mIStringMessageSink)
				mIStringMessageSink->InsertSystemString("操作异常,被断开连接!!!");
		}
		break;
	}

}

bool CServerItem::onEventTCPSocketRead(int main, int sub, void* data, int dataSize)
{
	switch (main)
	{
		//登录消息
	case MDM_GR_LOGON:	
		return OnSocketMainLogon(sub,data,dataSize);
		//配置信息
	case MDM_GR_CONFIG:	return OnSocketMainConfig(sub,data,dataSize);
		//用户信息
	case MDM_GR_USER:	return OnSocketMainUser(sub,data,dataSize);
		//状态信息
	case MDM_GR_STATUS:	return OnSocketMainStatus(sub,data,dataSize);
		//银行消息
	case MDM_GR_INSURE:	return OnSocketMainInsure(sub,data,dataSize);
		//管理消息
	case MDM_GR_MANAGE:	return OnSocketMainManager(sub,data,dataSize);
		//管理消息
	case MDM_CM_SYSTEM: return OnSocketMainSystem(sub,data,dataSize);
		//游戏消息
	case MDM_GF_GAME:
		//框架消息
	case MDM_GF_FRAME:	return OnSocketMainGameFrame(main,sub,data,dataSize);
		//比赛消息
	case MDM_GR_MATCH:	return OnSocketMainMatch(sub,data,dataSize);
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
