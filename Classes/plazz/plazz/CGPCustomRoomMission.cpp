#include "CGPCustomRoomMission.h"
#include "cocos2d.h"
#include "MELog.h"

#define MISSION_CREATE_ROOM	1
#define MISSION_ENTER_ROOM	2
#define MISSION_SELF_ROOM	3

USING_NS_CC;

CGPCustomRoomMission::CGPCustomRoomMission(const std::string& url, int port)
: CSocketMission(url, port)
{
	mMissionType = 0;
	mIGPCustomRoomMissionSink = 0;
}

// 设置回调接口
void CGPCustomRoomMission::setMissionSink(IGPCustomRoomMissionSink* pIGPCustomRoomMissionSink)
{
	mIGPCustomRoomMissionSink = pIGPCustomRoomMissionSink;
}

// 创建房间
void CGPCustomRoomMission::createCustomRoom(const tagGPCreateCustomRoom& cRoom)
{
	memcpy(&mCreateCustomRoom, &cRoom, sizeof(mCreateCustomRoom));
	mMissionType = MISSION_CREATE_ROOM;
	start();
}

// 进入房间
void CGPCustomRoomMission::enterCustomRoom(const tagGPEnterCustomRoom& eRoom)
{
	memcpy(&mEnterCustomRoom, &eRoom, sizeof(mEnterCustomRoom));
	mMissionType = MISSION_ENTER_ROOM;
	start();
}

// 请求自己创建的房间
void  CGPCustomRoomMission::reqSelfCustomRoom()
{
	mMissionType = MISSION_SELF_ROOM;
	start();
}

// 发送创建房间
bool  CGPCustomRoomMission::sendCreateCustomRoomPacket(const tagGPCreateCustomRoom& cRoom)
{
	MELOG(MELOG_INFO, "sendCreateCustomRoomPacket....................................... \n");
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();

// 	CServerListData * pServerListData = CServerListData::shared();
// 	tagGameServer GameServer;
// 
// 	CGameServerItemMap::iterator it = CServerListData::shared()->GetServerItemMapBegin();
// 	CGameServerItem* pGameServerItem = 0;
// 	while ((pGameServerItem = CServerListData::shared()->EmunGameServerItem(it)))
// 	{
// 		if (cRoom.wKindID == pGameServerItem->m_GameServer.wKindID &&  pGameServerItem->m_GameServer.wServerType==10)	// 暂时规定 ServerType 为10的话，为自定义房间
// 		{
// 			break;
// 		}
// 	}
	

	//变量定义
	PACKET_AIDE_SIZE(SIZE_PACK_DATA);

	//打包数据		// 这些数据来至 界面上
	packet.write4Byte(pGlobalUserData->dwUserID);
	packet.writeByte(cRoom.cbRound);
	packet.write2Byte(cRoom.wKindID);
	packet.write8Byte(cRoom.llBaseScore);



	//发送数据
	send(MDM_GP_SERVER_LIST, SUB_C2L_CUSTOMTABLE_CREATE, packet.getBuffer(), packet.getPosition());
	return true;
}

// 发送进入房间
bool CGPCustomRoomMission::sendEnterCustomRoomPacket(const tagGPEnterCustomRoom& eRoom)
{
	MELOG(MELOG_INFO, "sendEnterCustomRoomPacket.......................................... \n");

	//变量定义
	PACKET_AIDE_SIZE(SIZE_PACK_DATA);
	//打包数据
	packet.write4Byte(eRoom.dwRoomVerifyID);
	//发送数据
	send(MDM_GP_SERVER_LIST, SUB_C2L_CUSTOMTABLE_ENTER, packet.getBuffer(), packet.getPosition());
	return true;
}

// 发送请求自己创建的房间
bool CGPCustomRoomMission::sendSelfCustomRoomPacket()
{
	MELOG(MELOG_INFO, "sendSelfCustomRoomPacket.............................................. \n");
	CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();

	//变量定义
	PACKET_AIDE_SIZE(SIZE_PACK_DATA);

	//打包数据
	packet.write4Byte(pGlobalUserData->dwUserID);

	//发送数据
	send(MDM_GP_SERVER_LIST, SUB_C2L_CUSTOMTABLE_LIST, packet.getBuffer(), packet.getPosition());
	return true;
}

void CGPCustomRoomMission::onEventTCPSocketLink()
{
	switch (mMissionType)
	{
		// 创建房间
	case MISSION_CREATE_ROOM:
		sendCreateCustomRoomPacket(mCreateCustomRoom);
		break;
		// 进入房间
	case MISSION_ENTER_ROOM:
		sendEnterCustomRoomPacket(mEnterCustomRoom);
		break;
		// 请求自己创建的房间
	case MISSION_SELF_ROOM:
		sendSelfCustomRoomPacket();
		break;
	}
}

void CGPCustomRoomMission::onEventTCPSocketShut()
{
	PLAZZ_PRINTF("CGPCustomRoomMission::onEventTCPSocketShut\n");
}

void CGPCustomRoomMission::onEventTCPSocketError(int errorCode)
{
	PLAZZ_PRINTF("CGPCustomRoomMission::onEventTCPSocketError code[%d]\n", errorCode);
}

bool CGPCustomRoomMission::onEventTCPSocketRead(int main, int sub, void* data, int size)
{
	PLAZZ_PRINTF("CGPCustomRoomMission::onEventTCPSocketRead main:%d sub:%d size:%d\n", main, sub, size);
	if (main != MDM_GP_SERVER_LIST)
	{
		if (main != MDM_GR_USER)
		{
			return false;
		}
	}

	switch (sub)
	{
		//创建房间
	case SUB_L2C_CUSTOMTABLE_CREATE:	return onSocketCreateCustomRoom(data, size);
		//进入房间
	case SUB_L2C_CUSTOMTABLE_ENTER:		return onSocketEnterCustomRoom(data, size);
		//请求自己创建的房间列表
	//case SUB_L2C_CUSTOMTABLE_LIST:		return onSocketSelfCreateCustomRoom(data, size);
	}

	return false;
}

