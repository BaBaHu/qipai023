#include "CServerItem.h"
#include "MELog.h"

//状态信息
bool CServerItem::OnSocketMainStatus(int sub, void* data, int dataSize)
{
	switch (sub)
	{
		//桌子信息
	case SUB_GR_TABLE_INFO:		return OnSocketSubStatusTableInfo(data, dataSize);
		//桌子状态
	case SUB_GR_TABLE_STATUS:	return OnSocketSubStatusTableStatus(data, dataSize);
	}

	return true;
}

//桌子信息
bool CServerItem::OnSocketSubStatusTableInfo(void* data, int dataSize)
{
	//MELOG(MELOG_INFO, "flow->CServerItem::OnSocketSubStatusTableInfo 桌子信息 \n");

	//变量定义
	PACKET_AIDE_DATA(data);
	word wTableCount = packet.read2Byte();

	for (int i = 0; i < wTableCount; i++)
	{
		byte cbTableLock=packet.readByte();
		byte cbPlayStatus=packet.readByte();
		mTableFrame.SetTableStatus(i,(cbPlayStatus==TRUE),(cbTableLock==TRUE));
	}

	return true;
}

//桌子状态
bool CServerItem::OnSocketSubStatusTableStatus(void* data, int dataSize)
{
	//MELOG(MELOG_INFO, "flow->CServerItem::OnSocketSubStatusTableStatus 桌子状态 \n");

	PACKET_AIDE_DATA(data);
	word wTableID = packet.read2Byte();
	byte cbTableLock=packet.readByte();
	byte cbPlayStatus=packet.readByte();
	//设置桌子
	mTableFrame.SetTableStatus(wTableID,(cbPlayStatus==TRUE),(cbTableLock==TRUE));

	//设置桌子
	if(cbPlayStatus==TRUE && mMeUserItem->GetTableID()==wTableID && CServerRule::IsAllowAvertCheatMode(mServerAttribute.dwServerRule))
	{
		mTableFrame.SetTableStatus(false);
	}

	return true;
}