#include "CGPInsureMission.h"

CGPInsureMission::CGPInsureMission(const std::string& url, int port)
: CSocketMission(url, port)
{
	mMissionType = 0;
	mIGPInsureMissionSink = 0;
	memset(mInsurePass, 0, sizeof(mInsurePass));
	memset(mNickName, 0, sizeof(mNickName));
	memset(mOldPass, 0, sizeof(mOldPass));
	memset(mNewPass, 0, sizeof(mNewPass));
}

void CGPInsureMission::setMissionSink(IGPInsureMissionSink* pIGPInsureMissionSink)
{
	mIGPInsureMissionSink = pIGPInsureMissionSink;
}

void CGPInsureMission::query()
{
	mMissionType = INSURE_MISSION_QUERY;
	start();
}

void CGPInsureMission::save(int64 score)
{
	mScore = score;
	mMissionType = INSURE_MISSION_SAVE;
	start();
}

void CGPInsureMission::take(int64 score, const char* szInsurePass)
{
	mScore = score;
	memcpy(mInsurePass, szInsurePass, sizeof(mInsurePass));
	mMissionType = INSURE_MISSION_TAKE;
	start();
}

void CGPInsureMission::transfer(int nType, int64 score, const char* szInsurePass, const char* szNickName, uint8 cbByNickName)
{
	mScore = score;
	mByNickName = cbByNickName;
	memcpy(mInsurePass, szInsurePass, sizeof(mInsurePass));
	memcpy(mNickName, szNickName, sizeof(mNickName));
	if (nType == 1)
	{
		mMissionType = INSURE_MISSION_TRANSFER;
	}
	else if (nType == 2)
	{
		mMissionType = INSURE_MISSION_TRANSFER_ROOMCARD;
	}
	start();
}

// 修改密码
void CGPInsureMission::modifyPassword(int nType, const char* szOldPass, const char* szNewPass)
{
	memcpy(mOldPass, szOldPass, sizeof(mOldPass));
	memcpy(mNewPass, szNewPass, sizeof(mNewPass));

	if (nType == 1)
	{
		mMissionType = INSURE_MISSION_MODIFY_INSURE_PASS;
	}
	else if (nType == 2)
	{
		mMissionType = INSURE_MISSION_MODIFY_LOGON_PASS;
	}
	start();
}

