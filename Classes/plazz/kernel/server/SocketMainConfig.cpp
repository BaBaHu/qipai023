#include "CServerItem.h"

//配置信息
bool CServerItem::OnSocketMainConfig(int sub, void* data, int dataSize)
{
	switch (sub)
	{
		//列表配置
	case SUB_GR_CONFIG_COLUMN:		return OnSocketSubConfigColumn(data, dataSize);
		//房间配置
	case SUB_GR_CONFIG_SERVER:		return OnSocketSubConfigServer(data, dataSize);
		//道具配置
	case SUB_GR_CONFIG_PROPERTY:	return OnSocketSubConfigProperty(data, dataSize);
		//配置玩家权限	
	case SUB_GR_CONFIG_USER_RIGHT:	return OnSocketSubConfigUserRight(data, dataSize);
		//配置完成
	case SUB_GR_CONFIG_FINISH:		return OnSocketSubConfigFinish(data, dataSize);	
	}

	//错误断言
	//ASSERT(FALSE);
	return true;
}

//列表配置
bool CServerItem::OnSocketSubConfigColumn(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubConfigColumn 列表配置 "));

	//变量定义
	PACKET_AIDE_DATA(data);
	byte cbColumnCount = packet.readByte();

	for (int i = 0; i < cbColumnCount; ++i)
	{
		//tagColumnItem ColumnItem;
		//ColumnItem.cbColumnWidth = packet.readByte();
		//ColumnItem.cbDataDescribe = packet.readByte();
		//strncpy(ColumnItem.szColumnName, packet.readString(16).c_str(), CountArray(ColumnItem.szColumnName));
	}

	if (mIServerItemSink)
		mIServerItemSink->OnGRConfigColumn();

	return true;

	////变量定义
	//CMD_GR_ConfigColumn * pConfigColumn=(CMD_GR_ConfigColumn *)data;
	//word wHeadSize=sizeof(CMD_GR_ConfigColumn)-sizeof(pConfigColumn->ColumnItem);

	////效验参数
	//ASSERT((wHeadSize+pConfigColumn->cbColumnCount*sizeof(pConfigColumn->ColumnItem[0]))==dataSize);
	//if ((wHeadSize+pConfigColumn->cbColumnCount*sizeof(pConfigColumn->ColumnItem[0]))!=dataSize) return false;

	//////保存信息
	////m_cbColumnCount=__min(pConfigColumn->cbColumnCount,CountArray(m_ColumnItem));
	////memcpy(m_ColumnItem,pConfigColumn->ColumnItem,sizeof(tagColumnItem)*m_cbColumnCount);

	//////设置列表
	////m_UserListControl.SetColumnDescribe(pConfigColumn->ColumnItem,pConfigColumn->cbColumnCount);
	//
	//if (mIServerItemSink)
	//	mIServerItemSink->OnGRConfigColumn();

	//return true;
}

//房间配置
bool CServerItem::OnSocketSubConfigServer(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubConfigServer 房间配置 "));

	//效验数据
	ASSERT(dataSize==10);
	if (dataSize<10) return false;

	PACKET_AIDE_DATA(data);

	//房间属性
	mServerAttribute.wTableCount=packet.read2Byte();
	mServerAttribute.wChairCount=packet.read2Byte();
	mServerAttribute.wServerType=packet.read2Byte();
	mServerAttribute.dwServerRule=packet.read4Byte();
	//m_UserListControl.SetServerRule(m_dwServerRule);

	if (!mTableFrame.ConfigTableFrame(
		mServerAttribute.wTableCount,
		mServerAttribute.wChairCount,
		mServerAttribute.dwServerRule,
		mServerAttribute.wServerType,
		mServerAttribute.wServerID))
	{
		IntermitConnect(true, true);
		return false;
	}

	if (mIServerItemSink)
		mIServerItemSink->OnGRConfigServer();

	return true;
}

//道具配置
bool CServerItem::OnSocketSubConfigProperty(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubConfigProperty 道具配置 "));

	//变量定义
	PACKET_AIDE_DATA(data);
	byte cbPropertyCount=packet.readByte();

	for (int i = 0; i < cbPropertyCount; ++i)
	{
		tagPropertyInfo PropertyInfo;
		PropertyInfo.wIndex			= packet.read2Byte();
		PropertyInfo.wDiscount		= packet.read2Byte();
		PropertyInfo.wIssueArea		= packet.read2Byte();
		PropertyInfo.lPropertyGold	= packet.read8Byte();
		PropertyInfo.dPropertyCash	= packet.read8Byte();
		PropertyInfo.lSendLoveLiness = packet.read8Byte();
		PropertyInfo.lRecvLoveLiness = packet.read8Byte();
	}

	if (mIServerItemSink)
		mIServerItemSink->OnGRConfigProperty();

	return true;

	////变量定义
	//CMD_GR_ConfigProperty * pConfigProperty=(CMD_GR_ConfigProperty *)data;
	//word wHeadSize=sizeof(CMD_GR_ConfigProperty)-sizeof(pConfigProperty->PropertyInfo);

	////效验参数
	//ASSERT((wHeadSize+pConfigProperty->cbPropertyCount*sizeof(pConfigProperty->PropertyInfo[0]))==dataSize);
	//if ((wHeadSize+pConfigProperty->cbPropertyCount*sizeof(pConfigProperty->PropertyInfo[0]))!=dataSize) return false;

	////保存信息
	////m_cbPropertyCount=__min(pConfigProperty->cbPropertyCount,CountArray(m_PropertyInfo));
	////memcpy(m_PropertyInfo,pConfigProperty->PropertyInfo,sizeof(tagPropertyInfo)*m_cbPropertyCount);

	////设置道具
	////m_GamePropertyCtrl.SetGamePropertyInfo(m_PropertyInfo,m_cbPropertyCount,PT_ISSUE_AREA_SERVER);
	//
	//if (mIServerItemSink)
	//	mIServerItemSink->OnGRConfigProperty();

	//return true;
}

//配置玩家权限	
bool CServerItem::OnSocketSubConfigUserRight(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubConfigUserRight 配置玩家权限 "));

	PACKET_AIDE_DATA(data);
	//玩家权限
	mUserAttribute.dwUserRight=packet.read4Byte();
	if (mIServerItemSink)
		mIServerItemSink->OnGRConfigUserRight();

	return true;
}

//配置完成
bool CServerItem::OnSocketSubConfigFinish(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubConfigFinish 配置玩家权限 "));
	if (mIServerItemSink)
		mIServerItemSink->OnGRConfigFinish();
	return true;
}
