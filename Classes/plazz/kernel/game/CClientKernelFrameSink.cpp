#include "CClientKernel.h"

//房间配置
void CClientKernel::OnGFConfigServer(const tagUserAttribute& UserAttribute, const tagServerAttribute& ServerAttribute)
{
	PLAZZ_PRINTF(("flow->CClientKernel::OnGFConfigServer 房间配置"));

	memcpy(&mUserAttribute, &UserAttribute, sizeof(mUserAttribute));
	memcpy(&mServerAttribute, &ServerAttribute, sizeof(mServerAttribute));
}

//配置完成
void CClientKernel::OnGFConfigFinish()
{
	PLAZZ_PRINTF(("flow->CClientKernel::OnGFConfigFinish 配置完成"));
	if (mIClientKernelSink && !mIClientKernelSink->SetupGameClient())
		return;
	SendGameOption();
}

bool CClientKernel::OnGFEventSocket(int main, int sub, void* data, int dataSize)
{
	PLAZZ_PRINTF("flow->CClientKernel::OnGFEventSocket main = %d, sub = %d, dataSize = %d\n", main, sub, dataSize);
	
	//游戏消息
	if (main==MDM_GF_GAME)
	{
		//效验状态
		ASSERT(mIClientKernelSink!=0);
		if (mIClientKernelSink==0) 
			return false;
		return mIClientKernelSink->OnEventGameMessage(sub,data,dataSize);
	}

	//游戏消息
	if (main==MDM_GR_INSURE)
	{
		//PLAZZ_PRINTF("flow->CClientKernel::OnGFEventSocket MDM_GR_INSURE\n");
		//if(mIClientKernelSink)
		//	mIClientKernelSink->OnEventInsureMessage(sub,data,dataSize);

		return true;
	}

	//管理消息
	if (main == MDM_GR_MANAGE)
	{
		PLAZZ_PRINTF("flow->CClientKernel::OnGFEventSocket MDM_GR_MANAGE\n");
		if(mIClientKernelSink)
			mIClientKernelSink->OnEventManageMessage(sub,data,dataSize);
		return true;
	}

	//内核处理
	if (main==MDM_GF_FRAME)
	{
		switch (sub)
		{ 
		case SUB_GF_USER_CHAT:			//用户聊天
			{
				return OnSocketSubUserChat(data,dataSize);
			}
		case SUB_GF_USER_EXPRESSION:	//用户表情
			{
				return OnSocketSubExpression(data,dataSize);
			}
		case SUB_GF_GAME_STATUS:		//游戏状态
			{
				return OnSocketSubGameStatus(data,dataSize);
			}
		case SUB_GF_GAME_SCENE:			//游戏场景
			{
				return OnSocketSubGameScene(data,dataSize);
			}
		case SUB_GF_LOOKON_STATUS:		//旁观状态
			{
				return OnSocketSubLookonStatus(data,dataSize);
			}
		case SUB_GF_SYSTEM_MESSAGE:		//系统消息
			{
				return OnSocketSubSystemMessage(data,dataSize);
			}
		case SUB_GF_ACTION_MESSAGE:		//动作消息
			{
				return OnSocketSubActionMessage(data,dataSize);
			}
		case SUB_GF_USER_READY:			//用户准备
			{
				if(mMeUserItem ==0 || mMeUserItem->GetUserStatus()>=US_READY)
					return true;
				SendUserReady(0,0);
				if (mIClientKernelSink)
					mIClientKernelSink->OnGFMatchWaitTips(0);
				return true;
			}
		case SUB_GR_USER_WAIT_DISTRIBUTE:   //等待提示
			{
				if (mIClientKernelSink)
					mIClientKernelSink->OnGFWaitTips(true);
				return true;
			}
		case SUB_GR_MATCH_INFO:				//比赛信息
			{
				if (!mIClientKernelSink)
					return true;

				//PACKET_AIDE_DATA(data);
				//	
				//tagMatchInfo MatchInfo;
				//u2string sTitle;

				//for (int i = 0; i < 4; ++i)
				//{
				//	sTitle = packet.readUTF16(64);
				//	strncpy(MatchInfo.szTitle[i], u2_8(&sTitle[0]), countarray(MatchInfo.szTitle[i]));
				//}
				//
				//MatchInfo.wGameCount = packet.read2Byte();
				//mIClientKernelSink->OnGFMatchInfo(&MatchInfo);

				PACKET_AIDE_DATA(data);

				tagMatchInfo MatchInfo;
				std::string sTitle;

				for (int i = 0; i < 4; ++i)
				{
					sTitle = packet.readString(64);
					strncpy(MatchInfo.szTitle[i], sTitle.c_str(), countarray(MatchInfo.szTitle[i]));
				}

				MatchInfo.wGameCount = packet.read2Byte();
				mIClientKernelSink->OnGFMatchInfo(&MatchInfo);
				return true;
			}
		case SUB_GR_MATCH_WAIT_TIP:			//等待提示
			{
				if (!mIClientKernelSink)
					return true;

				//设置参数
				if(dataSize!=0)
				{
					//PACKET_AIDE_DATA(data);
					//tagMatchWaitTip MatchWaitTip;
					//MatchWaitTip.lScore = packet.read8Byte();
					//MatchWaitTip.wRank = packet.read2Byte();
					//MatchWaitTip.wCurTableRank = packet.read2Byte();
					//MatchWaitTip.wUserCount = packet.read2Byte();
					//MatchWaitTip.wPlayingTable = packet.read2Byte();
					//u2string str;
					//str.resize(LEN_SERVER+1,'\0');
					//packet.readUTF16(&str[0], LEN_SERVER);
					//strncpy(MatchWaitTip.szMatchName, u2_8(&str[0]), countarray(MatchWaitTip.szMatchName));
					//mIClientKernelSink->OnGFMatchWaitTips(&MatchWaitTip);

					PACKET_AIDE_DATA(data);
					tagMatchWaitTip MatchWaitTip;
					MatchWaitTip.lScore = packet.read8Byte();
					MatchWaitTip.wRank = packet.read2Byte();
					MatchWaitTip.wCurTableRank = packet.read2Byte();
					MatchWaitTip.wUserCount = packet.read2Byte();
					MatchWaitTip.wPlayingTable = packet.read2Byte();
					std::string str = packet.readString(LEN_SERVER);
					strncpy(MatchWaitTip.szMatchName, str.c_str(), countarray(MatchWaitTip.szMatchName));
					mIClientKernelSink->OnGFMatchWaitTips(&MatchWaitTip);
				}
				else
				{
					mIClientKernelSink->OnGFMatchWaitTips(0);
				}
				return true;
			}
		case SUB_GR_MATCH_RESULT:			//比赛结果
			{
				//设置参数
				if (!mIClientKernelSink)
					return true;

				//PACKET_AIDE_DATA(data);

				//tagMatchResult MatchResult;
				//u2string str;
				//str.resize(256+1, '\0');
				//packet.readUTF16(&str[0], 256);
				//strncpy(MatchResult.szDescribe, u2_8(&str[0]), countarray(MatchResult.szDescribe));
				//
				//MatchResult.dwGold = packet.read4Byte();
				//MatchResult.dwMedal = packet.read4Byte();
				//MatchResult.dwExperience = packet.read4Byte();

				//mIClientKernelSink->OnGFMatchWaitTips(0);
				//mIClientKernelSink->OnGFMatchResult(&MatchResult);

				PACKET_AIDE_DATA(data);

				tagMatchResult MatchResult;
				std::string str = packet.readString(256);
				strncpy(MatchResult.szDescribe, str.c_str(), countarray(MatchResult.szDescribe));

				MatchResult.dwGold = packet.read4Byte();
				MatchResult.dwMedal = packet.read4Byte();
				MatchResult.dwExperience = packet.read4Byte();

				mIClientKernelSink->OnGFMatchWaitTips(0);
				mIClientKernelSink->OnGFMatchResult(&MatchResult);
				return true;
			}
		case SUB_MB_FINAL_RESULT:
			{
				if (mIClientKernelSink)
					mIClientKernelSink->OnGFCustomRoomResult(data, dataSize);
				return true;
			}
		case SUB_GR_TABLE_TALK:
			{
				if (mIClientKernelSink)
					mIClientKernelSink->OnGFTableVoiceChat(data, dataSize);
				return true;
			}
		}

		return true;
	}

	return false;
}