void CGPInsureMission::onEventTCPSocketLink()
{
	PLAZZ_PRINTF("CGPInsureMission::onEventTCPSocketLink\n");

	
	switch (mMissionType)
	{
		// 查询
	case INSURE_MISSION_QUERY:
		{
			//TEST_NULL
			//变量定义
			CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

			//打包数据
			PACKET_AIDE_SIZE(512);
			packet.write4Byte(pGlobalUserData->dwUserID);
			packet.writeString(DF::MD5Encrypt(mInsurePass), LEN_PASSWORD);
			//发送数据
			send(MDM_GP_USER_SERVICE,SUB_GP_QUERY_INSURE_INFO, packet.getBuffer(), packet.getPosition());

			////变量定义
			//CMD_GP_QueryInsureInfo QueryInsureInfo;
			//zeromemory(&QueryInsureInfo,sizeof(QueryInsureInfo));

			////设置变量
			//CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			//QueryInsureInfo.dwUserID=pGlobalUserInfo->GetGlobalUserData()->dwUserID;

			////发送数据
			//send(MDM_GP_USER_SERVICE,SUB_GP_QUERY_INSURE_INFO,&QueryInsureInfo,sizeof(QueryInsureInfo));
			break;
		}
		// 存入
	case INSURE_MISSION_SAVE:
		{
			//TEST_NULL
			//变量定义
			CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
			
			//打包数据
			PACKET_AIDE_SIZE(512);
			packet.write4Byte(pGlobalUserData->dwUserID);
			packet.write8Byte(mScore);
			packet.writeString(DF::shared()->GetMachineID(), LEN_MACHINE_ID);

			//发送数据
			send(MDM_GP_USER_SERVICE,SUB_GP_USER_SAVE_SCORE, packet.getBuffer(), packet.getPosition());

			////变量定义
			//CMD_GP_UserSaveScore UserSaveScore;
			//zeromemory(&UserSaveScore,sizeof(UserSaveScore));

			////变量定义
			//CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			//tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

			////设置变量
			//UserSaveScore.lSaveScore=mScore;
			//UserSaveScore.dwUserID=pGlobalUserData->dwUserID;
			//DF::shared()->GetMachineID(UserSaveScore.szMachineID);

			////发送数据
			//send(MDM_GP_USER_SERVICE,SUB_GP_USER_SAVE_SCORE,&UserSaveScore,sizeof(UserSaveScore));
			break;
		}
		// 取款
	case INSURE_MISSION_TAKE:
		{
			//变量定义
			CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

			//打包数据
			PACKET_AIDE_SIZE(512);
			packet.write4Byte(pGlobalUserData->dwUserID);
			packet.write8Byte(mScore);
			packet.writeString(DF::MD5Encrypt(mInsurePass), LEN_PASSWORD);
			packet.writeString(DF::shared()->GetMachineID(), LEN_MACHINE_ID);

			//发送数据
			send(MDM_GP_USER_SERVICE,SUB_GP_USER_TAKE_SCORE, packet.getBuffer(), packet.getPosition());

			////变量定义
			//CMD_GP_UserTakeScore UserTakeScore;
			//zeromemory(&UserTakeScore,sizeof(UserTakeScore));

			////变量定义
			//CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			//tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

			////设置变量
			//UserTakeScore.lTakeScore=mScore;
			//UserTakeScore.dwUserID=pGlobalUserData->dwUserID;
			//DF::shared()->GetMachineID(UserTakeScore.szMachineID);
			//DF::MD5Encrypt(mInsurePass,UserTakeScore.szPassword);

			////发送数据
			//send(MDM_GP_USER_SERVICE,SUB_GP_USER_TAKE_SCORE,&UserTakeScore,sizeof(UserTakeScore));
			break;
		}
		// 转账
	case INSURE_MISSION_TRANSFER:
	case INSURE_MISSION_TRANSFER_ROOMCARD:
		{
			CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();

			PACKET_AIDE_SIZE(512);
			packet.write4Byte(pGlobalUserData->dwUserID);
			packet.writeByte(mByNickName);
			packet.write8Byte(mScore);
			packet.writeString(DF::MD5Encrypt(mInsurePass), LEN_PASSWORD);
			packet.writeString(mNickName, LEN_NICKNAME);
			packet.writeString(DF::shared()->GetMachineID(), LEN_MACHINE_ID);
			//发送数据
			if (mMissionType == INSURE_MISSION_TRANSFER)
			{
				send(MDM_GP_USER_SERVICE, SUB_GP_USER_TRANSFER_SCORE, packet.getBuffer(), packet.getPosition());
			}
			else if (mMissionType == INSURE_MISSION_TRANSFER_ROOMCARD)
			{
				send(MDM_GP_USER_SERVICE, SUB_GP_USER_TRANSFER_ROOMC, packet.getBuffer(), packet.getPosition());
			}

			////变量定义
			//CMD_GP_QueryUserInfoRequest QueryUserInfoRequest;
			//zeromemory(&QueryUserInfoRequest,sizeof(QueryUserInfoRequest));

			////设置变量
			//QueryUserInfoRequest.cbByNickName=mByNickName;
			//tstrcpyn(QueryUserInfoRequest.szNickName,mNickName,countarray(QueryUserInfoRequest.szNickName));

			////发送数据
			//send(MDM_GP_USER_SERVICE,SUB_GP_QUERY_USER_INFO_REQUEST,&QueryUserInfoRequest,sizeof(QueryUserInfoRequest));
			break;
		}
		// 修改密码
	case INSURE_MISSION_MODIFY_LOGON_PASS:
	case INSURE_MISSION_MODIFY_INSURE_PASS:
		{
			CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();

			PACKET_AIDE_SIZE(512);
			packet.write4Byte(pGlobalUserData->dwUserID);
			packet.writeString(DF::MD5Encrypt(mNewPass), LEN_PASSWORD);
			packet.writeString(DF::MD5Encrypt(mOldPass), LEN_PASSWORD);

			//发送数据
			if (mMissionType == INSURE_MISSION_MODIFY_LOGON_PASS)
			{
				send(MDM_GP_USER_SERVICE, SUB_GP_MODIFY_LOGON_PASS, packet.getBuffer(), packet.getPosition());
			}
			else if (mMissionType == INSURE_MISSION_MODIFY_INSURE_PASS)
			{
				send(MDM_GP_USER_SERVICE, SUB_GP_MODIFY_INSURE_PASS, packet.getBuffer(), packet.getPosition());
			}
			break;
		}
	}

}

