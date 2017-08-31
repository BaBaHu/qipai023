#include "CServerItem.h"

//比赛消息
bool CServerItem::OnSocketMainMatch(int sub, void* data, int dataSize)
{
	switch (sub)
	{
		//费用查询
	case SUB_GR_MATCH_FEE:		return OnSocketSubMatchFee(data,dataSize);
		//参赛人数
	case SUB_GR_MATCH_NUM:		return OnSocketSubMatchNum(data,dataSize); 
		//比赛状态
	case SUB_GR_MATCH_STATUS:	return OnSocketSubMatchStatus(data, dataSize);
		//比赛描述
	case SUB_GR_MATCH_DESC:		return OnSocketSubMatchDesc(data, dataSize);
	}
	return true;
}

//比赛费用
bool CServerItem::OnSocketSubMatchFee(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubMatchFee 比赛费用 "));
	//参数效验
	ASSERT(dataSize==sizeof(dword));
	if(dataSize!=sizeof(dword)) return false;

	dword dwMatchFee=*(dword*)data;
	if(dwMatchFee>0)
	{
		char szDescribe[256]={0};
		sprintf(szDescribe,"参赛将扣除报名费 %ld 游戏币，确认要参赛吗?",dwMatchFee);
		PLAZZ_PRINTF("%s\n", szDescribe);
		CGDialog("系统消息", szDescribe, CGDLG_MB_OK|CGDLG_MB_CANCEL,
			[&, dwMatchFee](){
				dword dwMatchFeeT = dwMatchFee;
				SendSocketData(MDM_GR_MATCH,SUB_GR_MATCH_FEE,&dwMatchFeeT,sizeof(dwMatchFeeT));
			},
			nullptr);
	}
	return true;
}

//参赛人数
bool CServerItem::OnSocketSubMatchNum(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubMatchNum 参赛人数 "));
	PACKET_AIDE_DATA(data);

	mTableFrame.mMatchWaittingCount=packet.read4Byte();
	mTableFrame.mMatchTotalUser=packet.read4Byte();
	//mTableFrame.InvalidateRect(0);
	return true;
}

//比赛状态
bool CServerItem::OnSocketSubMatchStatus(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubMatchStatus 比赛状态 "));
	//效验参数
	ASSERT(dataSize==sizeof(byte));
	if(dataSize!=sizeof(byte)) return false;

	mTableFrame.SetMatchStatus(*(byte*)data);

	return true;
}

//比赛描述
bool CServerItem::OnSocketSubMatchDesc(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubMatchDesc 比赛描述 "));
	PACKET_AIDE_DATA(data);

	for (int i = 0; i < 4; ++i)
	{
		strncpy(mTableFrame.mMatchDesc.szTitle[i], packet.readString(16).c_str(), countarray(mTableFrame.mMatchDesc.szTitle[i]));
	}

	for (int i = 0; i < 4; ++i)
	{
		strncpy(mTableFrame.mMatchDesc.szDescribe[i], packet.readString(64).c_str(), countarray(mTableFrame.mMatchDesc.szDescribe[i]));
	}

	mTableFrame.mMatchDesc.crTitleColor = packet.read4Byte();
	mTableFrame.mMatchDesc.crDescribeColor = packet.read4Byte();

	return true;
}
