#include "MTNotification.h"
#include "../Plazz.h"
#include "MECallBackListenerHelper.h"
#include "../utils/StringData.h"
#include "ClientKernelSink.h"
#include "MELog.h"

#define TAG_WAITING 90086

//////////////////////////////////////////////////////////////////////////
class MTNotificationImp 
	: public Node
	, public IChatSink
	, public IStringMessageSink
	, public IServerItemSink
{
private:
	bool mHasLoaded;
public:
	MTNotificationImp()
	{
		mHasLoaded = false;
		
		G_NOTIFY_REG("LOADING_COMPLETE", MTNotificationImp::loadCompleteNotify);	
		G_NOTIFY_REG("LOGON_COMPLETE", MTNotificationImp::logonCompleteNotify);	

		G_NOTIFY_REG("BACK_TO_SERVER_LIST", MTNotificationImp::backToServerListNofity);		

		G_NOTIFY_REG("CONNECT_SERVER", MTNotificationImp::connectServerNotify);	
		G_NOTIFY_REG("CONNECT_CUSTOM_SERVER", MTNotificationImp::connectCustomServerNotify);
		G_NOTIFY_REG("CHAIR_SIT_DOWN", MTNotificationImp::serverItemChairSitDown);
		G_NOTIFY_REG("NOTICE_MSG", MTNotificationImp::noticeMsgNotify);
	}
	~MTNotificationImp()
	{
		
		G_NOTIFY_UNREG("LOADING_COMPLETE");
		G_NOTIFY_UNREG("LOGON_COMPLETE");
		G_NOTIFY_UNREG("BACK_TO_SERVER_LIST");	
		G_NOTIFY_UNREG("CONNECT_SERVER");
		G_NOTIFY_UNREG("CONNECT_CUSTOM_SERVER");
		G_NOTIFY_UNREG("CHAIR_SIT_DOWN");
		G_NOTIFY_UNREG("NOTICE_MSG");
	}

public:

	//////////////////////////////////////////////////////////////////////////
	
	void loadCompleteNotify(Ref* obj)
	{
		mHasLoaded = true;
		//TODO
	}

	void logonCompleteNotify(Ref* obj)
	{
		//TODO
		int ret = 0;
		do
		{
			LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onLoginBack");
			CC_BREAK_IF(0 == nLuaHandler);
			LuaEngine* pEngine = LuaEngine::getInstance();
			LuaStack* pStack = pEngine->getLuaStack();
			lua_State *tolua_s = pStack->getLuaState();
			lua_settop(tolua_s, 0);
			ret = pStack->executeFunctionByHandler(nLuaHandler, 0);
		} while (0);
	}

	void backToServerListNofity(Ref* obj)
	{
		bool bShowTips = false;
		MTData* data = dynamic_cast<MTData*>(obj);
		if (data != nullptr)
			bShowTips = true;

		//TODO
		int ret = 0;
		do
		{
			LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onBackToServerListBack");
			CC_BREAK_IF(0 == nLuaHandler);
			LuaEngine* pEngine = LuaEngine::getInstance();
			LuaStack* pStack = pEngine->getLuaStack();
			lua_State *tolua_s = pStack->getLuaState();
			lua_settop(tolua_s, 0);
			pStack->pushBoolean(bShowTips);
			ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
		} while (0);
	}

	//////////////////////////////////////////////////////////////////////////
	// 
	// 进入房间动作
	void connectServerNotify(Ref* obj)
	{
		MTData* data = (MTData*)obj;
		// 关闭之前的房间
		if (IServerItem::get())
		{
			IServerItem::get()->IntermitConnect(true, true);
			IServerItem::destory();
		}

		CGameServerItemMap::iterator it = CServerListData::shared()->GetServerItemMapBegin();
		CGameServerItem* pGameServerItem = 0;
		int idx = 0;
		while ((pGameServerItem = CServerListData::shared()->EmunGameServerItem(it)))
		{
			if (data->mData1 == pGameServerItem->m_pGameKindItem->m_GameKind.wKindID && 
				data->mData2 == pGameServerItem->m_GameServer.wServerID)
			{
				break;
			}
		}

		IServerItem::create();
		IServerItem::get()->SetChatSink(this);
		IServerItem::get()->SetServerItemSink(this);
		IServerItem::get()->SetStringMessageSink(this);
		IServerItem::get()->ConnectServer(pGameServerItem, 0, 0);
	}

	void connectCustomServerNotify(Ref* obj)
	{
		MTData* data = (MTData*)obj;
		// 关闭之前的房间
		if (IServerItem::get())
		{
			IServerItem::get()->IntermitConnect(true, true);
			IServerItem::destory();
		}

		CGameServerItem* pGameServerItem = CServerListData::shared()->searchCustomServerByUUID(data->mData1);
		if (pGameServerItem == 0)
		{
			int ret = 0;
			do
			{
				LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onEnterCustomRoomErrorBack");
				CC_BREAK_IF(0 == nLuaHandler);
				LuaEngine* pEngine = LuaEngine::getInstance();
				LuaStack* pStack = pEngine->getLuaStack();
				lua_State *tolua_s = pStack->getLuaState();
				lua_settop(tolua_s, 0);
				pStack->pushInt(32);
				ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
			} while (0);
			return;
		}

		IServerItem::create();
		IServerItem::get()->SetChatSink(this);
		IServerItem::get()->SetServerItemSink(this);
		IServerItem::get()->SetStringMessageSink(this);
		IServerItem::get()->setCustTUUID(data->mData1);
		IServerItem::get()->ConnectServer(pGameServerItem, 0, 0);
	}

	// 坐下动作
	void serverItemChairSitDown(Ref* obj)
	{
		MTData* data = dynamic_cast<MTData*>(obj);
		if (data == 0)
			return;
		IServerItem::get()->PerformSitDownAction(data->mData1, data->mData2, false);
	}

	// 坐下动作
	void pushNoticeMsg(const char* msg)
	{
		int ret = 0;
		do
		{
			LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onNoticeMsgBack");
			CC_BREAK_IF(0 == nLuaHandler);
			LuaEngine* pEngine = LuaEngine::getInstance();
			LuaStack* pStack = pEngine->getLuaStack();
			lua_State *tolua_s = pStack->getLuaState();
			lua_settop(tolua_s, 0);
			pStack->pushString(msg);
			ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
		} while (0);
	}

	void noticeMsgNotify(Ref* obj)
	{
		MTData* data = dynamic_cast<MTData*>(obj);
		if (data == 0)
			return;
		pushNoticeMsg(data->mStr1.c_str());
	}

	//////////////////////////////////////////////////////////////////////////
	// IChatSink
	//////////////////////////////////////////////////////////////////////////
	//表情消息
	//用户表情
	virtual bool InsertExpression(const char* pszSendUser, unsigned int index)
	{
		PLAZZ_PRINTF(("xx->IChatSink::InsertExpression %s 发送表情:%d"), pszSendUser, index);

		////变量定义
		//CExpressionManager * pExpressionManager=CExpressionManager::GetInstance();
		//CExpression * pExpressionItem=pExpressionManager->GetExpressionItem(pUserExpression->wItemIndex);

		////插入表情
		//if (pExpressionItem!=0)
		//{
		//	//获取路径
		//	char szImagePath[MAX_PATH]=TEXT("");
		//	pExpressionItem->GetExpressionPath(szImagePath,CountArray(szImagePath));

		//	//插入消息
		//	const char* pszSendUser=pISendUserItem->GetNickName();
		//	m_ChatMessage.InsertExpression(pszSendUser,szImagePath);
		//}
		return true;
	}

	//用户表情
	virtual bool InsertExpression(const char* pszSendUser, unsigned int index, bool bMyselfString)
	{
		PLAZZ_PRINTF(("xx->IChatSink::InsertExpression %s 发送表情:%d"), pszSendUser, index);
		return true;
	}

	//用户表情
	virtual bool InsertExpression(const char* pszSendUser, const char* pszRecvUser, unsigned int index)
	{
		PLAZZ_PRINTF(("xx->IChatSink::InsertExpression %s 对 %s 发送表情:%d"), pszSendUser, pszRecvUser, index);
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	//聊天消息

	//用户聊天
	virtual bool InsertUserChat(const char* pszSendUser, const char* pszString, unsigned int crColor)
	{
		PLAZZ_PRINTF(("xx->IChatSink::InsertUserChat %s 说:%s"), pszSendUser, pszString);
		return true;
	}
	//用户聊天
	virtual bool InsertUserChat(const char* pszSendUser, const char* pszRecvUser, const char* pszString, unsigned int crColor)
	{
		PLAZZ_PRINTF(("xx->IChatSink::InsertUserChat %s 对 %s 说:%s"), pszSendUser, pszRecvUser, pszString);
		return true;
	}
	//用户私聊
	virtual bool InsertWhisperChat(const char* pszSendUser, const char* pszString, unsigned int crColor, bool bMyselfString)
	{
		PLAZZ_PRINTF(("xx->IChatSink::InsertWhisperChat %s 对你说:%s"), pszSendUser, pszString);
		return true;
	}
	//用户喇叭
	virtual bool InsertUserTrumpet(const char* pszSendUser,const char* pszString,unsigned int crColor)
	{
		PLAZZ_PRINTF(("xx->IChatSink::InsertUserTrumpet %s :%s"), pszSendUser, pszString);
		//pushNoticeMsg(pszString);
		return true;
	}
	//用户喇叭
	virtual bool InsertUserTyphon(const char* pszSendUser,const char* pszString,unsigned int crColor)
	{
		PLAZZ_PRINTF(("xx->IChatSink::InsertUserTyphon %s :%s"), pszSendUser, pszString);
		//pushNoticeMsg(pszString);
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	//系统消息

	//系统消息
	virtual bool InsertSystemChat(const char* pszString)
	{
		PLAZZ_PRINTF(("xx->IChatSink::InsertSystemChat :%s "), pszString);
		//TODO
		//pushNoticeMsg(pszString);
		return true;
	}

	//系统消息
	virtual bool InsertSystemChat(const int idString)
	{
		PLAZZ_PRINTF(("xx->IChatSink::InsertSystemChat :%d "), idString);
		//TODO
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	// IStringMessageSink

	//////////////////////////////////////////////////////////////////////////
	//事件消息
	//进入事件
	virtual bool InsertUserEnter(const char* pszUserName)
	{
		PLAZZ_PRINTF(("xx->IStringMessageSink::InsertUserEnter %s "), pszUserName);
		return true;
	}

	//离开事件
	virtual bool InsertUserLeave(const char* pszUserName)
	{
		PLAZZ_PRINTF(("xx->IStringMessageSink::InsertUserLeave %s "), pszUserName);
		return true;
	}

	//断线事件
	virtual bool InsertUserOffLine(const char* pszUserName)
	{
		PLAZZ_PRINTF(("xx->IStringMessageSink::InsertUserOffLine %s "), pszUserName);
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	//字符消息
	//普通消息(窗口输出)
	virtual bool InsertNormalString(const char* pszString)
	{
		PLAZZ_PRINTF("xx->IStringMessageSink::InsertNormalString %s", pszString);
		return true;
	}
	//系统消息(窗口输出)
	virtual bool InsertSystemString(const char* pszString)
	{
		PLAZZ_PRINTF(("xx->IStringMessageSink::InsertSystemString :%s"), pszString);
		return true;
	}
	
	//公告消息(窗口输出)
	virtual bool InsertAfficheString(const char* pszString)
	{
		PLAZZ_PRINTF(("xx->IStringMessageSink::InsertAfficheString :%s"), pszString);
		return true;
	}

	//喜报消息
	virtual bool InsertGladString(const char* pszContent, const char* pszNickName, const char* pszNum, dword colText, dword colName, dword colNum)
	{
		G_NOTIFY("GLAD_MSG", MTData::create(colText, colName, colNum, pszContent, pszNickName, pszNum));
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	//登陆信息
	//请求失败
	virtual void onGRRequestFailure(const std::string& szDescribeString)
	{
		MELOG(MELOG_INFO, "xx->IServerItemSink::onGRRequestFailure :%s", szDescribeString.c_str());
		//TODO
		int ret = 0;
		do
		{
			LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onSitDownErrorBack");
			CC_BREAK_IF(0 == nLuaHandler);
			LuaEngine* pEngine = LuaEngine::getInstance();
			LuaStack* pStack = pEngine->getLuaStack();
			lua_State *tolua_s = pStack->getLuaState();
			lua_settop(tolua_s, 0);
			pStack->pushString(szDescribeString.c_str());
			ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
		} while (0);
	}

	//登陆成功
	virtual void OnGRLogonSuccess()
	{
		MELOG(MELOG_INFO, "xx->IServerItemSink::OnGRLogonSuccess ");
	}

	//登陆失败
	virtual void OnGRLogonFailure(long lErrorCode, const std::string& sDescribeString)
	{
		MELOG(MELOG_INFO, "xx->IServerItemSink::OnGRLogonFailure :%s", sDescribeString.c_str());
		int ret = 0;
		do
		{
			LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onLoginGameErrorBack");
			CC_BREAK_IF(0 == nLuaHandler);
			LuaEngine* pEngine = LuaEngine::getInstance();
			LuaStack* pStack = pEngine->getLuaStack();
			lua_State *tolua_s = pStack->getLuaState();
			lua_settop(tolua_s, 0);
			pStack->pushString(sDescribeString.c_str());
			ret = pStack->executeFunctionByHandler(nLuaHandler, 1);
		} while (0);
	}

	//登陆完成
	virtual void OnGRLogonFinish()
	{
		MELOG(MELOG_INFO, "xx->IServerItemSink::OnGRLogonFinish ");

		dword dwCustTUUID = IServerItem::get()->getCustTUUID();
		if (dwCustTUUID > 0 && IServerItem::get()->GetMeUserItem() != nullptr)
		{
			if (IServerItem::get()->GetMeUserItem()->GetTableID() == INVALID_TABLE)
			{
				word wTableID = TableIDbyUUID(dwCustTUUID);
				MELOG(MELOG_INFO, "Custom Room PerformSitDownAction %d\n", wTableID);
				IServerItem::get()->PerformSitDownAction(wTableID, INVALID_CHAIR, false);
			}
			else
			{
				word wTableID = IServerItem::get()->GetMeUserItem()->GetTableID();
				word wChairID = IServerItem::get()->GetMeUserItem()->GetChairID();
				MELOG(MELOG_INFO, "Custom Room =============================== %d, %d\n", wTableID, wChairID);
				IServerItem::get()->OnRecoveryGame();
			}
			return;
		}

		//TODO
		int ret = 0;
		do
		{
			LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onLoginGameBack");
			CC_BREAK_IF(0 == nLuaHandler);
			LuaEngine* pEngine = LuaEngine::getInstance();
			LuaStack* pStack = pEngine->getLuaStack();
			lua_State *tolua_s = pStack->getLuaState();
			lua_settop(tolua_s, 0);
			pStack->pushInt(IServerItem::get()->GetServerAttribute().wKindID);
			pStack->pushInt(IServerItem::get()->GetServerAttribute().wServerID);
			ret = pStack->executeFunctionByHandler(nLuaHandler, 2);
		} while (0);
	}

	//////////////////////////////////////////////////////////////////////////
	//配置信息

	//列表配置
	virtual void OnGRConfigColumn()
	{
		PLAZZ_PRINTF(("xx->IServerItemSink::OnGRConfigColumn 列表配置"));
	}
	//房间配置
	virtual void OnGRConfigServer() 
	{
		PLAZZ_PRINTF(("xx->IServerItemSink::OnGRConfigServer 房间配置"));
	}
	//道具配置
	virtual void OnGRConfigProperty()
	{
		PLAZZ_PRINTF(("xx->IServerItemSink::OnGRConfigProperty 道具配置"));
	}
	//玩家权限配置
	virtual void OnGRConfigUserRight() 
	{
		PLAZZ_PRINTF(("xx->IServerItemSink::OnGRConfigUserRight 玩家权限配置"));
	}

	//配置完成
	virtual void OnGRConfigFinish()
	{
		PLAZZ_PRINTF(("xx->IServerItemSink::OnGRConfigFinish 配置完成"));
	}

	//////////////////////////////////////////////////////////////////////////
	//用户信息

	//用户进入
	virtual void OnGRUserEnter(IClientUserItem* pIClientUserItem)
	{
		PLAZZ_PRINTF(("xx->IServerItemSink::OnGRUserEnter 用户进入:%s"), pIClientUserItem->GetNickName());
	}

	//用户更新
	virtual void OnGRUserUpdate(IClientUserItem* pIClientUserItem)
	{
		PLAZZ_PRINTF(("xx->IServerItemSink::OnGRUserUpdate 用户更新:%s"), pIClientUserItem->GetNickName());
		if (pIClientUserItem == IServerItem::get()->GetMeUserItem())
			G_NOTIFY("USER_SCORE", 0);
	}
	//用户删除
	virtual void OnGRUserDelete(IClientUserItem* pIClientUserItem)
	{
		PLAZZ_PRINTF(("xx->IServerItemSink::OnGRUserDelete 用户删除:%s"), pIClientUserItem->GetNickName());
	}

	///////////////////////////////////////////////z///////////////////////////
	//框架消息

	//房间退出
	virtual void OnGFServerClose(const std::string& szMessage)
	{	
		MELOG(MELOG_INFO, "xx->IServerItemSink::OnGFServerClose 房间退出:%s", szMessage.c_str());
		G_NOTIFY("BACK_TO_SERVER_LIST", MTData::create(0, 0, 0, szMessage));
	}

	//游戏退出
	virtual void OnGFGameClose(const std::string& sInfo, bool bExitGame)
	{	
		PLAZZ_PRINTF(("xx->IServerItemSink::OnGFGameClose %s , %d"), sInfo.c_str(), bExitGame);
		if (IServerItem::get()->isCustomServer())
		{
			//TODO
			G_NOTIFY("BACK_TO_SERVER_LIST", 0);
		}
		else
		{
			//TODO
			int ret = 0;
			do
			{
				LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onBackToTableBack");
				CC_BREAK_IF(0 == nLuaHandler);
				LuaEngine* pEngine = LuaEngine::getInstance();
				LuaStack* pStack = pEngine->getLuaStack();
				lua_State *tolua_s = pStack->getLuaState();
				lua_settop(tolua_s, 0);
				ret = pStack->executeFunctionByHandler(nLuaHandler, 0);
			} while (0);
		}
	}

	//创建游戏内核
	virtual IClientKernelSink* CreateKernelSink()
	{
		ClientKernelSink::GetInstance()->Release();
		return ClientKernelSink::GetInstance();
	}
}; // MTNotificationImp


//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// 多线程共享消息队列

//////////////////////////////////////////////////////////////////////////
// 队列锁
class MTQueueLocker  
{  
	std::mutex* _mutex;  

public:  
	MTQueueLocker(std::mutex* aMutex) : _mutex(aMutex)  
	{  
		_mutex->lock();
	}  
	~MTQueueLocker()
	{  
		_mutex->unlock();
	}  
}; // MTQueueLocker

#define MTQueueLock(mutex) MTQueueLocker __locker__(mutex) 

//////////////////////////////////////////////////////////////////////////

MTNotification* MTNotification::msInstance = 0;

MTNotification* MTNotification::shared()
{
	if (msInstance==0)
		msInstance = new MTNotification();
	return msInstance;
}

void MTNotification::purge()
{
	CSocket::purge();
	if (msInstance)
		delete msInstance;
	msInstance = 0;
}

//////////////////////////////////////////////////////////////////////////

MTNotification::MTNotification()
{
	mImp = new MTNotificationImp();
	mReceiveQueue = &mDataQueues1;
	mNotifyQueue = &mDataQueues2; 
}

MTNotification::~MTNotification()
{
	delete mImp;

	{
		MTQueueLock(&mDataMutex);

		while (!mDataQueues1.empty())
		{
			MTNotifyData& mtData = mDataQueues1.front();
			CC_SAFE_RELEASE(mtData.obj);
			mDataQueues1.pop_front();
		}

		while (!mDataQueues2.empty())
		{
			MTNotifyData& mtData = mDataQueues2.front();
			CC_SAFE_RELEASE(mtData.obj);
			mDataQueues2.pop_front();
		}

		mReceiveQueue = 0;
		mNotifyQueue = 0;
	}
}

void MTNotification::postNotify(const std::string& name, Ref* obj)
{
	MTNotifyData mtData;
	mtData.name = name;
	mtData.obj  = obj;
	CC_SAFE_RETAIN(obj);
	MTQueueLock(&mDataMutex);
	mReceiveQueue->push_back(mtData);
}

void MTNotification::post(float dt)
{
	CSocket::post();
	
	{
		MTQueueLock(&mDataMutex);
		std::list<MTNotifyData>* tmp = mReceiveQueue;
		mReceiveQueue = mNotifyQueue;
		mNotifyQueue = tmp;
	}

	while (!mNotifyQueue->empty())
	{
		MTNotifyData& mtData = mNotifyQueue->front();
		G_NOTIFY(mtData.name.c_str(), mtData.obj);
		CC_SAFE_RELEASE(mtData.obj);
		mNotifyQueue->pop_front();
	}
}