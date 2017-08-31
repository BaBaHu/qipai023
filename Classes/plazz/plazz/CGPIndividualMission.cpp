#include "CGPIndividualMission.h"

//////////////////////////////////////////////////////////////////////////
//#define ADD_PACKET(u8string, type)					\
//{													\
//u2string ucs2 = u8_2s(u8string);					\
//int ucs2len = ucs2_len(&ucs2[0]);					\
//packet.write2Byte(ucs2len*2);						\
//packet.write2Byte(type);							\
//packet.writeUTF16(&ucs2[0], ucs2len);				\
//}

#define ADD_PACKET(u8str, type)						\
{													\
	std::string ucs2 = u2l(u8str);					\
	int ucs2len = u2len(ucs2);						\
	packet.write2Byte(ucs2len*2);					\
	packet.write2Byte(type);						\
	packet.writeString(ucs2, ucs2len);				\
}


//////////////////////////////////////////////////////////////////////////

CGPIndividualMission::CGPIndividualMission(const std::string& url, int port)
: CSocketMission(url, port)
{
	mMissionType = MISSION_INDIVIDUAL_NULL;
	mIGPIndividualMissionSink = 0;
}

// 设置回调接口
void CGPIndividualMission::setMissionSink(IGPIndividualMissionSink* pIGPIndividualMissionSink)
{
	mIGPIndividualMissionSink = pIGPIndividualMissionSink;
}

// 查询个人资料
void CGPIndividualMission::query()
{
	mMissionType = MISSION_INDIVIDUAL_QUERY;
	start();
}

// 修改个人资料
void CGPIndividualMission::modify(const tagModifyIndividual& individual)
{
	mMissionType = MISSION_INDIVIDUAL_MODIFY;
	memcpy(&mModifyIndividual, &individual, sizeof(mModifyIndividual));
	start();
}

