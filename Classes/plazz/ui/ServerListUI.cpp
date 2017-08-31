#include "MTNotification.h"
#include "ServerListUI.h"
#include "MECallBackListenerHelper.h"

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
}

ServerListUI* ServerListUI::create(std::string strIp, int iPort)
{
	ServerListUI* pRet = new ServerListUI();
	if (pRet && pRet->init(strIp, iPort))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

ServerListUI::ServerListUI()
: mLoginMission(DEFAULT_IP_ADDRESS, DEFAULT_PORT)
{
	//mLoginMission.setMissionSink(this);
	mServerList.clear();
}

ServerListUI::~ServerListUI()
{
	mLoginMission.setMissionSink(0);
	CServerListData::shared()->SetServerListDataSink(0);
	G_NOTIFY_UNREG("GAME_ITEM_FINISH");
}

bool ServerListUI::init(std::string strIp, int iPort)
{
	mLoginMission.setUrl(strIp, iPort);
	G_NOTIFY_REG("GAME_ITEM_FINISH", ServerListUI::onGameItemFinishNofity);

	CServerListData::shared()->SetServerListDataSink(this);
	initGameKind();
	return true;
}

void ServerListUI::initGameKind()
{
	CGameKindItemMap::iterator it = CServerListData::shared()->GetKindItemMapBegin();
	CGameKindItem* pGameKindItem = 0;
	while ((pGameKindItem = CServerListData::shared()->EmunGameKindItem(it)))
	{
		int ret = 0;
		do
		{
			LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onGameKindBack");
			CC_BREAK_IF(0 == nLuaHandler);
			LuaEngine* pEngine = LuaEngine::getInstance();
			LuaStack* pStack = pEngine->getLuaStack();
			lua_State *tolua_s = pStack->getLuaState();
			lua_settop(tolua_s, 0);
			pStack->pushInt(pGameKindItem->m_GameKind.wKindID);
			pStack->pushString(pGameKindItem->m_GameKind.szKindName);
			ret = pStack->executeFunctionByHandler(nLuaHandler, 2);
		} while (0);
	}
}

//获取服务器列表 这个是有Lua调用 getServerList而来的
void ServerListUI::getServerLists(int nKindID)
{
	mServerList.clear();

	CGameServerItemMap::iterator it = CServerListData::shared()->GetServerItemMapBegin();
	CGameServerItem* pGameServerItem = 0;

	int idx = 0;
	while ((pGameServerItem = CServerListData::shared()->EmunGameServerItem(it)))
	{
		if (nKindID == pGameServerItem->m_pGameKindItem->m_GameKind.wKindID)
		{
			mServerList.push_back(pGameServerItem);

			int ret = 0;
			do
			{
				LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onServerListBack");
				CC_BREAK_IF(0 == nLuaHandler);
				LuaEngine* pEngine = LuaEngine::getInstance();
				LuaStack* pStack = pEngine->getLuaStack();
				lua_State *tolua_s = pStack->getLuaState();
				lua_settop(tolua_s, 0);
				pStack->pushInt(idx++);
				pStack->pushInt(pGameServerItem->m_GameServer.wKindID);
				pStack->pushInt(pGameServerItem->m_GameServer.wServerID);
				pStack->pushString(pGameServerItem->m_GameServer.szServerName);
				pStack->pushInt(pGameServerItem->m_GameServer.lMinTableScore);
				ret = pStack->executeFunctionByHandler(nLuaHandler, 5);
			} while (0);
		}
	}

	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onServerListFinishBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		ret = pStack->executeFunctionByHandler(nLuaHandler, 0);
	} while (0);
}

bool ServerListUI::enterServerRoom(int kindID, int serverID)
{
	G_NOTIFY("CONNECT_SERVER", MTData::create(kindID, serverID));
	return true;
}

void ServerListUI::updateOnlineInfo(float dt)
{
	mLoginMission.updateOnlineInfo();
}

//////////////////////////////////////////////////////////////////////////
// IServerListDataSink
//完成通知
void ServerListUI::OnGameItemFinish()
{
	log("OnGameItemFinish....................................");
	G_NOTIFY_SAFE("GAME_ITEM_FINISH", 0);
} 

//完成通知
void ServerListUI::OnGameKindFinish(uint16 wKindID)
{
}

//更新通知
void ServerListUI::OnGameItemUpdateFinish()
{
}

//插入通知
void ServerListUI::OnGameItemInsert(CGameListItem * pGameListItem)
{
	//构造数据
	switch ((int)(pGameListItem->GetItemGenre()))
	{
	case ItemGenre_Type:		//游戏类型
		{
			break;
		}
	case ItemGenre_Kind:		//游戏种类
		{
			break;
		}
	case ItemGenre_Node:		//游戏节点
		{
			break;
		}
	case ItemGenre_Server:		//游戏房间
		{
			//G_NOTIFY_SAFE("GAME_ITEM_FINISH", 0);
			break;
		}
	case ItemGenre_Page:	//定制子项
		{
			break;
		}
	}
}

//更新通知
void ServerListUI::OnGameItemUpdate(CGameListItem * pGameListItem)
{
	//构造数据
	switch ((int)(pGameListItem->GetItemGenre()))
	{
	case ItemGenre_Type:		//游戏类型
		{
			break;
		}
	case ItemGenre_Kind:		//游戏种类
		{
			break;
		}
	case ItemGenre_Node:		//游戏节点
		{
			break;
		}
	case ItemGenre_Server:		//游戏房间
		{
			//G_NOTIFY_SAFE("GAME_ITEM_FINISH", 0);
			//更新视图
			break;
		}
	case ItemGenre_Page:	//定制子项
		{
			break;
		}
	}
}

//删除通知
void ServerListUI::OnGameItemDelete(CGameListItem * pGameListItem)
{
	//构造数据
	switch ((int)(pGameListItem->GetItemGenre()))
	{
	case ItemGenre_Type:		//游戏类型
		{
			break;
		}
	case ItemGenre_Kind:		//游戏种类
		{
			break;
		}
	case ItemGenre_Node:		//游戏节点
		{
			break;
		}
	case ItemGenre_Server:		//游戏房间
		{
			//G_NOTIFY_SAFE("GAME_ITEM_FINISH", 0);
			break;
		}
	case ItemGenre_Page:	//定制子项
		{
			break;
		}
	}
}


void ServerListUI::onGameItemFinishNofity(Ref* obj)
{
	//setDatas();
}