//用户聊天
bool CClientKernel::OnSocketSubUserChat(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CClientKernel::OnSocketSubUserChat 用户聊天"));

	int baseSize=2+4+4+4;
	ASSERT(dataSize>=baseSize);
	if(dataSize<baseSize) return false;

	//显示消息
	if (mIChatSink==0) return true;

	//变量定义
	PACKET_AIDE_DATA(data);
	word wChatLength	= packet.read2Byte();
	dword dwChatColor	= packet.read4Byte();
	dword dwSendUserID	= packet.read4Byte();
	dword dwTargetUserID = packet.read4Byte();
	std::string str		= packet.readString(wChatLength);
	
	dwChatColor = ((dwChatColor & 0xFF) << 16) | (dwChatColor >> 8);

	//获取用户
	IClientUserItem * pISendUserItem=mUserManager->SearchUserByUserID(dwSendUserID);
	if (pISendUserItem==0) return true;

	//消息过虑
	if (pISendUserItem!=mMeUserItem)
	{
		//社团变量
		dword dwUserGroupID=pISendUserItem->GetGroupID();
		dword dwMySelfGroupID=mMeUserItem->GetGroupID();

		//社团判断
		bool bSameGroup=false;
		if ((dwMySelfGroupID!=0L)&&(dwMySelfGroupID==dwUserGroupID)) bSameGroup=true;

		//变量定义
		byte cbUserCompanion=pISendUserItem->GetUserCompanion();

		//好友模式
		if ((gGlobalUnits.m_cbMessageMode==MESSAGE_MODE_FRIEND)&&(cbUserCompanion!=CP_FRIEND)&&(bSameGroup==false))
			return true;

		//厌恶模式
		if ((gGlobalUnits.m_cbMessageMode==MESSAGE_MODE_DETEST)&&(cbUserCompanion==CP_DETEST)&&(bSameGroup==false))
			return true;
	}

	//插入消息
	if (dwTargetUserID!=0L)
	{
		//获取用户
		IClientUserItem * pIRecvUserItem=mUserManager->SearchUserByUserID(dwTargetUserID);

		if (pIRecvUserItem!=0)
		{
			//插入消息
			mIChatSink->InsertUserChat(
				pISendUserItem->GetNickName(), pIRecvUserItem->GetNickName(),
				str.c_str(), dwChatColor);
		}
	}
	else 
	{
		//插入消息
		mIChatSink->InsertUserChat(pISendUserItem->GetNickName(),str.c_str(), dwChatColor);
	}

	return true;
}