void CGPIndividualMission::onEventTCPSocketLink()
{
	PLAZZ_PRINTF("CGPIndividualMission::onEventTCPSocketLink\n");
	
	switch (mMissionType)
	{
		// 查询个人资料
	case MISSION_INDIVIDUAL_QUERY:
		{
			//TEST_NULL
			//变量定义
			CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

			PACKET_AIDE_SIZE(4);
			packet.write4Byte(pGlobalUserData->dwUserID);
			//发送数据
			send(MDM_GP_USER_SERVICE,SUB_GP_QUERY_INDIVIDUAL, packet.getBuffer(),packet.getPosition());

			////变量定义
			//CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			//tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

			////变量定义
			//CMD_GP_QueryIndividual QueryIndividual;
			//zeromemory(&QueryIndividual,sizeof(QueryIndividual));

			////设置变量
			//QueryIndividual.dwUserID=pGlobalUserData->dwUserID;

			////发送数据
			//send(MDM_GP_USER_SERVICE,SUB_GP_QUERY_INDIVIDUAL,&QueryIndividual,sizeof(QueryIndividual));
			break;
		}
		// 修改个人资料
	case MISSION_INDIVIDUAL_MODIFY:
		{
			//TEST_NULL
			//变量定义
			CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	
			//变量定义
			PACKET_AIDE_SIZE(SIZE_PACK_DATA);
			packet.writeByte(mModifyIndividual.cbGender);
			packet.write4Byte(pGlobalUserData->dwUserID);
			packet.writeString(pGlobalUserData->szPassword, LEN_PASSWORD);

			//用户昵称
			if (mModifyIndividual.szNickName[0]!=0 && u8len(mModifyIndividual.szNickName) >= 6)
			{
				PLAZZ_PRINTF("szNickName:%s \n", mModifyIndividual.szNickName);
				ADD_PACKET(mModifyIndividual.szNickName, DTP_GP_UI_NICKNAME);
			}

			//个性签名
			if (mModifyIndividual.szUnderWrite[0]!=0)
			{
				PLAZZ_PRINTF("szUnderWrite:%s \n", mModifyIndividual.szUnderWrite);
				ADD_PACKET(mModifyIndividual.szUnderWrite, DTP_GP_UI_UNDER_WRITE);
			}

			//用户备注
			if (mModifyIndividual.szUserNote[0]!=0)
			{
				ADD_PACKET(mModifyIndividual.szUserNote, DTP_GP_UI_USER_NOTE);
			}

			//真实名字
			if (mModifyIndividual.szCompellation[0]!=0) 
			{
				ADD_PACKET(mModifyIndividual.szCompellation, DTP_GP_UI_COMPELLATION);
			}

			//固定号码
			if (mModifyIndividual.szSeatPhone[0]!=0) 
			{
				ADD_PACKET(mModifyIndividual.szSeatPhone, DTP_GP_UI_SEAT_PHONE);
			}

			//手机号码
			if (mModifyIndividual.szMobilePhone[0]!=0)
			{
				ADD_PACKET(mModifyIndividual.szMobilePhone, DTP_GP_UI_MOBILE_PHONE);
			}

			//Q Q 号码
			if (mModifyIndividual.szQQ[0]!=0) 
			{
				ADD_PACKET(mModifyIndividual.szQQ, DTP_GP_UI_QQ);
			}

			//电子邮件
			if (mModifyIndividual.szEMail[0]!=0) 
			{
				ADD_PACKET(mModifyIndividual.szEMail, DTP_GP_UI_EMAIL);
			}

			//详细地址
			if (mModifyIndividual.szDwellingPlace[0]!=0) 
			{
				ADD_PACKET(mModifyIndividual.szDwellingPlace, DTP_GP_UI_DWELLING_PLACE);
			}

			//发送数据
			send(MDM_GP_USER_SERVICE,SUB_GP_MODIFY_INDIVIDUAL,packet.getBuffer(),packet.getPosition());

			////变量定义
			//byte cbBuffer[SIZE_PACK_DATA];
			//zeromemory(cbBuffer,sizeof(cbBuffer));

			////变量定义
			//CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			//tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

			////变量定义
			//CMD_GP_ModifyIndividual * pModifyIndividual=(CMD_GP_ModifyIndividual *)cbBuffer;
			//CSendPacketHelper SendPacket(cbBuffer+sizeof(CMD_GP_ModifyIndividual),sizeof(cbBuffer)-sizeof(CMD_GP_ModifyIndividual));

			////设置变量
			//pModifyIndividual->cbGender=mModifyIndividual.cbGender;
			//pModifyIndividual->dwUserID=pGlobalUserData->dwUserID;
			//strncpy(pModifyIndividual->szPassword,pGlobalUserData->szPassword,countarray(pModifyIndividual->szPassword));

			////用户昵称
			//if (mModifyIndividual.szNickName[0]!=0 && tstrlen(mModifyIndividual.szNickName) >= 6)
			//{
			//	PLAZZ_PRINTF("szNickName:%s \n"), mModifyIndividual.szNickName);
			//	SendPacket.AddPacket(mModifyIndividual.szNickName,DTP_GP_UI_NICKNAME);
			//}

			////个性签名
			//if (mModifyIndividual.szUnderWrite[0]!=0)
			//{
			//	PLAZZ_PRINTF("szUnderWrite:%s \n"), mModifyIndividual.szUnderWrite);
			//	SendPacket.AddPacket(mModifyIndividual.szUnderWrite,DTP_GP_UI_UNDER_WRITE);
			//}

			////用户备注
			//if (mModifyIndividual.szUserNote[0]!=0)
			//{
			//	SendPacket.AddPacket(mModifyIndividual.szUserNote,DTP_GP_UI_USER_NOTE);
			//}

			////真实名字
			//if (mModifyIndividual.szCompellation[0]!=0) 
			//{
			//	SendPacket.AddPacket(mModifyIndividual.szCompellation,DTP_GP_UI_COMPELLATION);
			//}

			////固定号码
			//if (mModifyIndividual.szSeatPhone[0]!=0) 
			//{
			//	SendPacket.AddPacket(mModifyIndividual.szSeatPhone,DTP_GP_UI_SEAT_PHONE);
			//}

			////手机号码
			//if (mModifyIndividual.szMobilePhone[0]!=0)
			//{
			//	SendPacket.AddPacket(mModifyIndividual.szMobilePhone,DTP_GP_UI_MOBILE_PHONE);
			//}

			////Q Q 号码
			//if (mModifyIndividual.szQQ[0]!=0) 
			//{
			//	SendPacket.AddPacket(mModifyIndividual.szQQ,DTP_GP_UI_QQ);
			//}

			////电子邮件
			//if (mModifyIndividual.szEMail[0]!=0) 
			//{
			//	SendPacket.AddPacket(mModifyIndividual.szEMail,DTP_GP_UI_EMAIL);
			//}

			////详细地址
			//if (mModifyIndividual.szDwellingPlace[0]!=0) 
			//{
			//	SendPacket.AddPacket(mModifyIndividual.szDwellingPlace,DTP_GP_UI_DWELLING_PLACE);
			//}

			////发送数据
			//word wSendSize=sizeof(CMD_GP_ModifyIndividual)+SendPacket.GetDataSize();
			//send(MDM_GP_USER_SERVICE,SUB_GP_MODIFY_INDIVIDUAL,cbBuffer,wSendSize);
			break;
		}
	}

}