void CGPInsureMission::onEventTCPSocketShut()
{
	PLAZZ_PRINTF("CGPInsureMission::onEventTCPSocketShut\n");
}

void CGPInsureMission::onEventTCPSocketError(int errorCode)
{
	PLAZZ_PRINTF("CGPInsureMission::onEventTCPSocketError code[%d]\n", errorCode);
}

bool CGPInsureMission::onEventTCPSocketRead(int main, int sub, void* data, int size) 
{
	PLAZZ_PRINTF("CGPInsureMission::onEventTCPSocketRead main:%d sub:%d size:%d\n", main, sub, size);
	if (main != MDM_GP_USER_SERVICE)
	{
		return false;
	}

	switch (sub)
	{
		//转账查询
	case SUB_GP_QUERY_USER_INFO_RESULT:		return onSubQueryInfoResult(data, size);
		//银行资料
	case SUB_GP_USER_INSURE_INFO:			return onSubInsureInfo(data, size);
		//银行成功
	case SUB_GP_USER_INSURE_SUCCESS:		return onSubInsureSuccess(data, size);
		//银行失败
	case SUB_GP_USER_INSURE_FAILURE:		return onSubInsureFailure(data, size);	
		//操作成功
	case SUB_GP_OPERATE_SUCCESS:			return onSubOperateSuccess(data, size);
		//操作失败
	case SUB_GP_OPERATE_FAILURE:			return onSubOperateFailure(data, size);
		//房卡转账成功
	case SUB_GP_USER_ROOMC_SUCCESS:			return onSubTransferRoomCardSuccess(data, size);
	}

	return false;
}