//创建自定义房间
bool CGPCustomRoomMission::onSocketCreateCustomRoom(void* data, int size)
{
	MELOG(MELOG_INFO, "onSocketCreateCustomRoom.......................................\n");
	
	//获取对象
	ASSERT(CServerListData::shared() != 0);
	CServerListData * pServerListData = CServerListData::shared();

	PACKET_AIDE_DATA(data);
	byte cbResult = packet.readByte();
	
	if (cbResult == 0 || cbResult == eTR_ExistT)
	{
		tagGameServer server;

		server.wKindID = packet.read2Byte();
		server.wNodeID = packet.read2Byte();		// 节点索引
		server.wSortID = packet.read2Byte();		// 排序索引
		server.wServerID = packet.read2Byte();		// 房间索引
		server.wServerPort = packet.read2Byte();
		server.wGameState = packet.read2Byte();
		server.dwOnLineCount = packet.read4Byte();
		server.dwAndroidCount = packet.read4Byte();
		server.dwFullCount = packet.read4Byte();
		server.dwServerRule = packet.read4Byte();
		server.wServerType = packet.read2Byte();

		std::string strServerAddr = packet.readStringFromAnsi_2(sizeof(server.szServerAddr));
		std::string strServerName = packet.readStringFromAnsi_2(sizeof(server.szServerName));

		strncpy(server.szServerAddr, strServerAddr.c_str(), countarray(server.szServerAddr));
		strncpy(server.szServerName, strServerName.c_str(), countarray(server.szServerName));

		server.lCellScore = packet.read4Byte();
		server.lRestrictScore = packet.read8Byte();
		server.lMinTableScore = packet.read8Byte();
		server.lMinEnterScore = packet.read8Byte();
		server.lMaxEnterScore = packet.read8Byte();


		CGlobalUserInfo * pGlobalUserInfo = CGlobalUserInfo::GetInstance();
		tagGlobalUserData * pGlobalUserData = pGlobalUserInfo->GetGlobalUserData();
		pGlobalUserData->dwRoomExtData = server.dwFullCount;
		MELOG(MELOG_INFO, "onSocketCreateCustomRoom....................................%d\n", server.dwFullCount);
		pServerListData->addCustomServer(server);
		if (cbResult == 0)
			pServerListData->addMyCustomTable(server);

		if (mIGPCustomRoomMissionSink)
			mIGPCustomRoomMissionSink->onGPCreateCustomRoomSuccess(server.wServerID, server);
	}
	else
	{
		if (mIGPCustomRoomMissionSink)
			mIGPCustomRoomMissionSink->onGPCreateCustomRoomFailure(cbResult);
	}

	//关闭连接
	stop();
	return true;
}

//进入自定义房间
bool CGPCustomRoomMission::onSocketEnterCustomRoom(void* data, int size)
{
	MELOG(MELOG_INFO, "onSocketEnterCustomRoom...............................\n");
	if (sizeof(tagGameServer) != size) return false;

	//获取对象
	ASSERT(CServerListData::shared() != 0);
	CServerListData * pServerListData = CServerListData::shared();

	PACKET_AIDE_DATA(data);
	std::string str;

	tagGameServer GameServer;
	GameServer.wKindID = packet.read2Byte();
	GameServer.wNodeID = packet.read2Byte();
	GameServer.wSortID = packet.read2Byte();
	GameServer.wServerID = packet.read2Byte();
	GameServer.wServerPort = packet.read2Byte();
	packet.read2Byte();//wGameState
	GameServer.dwOnLineCount = packet.read4Byte();
	packet.read4Byte();//dwAndroidCount
	GameServer.dwFullCount = packet.read4Byte();
	packet.read4Byte();//dwServerRule
	packet.read2Byte();//wServerType

	str = packet.readStringFromAnsi_2(countarray(GameServer.szServerAddr));
	strncpy(GameServer.szServerAddr, str.c_str(), countarray(GameServer.szServerAddr));

	str = packet.readStringFromAnsi_2(countarray(GameServer.szServerName));
	strncpy(GameServer.szServerName, str.c_str(), countarray(GameServer.szServerName));

	GameServer.lCellScore = packet.read4Byte();//lCellScore
	GameServer.lRestrictScore = packet.read8Byte(); //限制积分
	GameServer.lMinTableScore = packet.read8Byte();
	GameServer.lMinEnterScore = packet.read8Byte(); //最低积分
	GameServer.lMaxEnterScore = packet.read8Byte();

	MELOG(MELOG_INFO, "join custom Server:%d server:%s \n", GameServer.dwFullCount, GameServer.szServerName);
	if (GameServer.wKindID == 0 || GameServer.wServerID == 0)
	{
		if (mIGPCustomRoomMissionSink)
			mIGPCustomRoomMissionSink->onGPEnterCustomRoomFailure(31);
		return true;
	}
	pServerListData->addCustomServer(GameServer);

	//显示消息
	if (mIGPCustomRoomMissionSink)
		mIGPCustomRoomMissionSink->onGPEnterCustomRoomSuccess(GameServer.wServerID,GameServer);

	//关闭连接
//	stop();
	return true;
}

//请求自己创建的房间
bool CGPCustomRoomMission::onSocketSelfCreateCustomRoom(void* data, int size)
{
	MELOG(MELOG_INFO, "onSocketSelfCreateCustomRoom...............................\n");
	
	return true;
}