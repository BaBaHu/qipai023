#include "CServerItem.h"

//系统消息
bool CServerItem::OnSocketMainSystem(int sub, void* data, int dataSize)
{
	switch (sub)
	{
		//系统消息
	case SUB_CM_SYSTEM_MESSAGE:	return OnSocketSubSystemMessage(data,dataSize);
		//动作消息
	case SUB_CM_ACTION_MESSAGE:	return OnSocketSubActionMessage(data,dataSize);
	}

	//错误断言
	ASSERT(FALSE);

	return true;
}


//系统消息
bool CServerItem::OnSocketSubSystemMessage(void* data, int dataSize)
{
	PACKET_AIDE_DATA(data);
	word wType = packet.read2Byte();
	word wLength = packet.read2Byte();
	dword nElapse = packet.read4Byte();
	std::string str = packet.readString(wLength);

	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubSystemMessage 系统消息:%s"), str.c_str());

	//关闭游戏
	if (wType&(SMT_CLOSE_ROOM|SMT_CLOSE_LINK|SMT_CLOSE_GAME))
	{
		if (IClientKernel::get())
			IClientKernel::get()->Intermit(str, true);
	}

	//关闭游戏
	if (wType&(SMT_CLOSE_ROOM|SMT_CLOSE_LINK))
	{
		IntermitConnect(true, true);
	}

	//显示消息
	if (wType&SMT_CHAT) 
	{
		if (mIChatSink)
			mIChatSink->InsertSystemChat(str.c_str());
	}

	//弹出消息
	if (wType&SMT_EJECT)
	{
		CGDialog("系统消息", str, CGDLG_MB_OK, nullptr, nullptr);
	}

	//关闭处理
	if ((wType&(SMT_CLOSE_ROOM|SMT_CLOSE_LINK))!=0)
	{
		//时间延迟
		if (mIServerItemSink)
			mIServerItemSink->OnGFServerClose(str);
	}
	else if (wType&SMT_CLOSE_GAME)
	{	//只是关闭游戏时判断是否快速模式
		if (CServerRule::IsAllowQuickMode(mServerAttribute.dwServerRule))
		{
			//时间延迟
			IntermitConnect(true, true);
			if (mIServerItemSink)
				mIServerItemSink->OnGFServerClose(str);
		}
	}

	return true;
}

//动作消息
bool CServerItem::OnSocketSubActionMessage(void* data, int dataSize)
{
	PACKET_AIDE_DATA(data);
	word wType = packet.read2Byte();
	word wLength = packet.read2Byte();
	uint nButtonType = packet.read2Byte();
	std::string str = packet.readString(wLength);

	PLAZZ_PRINTF(("flow->CServerItem::OnSocketSubActionMessage 动作消息:%s"), str.c_str());

	//关闭处理
	if ((wType&(SMT_CLOSE_ROOM|SMT_CLOSE_LINK))!=0)
	{
		IntermitConnect(true, true);
	}

	//弹出消息
	CGDialog("系统消息", str, CGDLG_MB_OK, nullptr, nullptr);
	return true;
	////变量定义
	//CMD_CM_ActionMessage * pActionMessage=(CMD_CM_ActionMessage *)data;
	//word wHeadSize=sizeof(CMD_CM_ActionMessage)-sizeof(pActionMessage->szString);

	////效验参数
	//ASSERT((dataSize>wHeadSize)&&(dataSize>=(wHeadSize+pActionMessage->wLength*sizeof(tchar))));
	//if ((dataSize<=wHeadSize)||(dataSize<(wHeadSize+pActionMessage->wLength*sizeof(tchar)))) return false;

	////关闭处理
	//if ((pActionMessage->wType&(SMT_CLOSE_ROOM|SMT_CLOSE_LINK))!=0)
	//{
	//	IntermitConnect(true, true);

	//	////关闭提示
	//	//m_DlgStatus.HideStatusWindow();
	//}

	////弹出消息
	//CInformation Information;
	//int nResultCode=Information.ShowMessageBox(pActionMessage->szString,MB_ICONINFORMATION);

	////变量定义
	//word wExcursion=wHeadSize+pActionMessage->wLength*sizeof(tchar);

	////提取动作
	//while (wExcursion<dataSize)
	//{
	//	//变量定义
	//	tagActionHead * pActionHead=(tagActionHead *)((byte *)data+wExcursion);

	//	//效验参数
	//	ASSERT((wExcursion+sizeof(tagActionHead))<=dataSize);
	//	ASSERT((wExcursion+sizeof(tagActionHead)+pActionHead->wAppendSize)<=dataSize);

	//	//效验参数
	//	if ((wExcursion+sizeof(tagActionHead))>dataSize) return false;
	//	if ((wExcursion+sizeof(tagActionHead)+pActionHead->wAppendSize)>dataSize) return false;

	//	//动作出来
	//	if (nResultCode==pActionHead->uResponseID)
	//	{
	//		switch (pActionHead->cbActionType)
	//		{
	//		case ACT_BROWSE:	//浏览动作
	//			{
	//				//变量定义
	//				word wDataPos=wExcursion+sizeof(tagActionHead);
	//				tagActionBrowse * pActionBrowse=(tagActionBrowse *)((byte *)data+wDataPos);

	//				//I E 浏览
	//				if (pActionBrowse->cbBrowseType&BRT_IE)
	//				{
	//					ShellExecute(0,T_T("OPEN"),pActionBrowse->szBrowseUrl,0,0,SW_NORMAL);
	//				}

	//				//大厅浏览
	//				if (pActionBrowse->cbBrowseType&BRT_PLAZA)
	//				{
	//					CPlatformFrame::GetInstance()->WebBrowse(pActionBrowse->szBrowseUrl,true);
	//				}

	//				break;
	//			}
	//		case ACT_DOWN_LOAD:	//下载动作
	//			{
	//				//变量定义
	//				word wDataPos=wExcursion+sizeof(tagActionHead);
	//				tagActionDownLoad * pActionDownLoad=(tagActionDownLoad *)((byte *)data+wDataPos);

	//				//I E 下载
	//				if (pActionDownLoad->cbDownLoadMode&DLT_IE)
	//				{
	//					ShellExecute(0,T_T("OPEN"),pActionDownLoad->szDownLoadUrl,0,0,SW_NORMAL);
	//				}

	//				//下载模块
	//				if (pActionDownLoad->cbDownLoadMode&DLT_MODULE)
	//				{
	//					ShellExecute(0,T_T("OPEN"),pActionDownLoad->szDownLoadUrl,0,0,SW_NORMAL);
	//				}

	//				break;
	//			}
	//		}
	//	}

	//	//增加偏移
	//	wExcursion+=(sizeof(tagActionHead)+pActionHead->wAppendSize);
	//}

	////关闭房间
	//if (pActionMessage->wType&SMT_CLOSE_ROOM) PostMessage(WM_COMMAND,IDM_DELETE_SERVER_ITEM,0);

	//return true;
}