//转账查询
bool CGPInsureMission::onSubQueryInfoResult(void* data, int size)
{
	////效验参数
	//ASSERT(size==(sizeof(dword)+sizeof(tchar)*LEN_NICKNAME));
	//if (size<(sizeof(dword)+sizeof(tchar)*LEN_NICKNAME)) return false;

	//变量定义
	//PACKET_AIDE_DATA(data);

	//dword dwTargetGameID = packet.read4Byte();
	//std::string sNickname = packet.readString(LEN_NICKNAME);

	////构造消息
	//char szMessage[128]={0};
	//sprintf(szMessage, "您确定要给[%s], ID:%lu 赠送 " LLSTRING " 星豆吗?", sNickname.c_str(), dwTargetGameID, mScore);

	//// 实现对话框
	//CGDialog("系统提示", szMessage, CGDLG_MB_OK|CGDLG_MB_CANCEL,
	//	[&](){
	//		//变量定义
	//		CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	//		tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//		PACKET_AIDE_SIZE(512);
	//		packet.write4Byte(pGlobalUserData->dwUserID);
	//		packet.writeByte(mByNickName);
	//		packet.write8Byte(mScore);
	//		packet.writeString(DF::MD5Encrypt(mInsurePass), LEN_PASSWORD);
	//		packet.writeString(mNickName, LEN_NICKNAME);
	//		packet.writeString(DF::shared()->GetMachineID(), LEN_MACHINE_ID);
	//		//发送数据
	//		send(MDM_GP_USER_SERVICE,SUB_GP_USER_TRANSFER_SCORE, packet.getBuffer(), packet.getPosition());
	//	},
	//	[&](){
	//		//关闭连接
	//		stop();
	//	});
	return true;
	
	////效验参数
	//ASSERT(size==sizeof(CMD_GP_UserTransferUserInfo));
	//if (size<sizeof(CMD_GP_UserTransferUserInfo)) return false;

	////变量定义
	//CMD_GP_UserTransferUserInfo * pTransferUserInfo=(CMD_GP_UserTransferUserInfo *)data;

	////构造消息
	//tchar szMessage[128]={0};
	//_sntprintf(szMessage, countarray(szMessage), T_T("您确定要给[%s], ID:%d 赠送%I64d 星豆吗?"), pTransferUserInfo->szNickName, pTransferUserInfo->dwTargetGameID, mScore);

	//if (mIGPInsureMissionSink)
	//{
	//	if (mIGPInsureMissionSink->onInsureTransferConfirm(szMessage))
	//	{
	//		////变量定义
	//		//CMD_GP_UserTransferScore UserTransferScore;
	//		//zeromemory(&UserTransferScore,sizeof(UserTransferScore));

	//		////变量定义
	//		//CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	//		//tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//		////设置变量
	//		//UserTransferScore.cbByNickName=mByNickName;
	//		//UserTransferScore.lTransferScore=mScore;
	//		//UserTransferScore.dwUserID=pGlobalUserData->dwUserID;
	//		//DF::shared()->GetMachineID(UserTransferScore.szMachineID);
	//		//DF::MD5Encrypt(mInsurePass,UserTransferScore.szPassword);
	//		//tstrcpyn(UserTransferScore.szNickName,mNickName,countarray(UserTransferScore.szNickName));
	//	
	//		////发送数据
	//		//send(MDM_GP_USER_SERVICE,SUB_GP_USER_TRANSFER_SCORE,&UserTransferScore,sizeof(UserTransferScore));
	//		return true;
	//	}
	//}

	////关闭连接
	//stop();
	//return true;
}

//银行资料
bool CGPInsureMission::onSubInsureInfo(void* data, int size)
{
	//
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagUserInsureInfo * pInsureInfo=pGlobalUserInfo->GetUserInsureInfo();
	tagGlobalUserData* pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	PACKET_AIDE_DATA(data);

	pInsureInfo->wRevenueTake			= packet.read2Byte();
	pInsureInfo->wRevenueTransfer		= packet.read2Byte();
	pInsureInfo->wServerID				= packet.read2Byte();
	pInsureInfo->lUserScore				= packet.read8Byte();
	pInsureInfo->lUserInsure			= packet.read8Byte();
	pInsureInfo->lTransferPrerequisite	= packet.read8Byte();
	pGlobalUserData->dwUserMedal		= packet.read4Byte();
	pGlobalUserData->lRoomCard			= packet.read4Byte();

	//关闭连接
	stop();

	if (mIGPInsureMissionSink)
		mIGPInsureMissionSink->onInsureInfo();

	return true;
}

//银行成功
bool CGPInsureMission::onSubInsureSuccess(void* data, int size)
{
	int baseSize = 4+8+8;
	//效验参数
	ASSERT(size>=baseSize);
	if (size<baseSize) return false;

	//变量定义
	CGlobalUserInfo * pGlobalUserInfo   = CGlobalUserInfo::GetInstance();
	tagUserInsureInfo * pInsureInfo=pGlobalUserInfo->GetUserInsureInfo();

	PACKET_AIDE_DATA(data);
	packet.read4Byte();
	//更新
	pInsureInfo->lUserScore		= packet.read8Byte();
	pInsureInfo->lUserInsure	= packet.read8Byte();
	std::string sDescribe		= packet.readString((size-baseSize)/2);

	//关闭连接
	stop();

	//显示消息
	if (mIGPInsureMissionSink)
		mIGPInsureMissionSink->onInsureSuccess(mMissionType, sDescribe.c_str());
	return true;
}

