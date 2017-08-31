#ifndef _ServerListUI_H_
#define _ServerListUI_H_

#include "cocos2d.h"
#include "../data/ServerListData.h"
USING_NS_CC;

class ServerListUI: public Ref, public IServerListDataSink
{
public:
	static ServerListUI* create(std::string strIp, int iPort);
	//获取服务器列表
	void getServerLists( int nKindID);
	bool enterServerRoom(int kindID, int serverID);
	
private:
	ServerListUI();
	~ServerListUI();
	bool init(std::string strIp, int iPort);
	void initGameKind();
	void updateOnlineInfo(float dt);
	//////////////////////////////////////////////////////////////////////////
	// IServerListDataSink
public:
	//状态通知
public:
	//完成通知
	virtual void OnGameItemFinish();
	//完成通知
	virtual void OnGameKindFinish(uint16 wKindID);
	//更新通知
	virtual void OnGameItemUpdateFinish();

	//更新通知
public:
	//插入通知
	virtual void OnGameItemInsert(CGameListItem * pGameListItem);
	//更新通知
	virtual void OnGameItemUpdate(CGameListItem * pGameListItem);
	//删除通知
	virtual void OnGameItemDelete(CGameListItem * pGameListItem);

	//UI转发
public:
	void onGameItemFinishNofity(Ref* obj);
private:
	std::vector<CGameServerItem*> mServerList;
	CGPLoginMission		mLoginMission;
};

#endif // _ServerListUI_H_