void CGPIndividualMission::onEventTCPSocketShut()
{
	PLAZZ_PRINTF("CGPIndividualMission::onEventTCPSocketShut\n");
}

void CGPIndividualMission::onEventTCPSocketError(int errorCode)
{
	PLAZZ_PRINTF("CGPIndividualMission::onEventTCPSocketError code[%d]\n", errorCode);
}

bool CGPIndividualMission::onEventTCPSocketRead(int main, int sub, void* data, int size) 
{
	PLAZZ_PRINTF("CGPIndividualMission::onEventTCPSocketRead main:%d sub:%d size:%d\n", main, sub, size);
	if (main != MDM_GP_USER_SERVICE)
	{
		return false;
	}

	switch (sub)
	{
		//个人信息
	case SUB_GP_USER_INDIVIDUAL:	return onSubUserIndividual(data, size);
		//操作成功
	case SUB_GP_OPERATE_SUCCESS:	return onSubOperateSuccess(data, size);
		//操作失败
	case SUB_GP_OPERATE_FAILURE:	return onSubOperateFailure(data, size);
	}

	return false;
}

// 个人信息
bool CGPIndividualMission::onSubUserIndividual(void* data, int size)
{
	//效验参数
	ASSERT(size>=sizeof(dword));
	if (size<sizeof(dword)) return false;

	//变量定义
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	tagIndividualUserData * pIndividualUserData=pGlobalUserInfo->GetIndividualUserData();

	PACKET_AIDE_DATA(data);
	packet.read4Byte();

	std::string str;

	while(true)
	{
		word wDataSize		= packet.read2Byte();
		word wDataDescribe	= packet.read2Byte();
		if (wDataDescribe == 0) break;
		str = packet.readString(wDataSize/2);

		switch (wDataDescribe)
		{
		case DTP_GP_UI_NICKNAME:		//昵称
			{
				strncpy(pGlobalUserData->szNickName,str.c_str(),countarray(pGlobalUserData->szNickName));
				break;
			}
		case DTP_GP_UI_UNDER_WRITE:		//签名
			{
				strncpy(pGlobalUserData->szUnderWrite,str.c_str(),countarray(pGlobalUserData->szUnderWrite));
				break;
			}
		case DTP_GP_UI_USER_NOTE:		//用户备注
			{
				strncpy(pIndividualUserData->szUserNote,str.c_str(),countarray(pIndividualUserData->szUserNote));
				break;
			}
		case DTP_GP_UI_COMPELLATION:	//真实名字
			{
				strncpy(pIndividualUserData->szCompellation,str.c_str(),countarray(pIndividualUserData->szCompellation));
				break;
			}
		case DTP_GP_UI_SEAT_PHONE:		//固定电话
			{
				strncpy(pIndividualUserData->szSeatPhone,str.c_str(),countarray(pIndividualUserData->szSeatPhone));
				break;
			}
		case DTP_GP_UI_MOBILE_PHONE:	//移动电话
			{
				strncpy(pIndividualUserData->szMobilePhone,str.c_str(),countarray(pIndividualUserData->szMobilePhone));
				break;
			}
		case DTP_GP_UI_QQ:				//Q Q 号码
			{
				strncpy(pIndividualUserData->szQQ,str.c_str(),countarray(pIndividualUserData->szQQ));
				break;
			}
		case DTP_GP_UI_EMAIL:			//电子邮件
			{
				strncpy(pIndividualUserData->szEMail,str.c_str(),countarray(pIndividualUserData->szEMail));
				break;
			}
		case DTP_GP_UI_DWELLING_PLACE:	//联系地址
			{
				strncpy(pIndividualUserData->szDwellingPlace,str.c_str(),countarray(pIndividualUserData->szDwellingPlace));
				break;
			}
		}
	}

	//关闭连接
	stop();

	//通知
	if (mIGPIndividualMissionSink)
		mIGPIndividualMissionSink->onGPIndividualInfo(mMissionType);
	return true;


	////效验参数
	//ASSERT(size>=sizeof(CMD_GP_UserIndividual));
	//if (size<sizeof(CMD_GP_UserIndividual)) return false;

	////变量定义
	//CMD_GP_UserIndividual * pUserIndividual=(CMD_GP_UserIndividual *)data;

	////变量定义
	//CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	//tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	//tagIndividualUserData * pIndividualUserData=pGlobalUserInfo->GetIndividualUserData();

	//PacketAide packet((unsigned char*)data);
	//packet.read4Byte();
	//
	//u2string str;

	//while(true)
	//{
	//	word wDataSize		= packet.read2Byte();
	//	word wDataDescribe	= packet.read2Byte();
	//	if (wDataDescribe == DTP_NULL) break;
	//	str.resize(wDataSize+1, '\0');
	//	packet.readUTF16(&str[0], wDataSize);

	//	switch (wDataDescribe)
	//	{
	//	case DTP_GP_UI_NICKNAME:		//昵称
	//		{
	//			strncpy(pGlobalUserData->szNickName,str.c_str(),countarray(pGlobalUserData->szNickName));
	//			break;
	//		}
	//	case DTP_GP_UI_UNDER_WRITE:		//签名
	//		{
	//			strncpy(pGlobalUserData->szUnderWrite,str.c_str(),countarray(pGlobalUserData->szUnderWrite));
	//			break;
	//		}
	//	case DTP_GP_UI_USER_NOTE:		//用户备注
	//		{
	//			strncpy(pIndividualUserData->szUserNote,str.c_str(),countarray(pIndividualUserData->szUserNote));
	//			break;
	//		}
	//	case DTP_GP_UI_COMPELLATION:	//真实名字
	//		{
	//			strncpy(pIndividualUserData->szCompellation,str.c_str(),countarray(pIndividualUserData->szCompellation));
	//			break;
	//		}
	//	case DTP_GP_UI_SEAT_PHONE:		//固定电话
	//		{
	//			strncpy(pIndividualUserData->szSeatPhone,str.c_str(),countarray(pIndividualUserData->szSeatPhone));
	//			break;
	//		}
	//	case DTP_GP_UI_MOBILE_PHONE:	//移动电话
	//		{
	//			strncpy(pIndividualUserData->szMobilePhone,str.c_str(),countarray(pIndividualUserData->szMobilePhone));
	//			break;
	//		}
	//	case DTP_GP_UI_QQ:				//Q Q 号码
	//		{
	//			strncpy(pIndividualUserData->szQQ,str.c_str(),countarray(pIndividualUserData->szQQ));
	//			break;
	//		}
	//	case DTP_GP_UI_EMAIL:			//电子邮件
	//		{
	//			strncpy(pIndividualUserData->szEMail,str.c_str(),countarray(pIndividualUserData->szEMail));
	//			break;
	//		}
	//	case DTP_GP_UI_DWELLING_PLACE:	//联系地址
	//		{
	//			strncpy(pIndividualUserData->szDwellingPlace,str.c_str(),countarray(pIndividualUserData->szDwellingPlace));
	//			break;
	//		}
	//	}
	//}
	//
	//////变量定义
	////void * pDataBuffer=0;
	////tagDataDescribe DataDescribe;
	////CRecvPacketHelper RecvPacket(pUserIndividual+1,(word)(size-sizeof(CMD_GP_UserIndividual)));

	//////扩展信息
	////while (true)
	////{
	////	pDataBuffer=RecvPacket.GetData(DataDescribe);
	////	if (DataDescribe.wDataDescribe==DTP_NULL) break;
	////	switch (DataDescribe.wDataDescribe)
	////	{
	////	case DTP_GP_UI_NICKNAME:		//昵称
	////		{
	////			strncpy(pGlobalUserData->szNickName,(const tchar*)pDataBuffer,countarray(pGlobalUserData->szNickName));
	////			break;
	////		}
	////	case DTP_GP_UI_UNDER_WRITE:		//签名
	////		{
	////			strncpy(pGlobalUserData->szUnderWrite,(const tchar*)pDataBuffer,countarray(pGlobalUserData->szUnderWrite));
	////			break;
	////		}
	////	case DTP_GP_UI_USER_NOTE:		//用户备注
	////		{
	////			strncpy(pIndividualUserData->szUserNote,(const tchar*)pDataBuffer,countarray(pIndividualUserData->szUserNote));
	////			break;
	////		}
	////	case DTP_GP_UI_COMPELLATION:	//真实名字
	////		{
	////			strncpy(pIndividualUserData->szCompellation,(const tchar*)pDataBuffer,countarray(pIndividualUserData->szCompellation));
	////			break;
	////		}
	////	case DTP_GP_UI_SEAT_PHONE:		//固定电话
	////		{
	////			strncpy(pIndividualUserData->szSeatPhone,(const tchar*)pDataBuffer,countarray(pIndividualUserData->szSeatPhone));
	////			break;
	////		}
	////	case DTP_GP_UI_MOBILE_PHONE:	//移动电话
	////		{
	////			strncpy(pIndividualUserData->szMobilePhone,(const tchar*)pDataBuffer,countarray(pIndividualUserData->szMobilePhone));
	////			break;
	////		}
	////	case DTP_GP_UI_QQ:				//Q Q 号码
	////		{
	////			strncpy(pIndividualUserData->szQQ,(const tchar*)pDataBuffer,countarray(pIndividualUserData->szQQ));
	////			break;
	////		}
	////	case DTP_GP_UI_EMAIL:			//电子邮件
	////		{
	////			strncpy(pIndividualUserData->szEMail,(const tchar*)pDataBuffer,countarray(pIndividualUserData->szEMail));
	////			break;
	////		}
	////	case DTP_GP_UI_DWELLING_PLACE:	//联系地址
	////		{
	////			strncpy(pIndividualUserData->szDwellingPlace,(const tchar*)pDataBuffer,countarray(pIndividualUserData->szDwellingPlace));
	////			break;
	////		}
	////	}
	////}

	////关闭连接
	//stop();

	////通知
	//if (mIGPIndividualMissionSink)
	//	mIGPIndividualMissionSink->onGPIndividualInfo(mMissionType);
	//return true;
}

