#include "CGPMachineMission.h"


CGPMachineMission::CGPMachineMission(const std::string& url, int port)
: CSocketMission(url, port)
{
	mIGPMachineMissionSink = 0;
}

// 设置回调接口
void CGPMachineMission::setMissionSink(IGPMachineMissionSink* pIGPMachineMissionSink)
{
	mIGPMachineMissionSink = pIGPMachineMissionSink;
}

void CGPMachineMission::modifyMachine(const char* szInsurePassword, uint8 cbBind)
{
	memcpy(mInsurePassword, szInsurePassword, sizeof(mInsurePassword));
	mBind = cbBind;
	start();
}

void CGPMachineMission::onEventTCPSocketLink()
{
	PLAZZ_PRINTF("CGPMachineMission::onEventTCPSocketLink\n");

	//变量定义
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//变量定义
	PACKET_AIDE_SIZE(512);
	packet.writeByte(mBind);
	packet.write4Byte(pGlobalUserData->dwUserID);
	packet.writeString(DF::MD5Encrypt(mInsurePassword), LEN_PASSWORD);
	packet.writeString(DF::shared()->GetMachineID(), LEN_MACHINE_ID);

	//发送数据
	send(MDM_GP_USER_SERVICE,SUB_GP_MODIFY_MACHINE, packet.getBuffer(), packet.getPosition());

	////变量定义
	//CMD_GP_ModifyMachine ModifyMachine;
	//zeromemory(&ModifyMachine,sizeof(ModifyMachine));

	////变量定义
	//CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	//tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	////设置变量
	//ModifyMachine.cbBind=mBind;
	//ModifyMachine.dwUserID=pGlobalUserData->dwUserID;

	////加密密码
	//DF::shared()->GetMachineID(ModifyMachine.szMachineID);
	//DF::MD5Encrypt(mInsurePassword,ModifyMachine.szPassword);

	////发送数据
	//send(MDM_GP_USER_SERVICE,SUB_GP_MODIFY_MACHINE,&ModifyMachine,sizeof(ModifyMachine));
}

void CGPMachineMission::onEventTCPSocketShut()
{
	PLAZZ_PRINTF("CGPMachineMission::onEventTCPSocketShut\n");
}

void CGPMachineMission::onEventTCPSocketError(int errorCode)
{
	PLAZZ_PRINTF("CGPMachineMission::onEventTCPSocketError code[%d]\n", errorCode);
}

bool CGPMachineMission::onEventTCPSocketRead(int main, int sub, void* data, int size) 
{
	PLAZZ_PRINTF("CGPMachineMission::onEventTCPSocketRead main:%d sub:%d size:%d\n", main, sub, size);
	if (main != MDM_GP_USER_SERVICE)
	{
		return false;
	}

	switch (sub)
	{
		//操作成功
	case SUB_GP_OPERATE_SUCCESS:	return onSubOperateSuccess(data, size);
		//操作失败
	case SUB_GP_OPERATE_FAILURE:	return onSubOperateFailure(data, size);
	}

	return false;
}

// 操作成功
bool CGPMachineMission::onSubOperateSuccess(void* data, int size)
{
	int baseSize = 4;
	//效验参数
	ASSERT(size>=baseSize);
	if (size<baseSize) return false;

	PACKET_AIDE_DATA(data);
	int lResultCode	= packet.read4Byte();
	std::string str	= packet.readString((size-baseSize)/2);

	//关闭连接
	stop();

	//变量定义
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//设置变量
	pGlobalUserData->cbMoorMachine=(mBind==TRUE)?TRUE:FALSE;

	//显示消息
	if (mIGPMachineMissionSink)
		mIGPMachineMissionSink->onGPMachineSuccess(str.c_str());
	return true;

	////变量定义
	//CMD_GP_OperateSuccess * pOperateSuccess=(CMD_GP_OperateSuccess *)data;

	////效验数据
	//ASSERT(size>=(sizeof(CMD_GP_OperateSuccess)-sizeof(pOperateSuccess->szDescribeString)));
	//if (size<(sizeof(CMD_GP_OperateSuccess)-sizeof(pOperateSuccess->szDescribeString))) return false;

	////变量定义
	//CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	//tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	////设置变量
	//pGlobalUserData->cbMoorMachine=(mBind==TRUE)?TRUE:FALSE;

	////关闭连接
	//stop();

	////显示消息
	//if (mIGPMachineMissionSink)
	//	mIGPMachineMissionSink->onGPMachineSuccess(pOperateSuccess->szDescribeString);
	//return true;
}

// 操作失败
bool CGPMachineMission::onSubOperateFailure(void* data, int size)
{
	int baseSize = 4;
	//效验参数
	ASSERT(size>=baseSize);
	if (size<baseSize) return false;

	PACKET_AIDE_DATA(data);
	int lResultCode	= packet.read4Byte();
	std::string str	= packet.readString((size-baseSize)/2);

	//关闭连接
	stop();

	//显示消息
	if (mIGPMachineMissionSink)
		mIGPMachineMissionSink->onGPMachineFailure(str.c_str());

	return true;
	////效验参数
	//CMD_GP_OperateFailure * pOperateFailure=(CMD_GP_OperateFailure *)data;
	//ASSERT(size>=(sizeof(CMD_GP_OperateFailure)-sizeof(pOperateFailure->szDescribeString)));
	//if (size<(sizeof(CMD_GP_OperateFailure)-sizeof(pOperateFailure->szDescribeString))) return false;

	////关闭连接
	//stop();

	////显示消息
	//if (mIGPMachineMissionSink)
	//	mIGPMachineMissionSink->onGPMachineFailure(pOperateFailure->szDescribeString);
	//return true;
}