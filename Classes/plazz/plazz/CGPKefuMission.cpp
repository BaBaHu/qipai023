#include "CGPKefuMission.h"


CGPKefuMission::CGPKefuMission(const std::string& url, int port)
: CSocketMission(url, port)
{
	mIGPKefuMissionSink = 0;
}

// 设置回调接口
void CGPKefuMission::setMissionSink(IGPKefuMissionSink* pIGPKefuMissionSink)
{
	mIGPKefuMissionSink = pIGPKefuMissionSink;
}

void CGPKefuMission::Kefu()
{
	start();
}

void CGPKefuMission::onEventTCPSocketLink()
{
	//发送数据
	send(MDM_GP_USER_SERVICE,SUB_GP_KEFU, 0, 0);
}

void CGPKefuMission::onEventTCPSocketShut()
{
	PLAZZ_PRINTF("CGPKefuMission::onEventTCPSocketShut\n");
}

void CGPKefuMission::onEventTCPSocketError(int errorCode)
{
	onDefaultKefuResult();
	PLAZZ_PRINTF("CGPKefuMission::onEventTCPSocketError code[%d]\n", errorCode);
}

bool CGPKefuMission::onEventTCPSocketRead(int main, int sub, void* data, int size) 
{
	PLAZZ_PRINTF("CGPKefuMission::onEventTCPSocketRead main:%d sub:%d size:%d\n", main, sub, size);
	if (main != MDM_GP_USER_SERVICE)
	{
		return false;
	}

	switch (sub)
	{
		//结果
	case SUB_GP_KEFU_RESULT:	return onSubKefuResult(data, size);
	}

	return false;
}

// 默认结果
bool CGPKefuMission::onDefaultKefuResult()
{
	std::string sMsg = "\n\
	您可以与客服联系，\n\
	对与提供宝贵意见的玩家，采纳后\n\
	我们将会给与金币奖励哦！\n";
	//显示消息
	if (mIGPKefuMissionSink)
		mIGPKefuMissionSink->onGPKefuResult(sMsg.c_str());
	return true;
}

// 结果
bool CGPKefuMission::onSubKefuResult(void* data, int size)
{
	//关闭连接
	stop();

	PACKET_AIDE_DATA(data);
	std::string sMsg = packet.readString(size/2);
	PLAZZ_PRINTF("kefu:%s", sMsg.c_str());
	//显示消息
	if (mIGPKefuMissionSink)
		mIGPKefuMissionSink->onGPKefuResult(sMsg.c_str());
	return true;
}