//用户表情
bool CClientKernel::OnSocketSubExpression(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CClientKernel::OnSocketSubExpression 用户表情"));

	//效验参数
	ASSERT(dataSize==9);
	if (dataSize!=9) return false;

	//显示消息
	if (mIChatSink==0) return true;

	PACKET_AIDE_DATA(data);
	word wItemIndex=packet.read2Byte();
	dword dwSendUserID=packet.read4Byte();
	dword dwTargetUserID=packet.read4Byte();

	//获取用户
	IClientUserItem * pISendUserItem=mUserManager->SearchUserByUserID(dwSendUserID);
	if (pISendUserItem==0) return true;

	//消息过虑
	if (pISendUserItem!=mMeUserItem)
	{
		//社团变量
		dword dwUserGroupID=pISendUserItem->GetGroupID();
		dword dwMySelfGroupID=mMeUserItem->GetGroupID();

		//社团判断
		bool bSameGroup=false;
		if ((dwMySelfGroupID!=0L)&&(dwMySelfGroupID==dwUserGroupID)) bSameGroup=true;

		//变量定义
		byte cbUserCompanion=pISendUserItem->GetUserCompanion();

		//好友模式
		if ((gGlobalUnits.m_cbMessageMode==MESSAGE_MODE_FRIEND)&&(cbUserCompanion!=CP_FRIEND)&&(bSameGroup==false))
		{
			return true;
		}

		//厌恶模式
		if ((gGlobalUnits.m_cbMessageMode==MESSAGE_MODE_DETEST)&&(cbUserCompanion==CP_DETEST)&&(bSameGroup==false))
		{
			return true;
		}
	}

	//插入消息
	if (dwTargetUserID!=0L)
	{
		//获取用户
		IClientUserItem * pIRecvUserItem=mUserManager->SearchUserByUserID(dwTargetUserID);

		//插入消息
		if (pIRecvUserItem!=0)
		{
			mIChatSink->InsertExpression(pISendUserItem->GetNickName(), pIRecvUserItem->GetNickName(),wItemIndex);
		}
	}
	else
	{
		//插入消息
		mIChatSink->InsertExpression(pISendUserItem->GetNickName(),wItemIndex);
	}

	return true;
}

//游戏状态
bool CClientKernel::OnSocketSubGameStatus(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CClientKernel::OnSocketSubGameStatus 游戏状态 "));

	PACKET_AIDE_DATA(data);

	//设置变量
	mGameStatus=packet.readByte();
	mAllowLookon=packet.readByte()!=0;
	return true;
}

//游戏场景
bool CClientKernel::OnSocketSubGameScene(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CClientKernel::OnSocketSubGameScene 游戏场景 "));

	//效验状态
	ASSERT(mMeUserItem!=0);
	if (mMeUserItem==0) return true;

	if (mIClientKernelSink==0)
		return true;

	//场景处理
	bool bLookonUser=(mMeUserItem->GetUserStatus()==US_LOOKON);
	bool bRet = mIClientKernelSink->OnEventSceneMessage(mGameStatus, bLookonUser, data, dataSize);
	if (!bLookonUser && mGameStatus == 0 && mCustTInfo.dwCreateUser>0)
	{
		//自动准备
		SendUserReady(NULL, 0);
	}

	return bRet;
}