// 操作成功
bool CGPIndividualMission::onSubOperateSuccess(void* data, int size)
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

	switch (mMissionType)
	{
		// 查询个人资料
	case MISSION_INDIVIDUAL_QUERY:
		{
			break;
		}
		// 修改个人资料
	case MISSION_INDIVIDUAL_MODIFY:
		{
			tagIndividualUserData * pIndividualUserData=pGlobalUserInfo->GetIndividualUserData();

			//帐号资料
			pGlobalUserData->cbGender=mModifyIndividual.cbGender;

			//用户昵称
			if (mModifyIndividual.szNickName[0]!=0 && u8len(mModifyIndividual.szNickName) >= 6)
				strncpy(pGlobalUserData->szNickName,mModifyIndividual.szNickName,countarray(pGlobalUserData->szNickName));

			//个性签名
			if (mModifyIndividual.szUnderWrite[0]!=0)
				strncpy(pGlobalUserData->szUnderWrite,mModifyIndividual.szUnderWrite,countarray(pGlobalUserData->szUnderWrite));

			//详细资料

			//用户备注
			if (mModifyIndividual.szUserNote[0]!=0)
				strncpy(pIndividualUserData->szUserNote,mModifyIndividual.szUserNote,countarray(pIndividualUserData->szUserNote));

			//真实名字
			if (mModifyIndividual.szCompellation[0]!=0) 
				strncpy(pIndividualUserData->szCompellation,mModifyIndividual.szCompellation,countarray(pIndividualUserData->szCompellation));

			//固定号码
			if (mModifyIndividual.szSeatPhone[0]!=0) 
				strncpy(pIndividualUserData->szSeatPhone,mModifyIndividual.szSeatPhone,countarray(pIndividualUserData->szSeatPhone));

			//手机号码
			if (mModifyIndividual.szMobilePhone[0]!=0)
				strncpy(pIndividualUserData->szMobilePhone,mModifyIndividual.szMobilePhone,countarray(pIndividualUserData->szMobilePhone));

			//Q Q 号码
			if (mModifyIndividual.szQQ[0]!=0) 
				strncpy(pIndividualUserData->szQQ,mModifyIndividual.szQQ,countarray(pIndividualUserData->szQQ));

			//电子邮件
			if (mModifyIndividual.szEMail[0]!=0) 
				strncpy(pIndividualUserData->szEMail,mModifyIndividual.szEMail,countarray(pIndividualUserData->szEMail));

			//详细地址
			if (mModifyIndividual.szDwellingPlace[0]!=0) 
				strncpy(pIndividualUserData->szDwellingPlace,mModifyIndividual.szDwellingPlace,countarray(pIndividualUserData->szDwellingPlace));

			break;
		}
	}

	//显示消息
	if (mIGPIndividualMissionSink)
		mIGPIndividualMissionSink->onGPIndividualSuccess(mMissionType, str.c_str());
	return true;

	////变量定义
	//CMD_GP_OperateSuccess * pOperateSuccess=(CMD_GP_OperateSuccess *)data;

	////效验数据
	//ASSERT(size>=(sizeof(CMD_GP_OperateSuccess)-sizeof(pOperateSuccess->szDescribeString)));
	//if (size<(sizeof(CMD_GP_OperateSuccess)-sizeof(pOperateSuccess->szDescribeString))) return false;

	////变量定义
	//CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	//tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//switch (mMissionType)
	//{
	//	// 查询个人资料
	//case MISSION_INDIVIDUAL_QUERY:
	//	{
	//		break;
	//	}
	//	// 修改个人资料
	//case MISSION_INDIVIDUAL_MODIFY:
	//	{
	//		tagIndividualUserData * pIndividualUserData=pGlobalUserInfo->GetIndividualUserData();

	//		//帐号资料
	//		pGlobalUserData->cbGender=mModifyIndividual.cbGender;

	//		//用户昵称
	//		if (mModifyIndividual.szNickName[0]!=0 && tstrlen(mModifyIndividual.szNickName) >= 6)
	//			strncpy(pGlobalUserData->szNickName,mModifyIndividual.szNickName,countarray(pGlobalUserData->szNickName));

	//		//个性签名
	//		if (mModifyIndividual.szUnderWrite[0]!=0)
	//			strncpy(pGlobalUserData->szUnderWrite,mModifyIndividual.szUnderWrite,countarray(pGlobalUserData->szUnderWrite));

	//		//详细资料

	//		//用户备注
	//		if (mModifyIndividual.szUserNote[0]!=0)
	//			strncpy(pIndividualUserData->szUserNote,mModifyIndividual.szUserNote,countarray(pIndividualUserData->szUserNote));

	//		//真实名字
	//		if (mModifyIndividual.szCompellation[0]!=0) 
	//			strncpy(pIndividualUserData->szCompellation,mModifyIndividual.szCompellation,countarray(pIndividualUserData->szCompellation));

	//		//固定号码
	//		if (mModifyIndividual.szSeatPhone[0]!=0) 
	//			strncpy(pIndividualUserData->szSeatPhone,mModifyIndividual.szSeatPhone,countarray(pIndividualUserData->szSeatPhone));

	//		//手机号码
	//		if (mModifyIndividual.szMobilePhone[0]!=0)
	//			strncpy(pIndividualUserData->szMobilePhone,mModifyIndividual.szMobilePhone,countarray(pIndividualUserData->szMobilePhone));

	//		//Q Q 号码
	//		if (mModifyIndividual.szQQ[0]!=0) 
	//			strncpy(pIndividualUserData->szQQ,mModifyIndividual.szQQ,countarray(pIndividualUserData->szQQ));

	//		//电子邮件
	//		if (mModifyIndividual.szEMail[0]!=0) 
	//			strncpy(pIndividualUserData->szEMail,mModifyIndividual.szEMail,countarray(pIndividualUserData->szEMail));

	//		//详细地址
	//		if (mModifyIndividual.szDwellingPlace[0]!=0) 
	//			strncpy(pIndividualUserData->szDwellingPlace,mModifyIndividual.szDwellingPlace,countarray(pIndividualUserData->szDwellingPlace));
	//		
	//		break;
	//	}
	//}

	////关闭连接
	//stop();

	////显示消息
	//if (mIGPIndividualMissionSink)
	//	mIGPIndividualMissionSink->onGPIndividualSuccess(mMissionType, pOperateSuccess->szDescribeString);
	//return true;
}

// 操作失败
bool CGPIndividualMission::onSubOperateFailure(void* data, int size)
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
	if (mIGPIndividualMissionSink)
		mIGPIndividualMissionSink->onGPIndividualFailure(mMissionType, str.c_str());

	return true;

	////效验参数
	//CMD_GP_OperateFailure * pOperateFailure=(CMD_GP_OperateFailure *)data;
	//ASSERT(size>=(sizeof(CMD_GP_OperateFailure)-sizeof(pOperateFailure->szDescribeString)));
	//if (size<(sizeof(CMD_GP_OperateFailure)-sizeof(pOperateFailure->szDescribeString))) return false;

	////关闭连接
	//stop();

	////显示消息
	//if (mIGPIndividualMissionSink)
	//	mIGPIndividualMissionSink->onGPIndividualFailure(mMissionType, pOperateFailure->szDescribeString);

	//return true;
}