//银行失败
bool CGPInsureMission::onSubInsureFailure(void* data, int size)
{
	int baseSize = 4;
	//效验参数
	ASSERT(size>=baseSize);
	if (size<baseSize) return false;

	PACKET_AIDE_DATA(data);
	int lResultCode			= packet.read4Byte();
	std::string sDescribe	= packet.readString((size-baseSize)/2);

	//关闭连接
	stop();

	//显示消息
	if (mIGPInsureMissionSink)
		mIGPInsureMissionSink->onInsureFailure(mMissionType, sDescribe.c_str());
	return true;

	////效验参数
	//CMD_GP_UserInsureFailure * pUserInsureFailure=(CMD_GP_UserInsureFailure *)data;
	//ASSERT(size>=(sizeof(CMD_GP_UserInsureFailure)-sizeof(pUserInsureFailure->szDescribeString)));
	//if (size<(sizeof(CMD_GP_UserInsureFailure)-sizeof(pUserInsureFailure->szDescribeString))) 
	//	return false;

	////关闭连接
	//stop();

	////显示消息
	//if (mIGPInsureMissionSink)
	//	mIGPInsureMissionSink->onInsureFailure(mMissionType, pUserInsureFailure->szDescribeString);
	//return true;
}

//操作成功
bool CGPInsureMission::onSubOperateSuccess(void* data, int size)
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
	if (mIGPInsureMissionSink)
		mIGPInsureMissionSink->onInsureSuccess(mMissionType, str.c_str());
	return true;

	////变量定义
	//CMD_GP_OperateSuccess * pOperateSuccess=(CMD_GP_OperateSuccess *)data;

	////效验数据
	//ASSERT(size>=(sizeof(CMD_GP_OperateSuccess)-sizeof(pOperateSuccess->szDescribeString)));
	//if (size<(sizeof(CMD_GP_OperateSuccess)-sizeof(pOperateSuccess->szDescribeString))) return false;

	////变量定义
	//CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	//tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	////关闭连接
	//stop();

	////显示消息
	//if (mIGPInsureMissionSink)
	//	mIGPInsureMissionSink->onInsureSuccess(mMissionType, pOperateSuccess->szDescribeString);

	//return true;
}

// 操作失败
bool CGPInsureMission::onSubOperateFailure(void* data, int size)
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
	if (mIGPInsureMissionSink)
		mIGPInsureMissionSink->onInsureFailure(mMissionType, str.c_str());
	return true;

	////效验参数
	//CMD_GP_OperateFailure * pOperateFailure=(CMD_GP_OperateFailure *)data;
	//ASSERT(size>=(sizeof(CMD_GP_OperateFailure)-sizeof(pOperateFailure->szDescribeString)));
	//if (size<(sizeof(CMD_GP_OperateFailure)-sizeof(pOperateFailure->szDescribeString))) return false;

	////关闭连接
	//stop();

	////显示消息
	//if (mIGPInsureMissionSink)
	//	mIGPInsureMissionSink->onInsureFailure(mMissionType, pOperateFailure->szDescribeString);
	//return true;
}

//操作成功
bool CGPInsureMission::onSubTransferRoomCardSuccess(void* data, int size)
{
	int baseSize = 4 + 4;
	//效验参数
	ASSERT(size >= baseSize);
	if (size<baseSize) return false;

	//变量定义
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();

	PACKET_AIDE_DATA(data);
	packet.read4Byte();
	//更新
	pGlobalUserData->lRoomCard = packet.read4Byte();
	
	std::string sDescribe = packet.readString((size - baseSize) / 2);

	//关闭连接
	stop();

	//显示消息
	if (mIGPInsureMissionSink)
		mIGPInsureMissionSink->onInsureSuccess(mMissionType, sDescribe.c_str());
	return true;
}