#include "CGPPasswordMission.h"

CGPPasswordMission::CGPPasswordMission(const std::string& url, int port)
: CSocketMission(url, port)
{
	mMissionType = MISSION_PASSWORD_NULL;
	mIGPPasswordMissionSink = 0;
}

// 设置回调接口
void CGPPasswordMission::setMissionSink(IGPPasswordMissionSink* pIGPPasswordMissionSink)
{
	mIGPPasswordMissionSink = pIGPPasswordMissionSink;
}

// 修改登陆密码
void CGPPasswordMission::modifyLogin(const char* szSrc, const char* szDst)
{
	mMissionType = MISSION_PASSWORD_LOGIN;
	memcpy(mSrcLogin, szSrc, sizeof(mSrcLogin));
	memcpy(mDstLogin, szDst, sizeof(mDstLogin));
	start();
}

// 修改银行柜密码
void CGPPasswordMission::modifyInsure(const char* szSrc, const char* szDst)
{
	mMissionType = MISSION_PASSWORD_INSURE;
	memcpy(mSrcInsure, szSrc, sizeof(mSrcInsure));
	memcpy(mDstInsure, szDst, sizeof(mDstInsure));
	start();
}

void CGPPasswordMission::onEventTCPSocketLink()
{
	PLAZZ_PRINTF("CGPPasswordMission::onEventTCPSocketLink\n");

	
	switch (mMissionType)
	{
		// 登陆密码
	case MISSION_PASSWORD_LOGIN:
		{
			//变量定义
			CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

			//变量定义
			PACKET_AIDE_SIZE(512);
			packet.write4Byte(pGlobalUserData->dwUserID);
			packet.writeString(DF::MD5Encrypt(mDstLogin), LEN_PASSWORD);
			packet.writeString(DF::MD5Encrypt(mSrcLogin), LEN_PASSWORD);
			//发送数据
			send(MDM_GP_USER_SERVICE,SUB_GP_MODIFY_LOGON_PASS, packet.getBuffer(), packet.getPosition());

			////变量定义
			//CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			//tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

			////变量定义
			//CMD_GP_ModifyLogonPass ModifyLogonPass;
			//zeromemory(&ModifyLogonPass,sizeof(ModifyLogonPass));

			////加密密码
			//tchar szSrcPassword[LEN_PASSWORD]=T_T("");
			//tchar szDesPassword[LEN_PASSWORD]=T_T("");
			//DF::MD5Encrypt(mSrcLogin,szSrcPassword);
			//DF::MD5Encrypt(mDstLogin,szDesPassword);

			////构造数据
			//ModifyLogonPass.dwUserID=pGlobalUserData->dwUserID;
			//tstrcpyn(ModifyLogonPass.szScrPassword,szSrcPassword,countarray(ModifyLogonPass.szScrPassword));
			//tstrcpyn(ModifyLogonPass.szDesPassword,szDesPassword,countarray(ModifyLogonPass.szDesPassword));

			////发送数据
			//send(MDM_GP_USER_SERVICE,SUB_GP_MODIFY_LOGON_PASS,&ModifyLogonPass,sizeof(ModifyLogonPass));

			break;
		}
		// 银行密码
	case MISSION_PASSWORD_INSURE:
		{
			//变量定义
			CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

			//变量定义
			PACKET_AIDE_SIZE(512);
			packet.write4Byte(pGlobalUserData->dwUserID);
			packet.writeString(DF::MD5Encrypt(mDstInsure), LEN_PASSWORD);
			packet.writeString(DF::MD5Encrypt(mSrcInsure), LEN_PASSWORD);
			
			//发送数据
			send(MDM_GP_USER_SERVICE,SUB_GP_MODIFY_INSURE_PASS, packet.getBuffer(),packet.getPosition());

			////变量定义
			//CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			//tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

			////变量定义
			//CMD_GP_ModifyInsurePass ModifyInsurePass;
			//zeromemory(&ModifyInsurePass,sizeof(ModifyInsurePass));

			////加密密码
			//tchar szSrcPassword[LEN_PASSWORD]=T_T("");
			//tchar szDesPassword[LEN_PASSWORD]=T_T("");
			//DF::MD5Encrypt(mSrcInsure,szSrcPassword);
			//DF::MD5Encrypt(mDstInsure,szDesPassword);

			////构造数据
			//ModifyInsurePass.dwUserID=pGlobalUserData->dwUserID;
			//tstrcpyn(ModifyInsurePass.szScrPassword,szSrcPassword,countarray(ModifyInsurePass.szScrPassword));
			//tstrcpyn(ModifyInsurePass.szDesPassword,szDesPassword,countarray(ModifyInsurePass.szDesPassword));

			////发送数据
			//send(MDM_GP_USER_SERVICE,SUB_GP_MODIFY_INSURE_PASS,&ModifyInsurePass,sizeof(ModifyInsurePass));
			break;
		}
	}

}

void CGPPasswordMission::onEventTCPSocketShut()
{
	PLAZZ_PRINTF("CGPPasswordMission::onEventTCPSocketShut\n");
}

void CGPPasswordMission::onEventTCPSocketError(int errorCode)
{
	PLAZZ_PRINTF("CGPPasswordMission::onEventTCPSocketError code[%d]\n", errorCode);
}

bool CGPPasswordMission::onEventTCPSocketRead(int main, int sub, void* data, int size) 
{
	PLAZZ_PRINTF("CGPPasswordMission::onEventTCPSocketRead main:%d sub:%d size:%d\n", main, sub, size);
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
bool CGPPasswordMission::onSubOperateSuccess(void* data, int size)
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
	//CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	//tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	switch (mMissionType)
	{
		// 登陆密码
	case MISSION_PASSWORD_LOGIN:
		{
			////变量定义
			//CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			//tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

			////密码资料
			//tchar szDesPassword[LEN_PASSWORD]=T_T("");
			//DF::MD5Encrypt(mDstLogin,szDesPassword);
			//tstrcpyn(pGlobalUserData->szPassword,szDesPassword,countarray(pGlobalUserData->szPassword));
			break;
		}
		// 银行密码
	case MISSION_PASSWORD_INSURE:
		{
			break;
		}
	}

	//显示消息
	if (mIGPPasswordMissionSink)
		mIGPPasswordMissionSink->onGPPasswordSuccess(mMissionType, str.c_str());
	return true;
}

// 操作失败
bool CGPPasswordMission::onSubOperateFailure(void* data, int size)
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
	if (mIGPPasswordMissionSink)
		mIGPPasswordMissionSink->onGPPasswordFailure(mMissionType, str.c_str());
	return true;

	////效验参数
	//CMD_GP_OperateFailure * pOperateFailure=(CMD_GP_OperateFailure *)data;
	//ASSERT(size>=(sizeof(CMD_GP_OperateFailure)-sizeof(pOperateFailure->szDescribeString)));
	//if (size<(sizeof(CMD_GP_OperateFailure)-sizeof(pOperateFailure->szDescribeString))) return false;

	////关闭连接
	//stop();

	////显示消息
	//if (mIGPPasswordMissionSink)
	//	mIGPPasswordMissionSink->onGPPasswordFailure(mMissionType, pOperateFailure->szDescribeString);
	//return true;
}