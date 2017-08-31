#include "CServerItem.h"

//登录消息
bool CServerItem::OnSocketMainLogon(int sub, void* data, int dataSize)
{
	switch (sub)
	{
		//登录成功
	case SUB_GR_LOGON_SUCCESS:	
		return OnSocketSubLogonSuccess(data,dataSize);
		//登录失败
	case SUB_GR_LOGON_FAILURE:	return OnSocketSubLogonFailure(data,dataSize);
		//登录完成
	case SUB_GR_LOGON_FINISH:	return OnSocketSubLogonFinish(data,dataSize);
		//更新提示
	case SUB_GR_UPDATE_NOTIFY:	return OnSocketSubUpdateNotify(data,dataSize);
	}

	return true;
}


//登录成功
bool CServerItem::OnSocketSubLogonSuccess(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubLogonSuccess 登录成功"));

	mIsQuickSitDown = false;

	PACKET_AIDE_DATA(data);

	//玩家属性
	mUserAttribute.dwUserRight=packet.read4Byte();
	mUserAttribute.dwMasterRight=packet.read4Byte();

	//设置状态
	SetServiceStatus(ServiceStatus_RecvInfo);

	if (mIServerItemSink)
		mIServerItemSink->OnGRLogonSuccess();

	return true;
}

//登录失败
bool CServerItem::OnSocketSubLogonFailure(void* data, int dataSize)
{
	//效验数据
	ASSERT(dataSize>=4);
	if (dataSize<4) return false;

	PACKET_AIDE_DATA(data);
	int lErrorCode = packet.read4Byte();
	std::string str = packet.readString((dataSize-4)/2);
	
	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubLogonFailure 登录失败:%s"), str.c_str());
	//关闭连接
	IntermitConnect(true, true);
	
	if (mIServerItemSink)
		mIServerItemSink->OnGRLogonFailure(lErrorCode, str);
	return true;
}

//登录完成
bool CServerItem::OnSocketSubLogonFinish(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubLogonFinish 登录完成"));

	//设置状态
	SetServiceStatus(ServiceStatus_ServiceIng);
		
	mUserAttribute.dwUserID=mMeUserItem->GetUserID();
	mUserAttribute.wChairID=INVALID_CHAIR;
	mUserAttribute.wTableID=INVALID_TABLE;

	//规则判断
	if (CServerRule::IsForfendGameRule(mServerAttribute.dwServerRule)==false)
	{
		//发送规则
		SendUserRulePacket();
	}

	if (mIServerItemSink)
		mIServerItemSink->OnGRLogonFinish();
	return true;
}


//更新提示
bool CServerItem::OnSocketSubUpdateNotify(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubUpdateNotify 更新提示"));

	PACKET_AIDE_DATA(data);
	//升级标志
	byte cbMustUpdatePlaza = packet.readByte();
	byte cbMustUpdateClient = packet.readByte();
	byte cbAdviceUpdateClient = packet.readByte();

	//当前版本
	dword dwCurrentPlazaVersion = packet.read4Byte();
	dword dwCurrentFrameVersion = packet.read4Byte();
	dword dwCurrentClientVersion = packet.read4Byte();

	//大厅更新
	if (cbMustUpdatePlaza==TRUE)
	{
		IntermitConnect(true, true);

		CGDialog("系统消息", 8, CGDLG_MB_OK | CGDLG_MB_CANCEL,nullptr,nullptr);
		return true;
	}

	//游戏更新
	if (cbMustUpdateClient==TRUE)
	{
		IntermitConnect(true, true);

		CGDialog("系统消息", 9, CGDLG_MB_OK | CGDLG_MB_CANCEL,nullptr,nullptr);
		return true;
	}

	//构造提示
	if (cbAdviceUpdateClient!=TRUE)
		return true;

	//构造提示
	char szDescribe[512]={0};
	sprintf(szDescribe,"“%s”已经更新了，我们强烈建议您进行更新，现在进行更新吗?",mGameKind.szKindName);
	std::string s = szDescribe;

	IntermitConnect(true, true);

	CGDialog("系统消息", szDescribe, CGDLG_MB_OK|CGDLG_MB_CANCEL,nullptr,nullptr);
	return true;
}