//旁观状态
bool CClientKernel::OnSocketSubLookonStatus(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CClientKernel::OnSocketSubLookonStatus 旁观状态 "));

	//消息处理
	if (IsLookonMode()==true)
	{
		byte cbAllowLookon = ((unsigned char*)data)[0];
		
		//事件处理
		mAllowLookon=cbAllowLookon!=0;

		//事件通知
		ASSERT(mMeUserItem!=0);

		if (mIClientKernelSink)
			mIClientKernelSink->OnEventLookonMode(data,dataSize);

		//提示消息
		if (mAllowLookon==true)
		{
			if (mIStringMessageSink!=0)
				mIStringMessageSink->InsertNormalString("您被允许观看玩家游戏");
		}
		else
		{
			if (mIStringMessageSink!=0)
				mIStringMessageSink->InsertNormalString("您被禁止观看玩家游戏");
		}
	}

	return true;
}

//系统消息
bool CClientKernel::OnSocketSubSystemMessage(void* data, int dataSize)
{
	PACKET_AIDE_DATA(data);
	word wType		= packet.read2Byte();
	word wLength	= packet.read2Byte();
	dword nElapse = packet.read4Byte();
	std::string str	= packet.readString(wLength);

	PLAZZ_PRINTF("flow->CClientKernel::OnSocketSubSystemMessage Type= %d, Context=%s",wType, str.c_str());
	//全局消息
	if((wType&SMT_GLOBAL)!=0)
	{
		if (mIClientKernelSink)
			mIClientKernelSink->OnGFGlobalMessage(str.c_str());
	}
	//公告消息
	if ((wType&SMT_NOTICE) != 0)
	{
		if (mIClientKernelSink)
			mIClientKernelSink->OnGFNoticeMessage(str.c_str());
	}
	//滚动消息
	if((wType&SMT_TABLE_ROLL)!=0)
	{
		if(str.find("系统配桌") != std::string::npos)
			mIClientKernelSink->OnGFWaitTips(true);

		if (mIClientKernelSink)
			mIClientKernelSink->OnGFTableMessage(str.c_str());

		if((wType|~SMT_TABLE_ROLL)==0)
			return true;
	}

	//显示消息
	if (wType&SMT_CHAT)
	{
		if (mIStringMessageSink!=0)
			mIStringMessageSink->InsertSystemString(str.c_str());

		if (mIClientKernelSink)
			mIClientKernelSink->OnGFTableMessage(str.c_str());
	}

	//关闭处理
	if ((wType&SMT_CLOSE_GAME)!=0)
	{
		KillGameClock(0);
		//中断连接
		Intermit(str, true);
	}

	//弹出消息
	if (wType&SMT_EJECT)
	{
		CGDialog("系统消息", str, CGDLG_MB_OK,nullptr, nullptr);
	}

	return true;
}

//动作消息
bool CClientKernel::OnSocketSubActionMessage(void* data, int dataSize)
{
	PLAZZ_PRINTF(("flow->CClientKernel::OnSocketSubActionMessage 动作消息"));

	PACKET_AIDE_DATA(data);
	word wType		= packet.read2Byte();
	word wLength	= packet.read2Byte();
	uint nButtonType = packet.read2Byte();
	std::string str	= packet.readString(wLength);

	//关闭处理
	if ((wType&SMT_CLOSE_GAME)!=0)
	{
		KillGameClock(0);
		//中断连接
		Intermit(str, true);
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
	//if ((pActionMessage->wType&SMT_CLOSE_GAME)!=0)
	//{
	//	//中断连接
	//	IntermitConnect();
	//}

	////弹出消息
	//int nResultCode=ShowInformation(pActionMessage->szString,pActionMessage->nButtonType,0);

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
	//					ShellExecute(0,T_T("open"),pActionBrowse->szBrowseUrl,0,0,SW_NORMAL);
	//				}

	//				//大厅浏览
	//				if (pActionBrowse->cbBrowseType&BRT_PLAZA)
	//				{
	//					//						CPlatformFrame::GetInstance()->WebBrowse(pActionBrowse->szBrowseUrl,true,true);
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
	//					ShellExecute(0,T_T("open"),pActionDownLoad->szDownLoadUrl,0,0,SW_NORMAL);
	//				}

	//				//下载模块
	//				if (pActionDownLoad->cbDownLoadMode&DLT_MODULE)
	//				{
	//					ShellExecute(0,T_T("open"),pActionDownLoad->szDownLoadUrl,0,0,SW_NORMAL);
	//				}

	//				break;
	//			}
	//		}
	//	}

	//	//增加偏移
	//	wExcursion+=(sizeof(tagActionHead)+pActionHead->wAppendSize);
	//}

	////关闭房间
	//if (pActionMessage->wType&SMT_CLOSE_GAME) m_pIClientKernelSink->CloseGameClient();

	//return true;
}