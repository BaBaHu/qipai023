#ifndef _CServerItem_H_
#define _CServerItem_H_

#include "../../Plazz.h"
#include "../../network/ISocketEngine.h"
#include "../user/ClientUserManager.h"
#include "IServerItem.h"
#include "TableFrame.h"
#include "../../df/DynamicPack.h"

class CUserManager;

class CServerItem 
	: public IServerItem
	, public IUserManagerSink
	, public ISocketEngineSink
{

public:
	CServerItem();
	~CServerItem();
	//////////////////////////////////////////////////////////////////////////
	// IServerItem
	//////////////////////////////////////////////////////////////////////////
	//配置接口
public:
	//设置接口
	virtual bool SetServerItemSink(IServerItemSink* pIServerItemSink);
	//设置接口
	virtual bool SetChatSink(IChatSink* pIChatSink);
	//设置接口
	virtual bool SetStringMessageSink(IStringMessageSink* pIStringMessageSink);
	//配置房间
	virtual bool SetServerAttribute(CGameServerItem * pGameServerItem,word wAVServerPort,dword dwAVServerAddr);

	//连接接口
public:
	//初始化房间
	virtual bool ConnectServer(CGameServerItem * pGameServerItem,word wAVServerPort,dword dwAVServerAddr);
	//中断连接
	virtual bool IntermitConnect(bool force, bool bExitGame = true);
	
	//属性接口
public:
	//用户属性
	virtual const tagUserAttribute& GetUserAttribute() const;
	//房间属性
	virtual const tagServerAttribute&  GetServerAttribute() const;
	//服务状态
	virtual enServiceStatus GetServiceStatus();
	//是否服务状态
	bool IsService();
	//设置状态
	void SetServiceStatus(enServiceStatus ServiceStatus);
	//自己状态
	bool IsPlayingMySelf();
	//自己状态
	int GetUserStatus();
	//是否自定义房间
	bool isCustomServer() const;
	//设置自定义房间
	void setCustTUUID(dword dwUUID) { m_dwCustTUUID = dwUUID; }
	//获取自定义房间
	dword getCustTUUID(){ return m_dwCustTUUID; }
	//用户接口
public:
	//自己位置
	virtual word GetMeChairID();
	//自己位置
	virtual IClientUserItem * GetMeUserItem();
	//游戏用户
	virtual IClientUserItem * GetTableUserItem(word wChariID);
	//查找用户
	virtual IClientUserItem * SearchUserByUserID(dword dwUserID);
	//查找用户
	virtual IClientUserItem * SearchUserByGameID(dword dwGameID);
	//查找用户
	virtual IClientUserItem * SearchUserByNickName(const char* szNickName);
	//获取桌子信息
	virtual ITableFrame * GetTableFrame();
	//设置手机用户
	virtual void SetMobileUser(bool bMobile);
	//获取手机用户
	virtual bool GetMobileUser();
	//网络接口
public:
	//发送函数
	virtual bool SendSocketData(word wMainCmdID, word wSubCmdID);
	//发送函数
	virtual bool SendSocketData(word wMainCmdID, word wSubCmdID, void * data, word dataSize);

	//网络命令
public:
	//发送登录
	virtual bool SendLogonPacket();
	//发送规则
	virtual bool SendUserRulePacket();
	//发送旁观
	virtual bool SendLookonPacket(word wTableID, word wChairID);
	//发送坐下
	virtual bool SendSitDownPacket(word wTableID, word wChairID, const char* lpszPassword=0);
	//发送起立
	virtual bool SendStandUpPacket(word wTableID, word wChairID, byte cbForceLeave);
	//发送表情
	virtual bool SendExpressionPacket(dword dwTargetUserID, word wItemIndex);
	//发送聊天
	virtual bool SendUserChatPacket(dword dwTargetUserID, const char* pszChatString, dword dwColor);
	//发送刷新桌子
	virtual bool SendRefreshTabePacket(word wTableIdx);

	//动作处理
public:
	//查找桌子
	virtual bool SearchGameTable(tagSearchTable & SearchTable);
	//执行快速加入
	virtual bool PerformQuickSitDown();
	//更换位置
	virtual bool PerformChangeChair();
	//执行刷新桌子
	virtual bool PerformRefreshTabe(word wTableIdx);
	//执行旁观
	virtual bool PerformLookonAction(word wTableID, word wChairID);
	//执行起立
	virtual bool PerformStandUpAction(word wTableID, word wChairID);
	//执行坐下
	virtual bool PerformSitDownAction(word wTableID, word wChairID, bool bEfficacyPass);
	//执行购买
	virtual bool PerformBuyProperty(byte cbRequestArea,const char* pszNickName, word wItemCount, word wPropertyIndex);

	//内部函数
protected:
	//聊天效验
	bool EfficacyUserChat(const char* pszChatString, word wExpressionIndex);
	//桌子效验
	bool EfficacyTableRule(word wTableID, word wChairID, bool bReqLookon, char strDescribe[256]);

	//////////////////////////////////////////////////////////////////////////
	// IUserManagerSink
	//////////////////////////////////////////////////////////////////////////
public:
	virtual void OnUserItemAcitve(IClientUserItem* pIClientUserItem);
	virtual void OnUserItemDelete(IClientUserItem* pIClientUserItem);
	virtual void OnUserFaceUpdate(IClientUserItem* pIClientUserItem);
	virtual void OnUserCustomTableUpdate(IClientUserItem* pIClientUserItem);
	virtual void OnUserItemUpdate(IClientUserItem* pIClientUserItem, const tagUserScore& LastScore);
	virtual void OnUserItemUpdate(IClientUserItem* pIClientUserItem, const tagUserStatus& LastStatus);
	virtual void OnUserItemUpdate(IClientUserItem* pIClientUserItem, const tagUserAttrib & UserAttrib);

	//////////////////////////////////////////////////////////////////////////
	// ISocketEngineSink
	//////////////////////////////////////////////////////////////////////////
public:
	virtual void onEventTCPSocketLink();
	virtual void onEventTCPSocketShut();
	virtual void onEventTCPSocketError(int errorCode);
	virtual bool onEventTCPSocketRead(int main, int sub, void* data, int dataSize);

	//////////////////////////////////////////////////////////////////////////
	//登录消息
	bool OnSocketMainLogon(int sub, void* data, int dataSize);
	//登录成功
	bool OnSocketSubLogonSuccess(void* data, int dataSize);
	//登录失败
	bool OnSocketSubLogonFailure(void* data, int dataSize);
	//登录完成
	bool OnSocketSubLogonFinish(void* data, int dataSize);
	//更新提示
	bool OnSocketSubUpdateNotify(void* data, int dataSize);
	
	//////////////////////////////////////////////////////////////////////////
	//配置信息
	bool OnSocketMainConfig(int sub, void* data, int dataSize);
	//列表配置
	bool OnSocketSubConfigColumn(void* data, int dataSize);
	//房间配置
	bool OnSocketSubConfigServer(void* data, int dataSize);
	//道具配置
	bool OnSocketSubConfigProperty(void* data, int dataSize);
	//配置玩家权限	
	bool OnSocketSubConfigUserRight(void* data, int dataSize);
	//配置完成
	bool OnSocketSubConfigFinish(void* data, int dataSize);

	//////////////////////////////////////////////////////////////////////////
	//用户信息
	bool OnSocketMainUser(int sub, void* data, int dataSize);
	//请求失败
	bool OnSocketSubRequestFailure(void* data, int dataSize);
	//邀请玩家
	bool OnSocketSubUserInvite(void* data, int dataSize);
	//等待分配
	bool OnSocketSubWaitDistribute(void* data, int dataSize);
	//用户进入
	bool OnSocketSubUserEnter(void* data, int dataSize);
	//用户积分
	bool OnSocketSubUserScore(void* data, int dataSize);
	//用户状态
	bool OnSocketSubUserStatus(void* data, int dataSize);
	//用户聊天
	bool OnSocketSubUserChat(void* data, int dataSize);
	//用户表情
	bool OnSocketSubExpression(void* data, int dataSize);
	//用户私聊
	bool OnSocketSubWisperUserChat(void* data, int dataSize);
	//私聊表情
	bool OnSocketSubWisperExpression(void* data, int dataSize);
	//道具成功
	bool OnSocketSubPropertySuccess(void* data, int dataSize);
	//道具失败
	bool OnSocketSubPropertyFailure(void* data, int dataSize);
	//道具效应
	bool OnSocketSubPropertyEffect(void* data, int dataSize);
	//道具消息
	bool OnSocketSubPropertyMessage(void* data, int dataSize);
	//道具喇叭
	bool OnSocketSubPropertyTrumpet(void* data, int dataSize);
	//喜报消息
	bool OnSocketSubGladMessage(void* data, int dataSize);
	//低保信息
	bool OnGameGuaranteeing(void *pData, int wDataSize);
	//更新自定义房间信息
	bool OnUpdateCustTInfo(void *pData, int wDataSize);

	//////////////////////////////////////////////////////////////////////////
	//状态信息
	bool OnSocketMainStatus(int sub, void* data, int dataSize);
	//桌子信息
	bool OnSocketSubStatusTableInfo(void* data, int dataSize);
	//桌子状态
	bool OnSocketSubStatusTableStatus(void* data, int dataSize);

	//////////////////////////////////////////////////////////////////////////
	//银行消息
	bool OnSocketMainInsure(int sub, void* data, int dataSize);

	//////////////////////////////////////////////////////////////////////////
	//管理消息
	bool OnSocketMainManager(int sub, void* data, int dataSize);

	//////////////////////////////////////////////////////////////////////////
	//系统消息
	bool OnSocketMainSystem(int sub, void* data, int dataSize);
	//系统消息
	bool OnSocketSubSystemMessage(void* data, int dataSize);
	//动作消息
	bool OnSocketSubActionMessage(void* data, int dataSize);

	//////////////////////////////////////////////////////////////////////////
	//游戏消息,框架消息
	bool OnSocketMainGameFrame(int main,int sub, void* data, int dataSize);
	
	//////////////////////////////////////////////////////////////////////////
	//比赛消息
	bool OnSocketMainMatch(int sub, void* data, int dataSize);
	//比赛费用
	bool OnSocketSubMatchFee(void* data, int dataSize);
	//参赛人数
	bool OnSocketSubMatchNum(void* data, int dataSize);
	//比赛状态
	bool OnSocketSubMatchStatus(void* data, int dataSize);
	//比赛描述
	bool OnSocketSubMatchDesc(void* data, int dataSize);


	//////////////////////////////////////////////////////////////////////////
	// 框架消息
public:
	//游戏已准备好
	virtual void OnGFGameReady();
	//游戏关闭
	virtual void OnGFGameClose(const std::string& sInfo, bool bExitGame = true);
	//恢复游戏
	virtual bool OnRecoveryGame();
	//////////////////////////////////////////////////////////////////////////
	// Socket消息
public:
	// 发送数据
	virtual bool GFSendData(int main, int sub, void* data, int size);

	//////////////////////////////////////////////////////////////////////////
	// 数据
	//////////////////////////////////////////////////////////////////////////
private:
	//辅助变量
	word	mReqTableID;						//请求桌子
	word	mReqChairID;						//请求位置
	word	mFindTableID;						//查找桌子
	bool	mIsGameReady;						//游戏是否准备好
	bool	mIsQuickSitDown;					//是否快速加入操作
	std::string mExitInfo;

	//用户
	IClientUserItem*	mMeUserItem;
	CPlazaUserManager*	mUserManager;
	bool				m_MobileUser;

	//房间属性
	enServiceStatus		mServiceStatus;
	tagGameKind			mGameKind;						//类型信息
	tagGameServer		mGameServer;					//房间信息
	tagUserAttribute	mUserAttribute;					//用户属性
	tagServerAttribute	mServerAttribute;				//房间属性

	//配置参数
	CParameterGame*		mParameterGame;					//游戏配置
	CParameterServer*	mParameterServer;				//房间配置
	
	//桌子
	CTableFrame			mTableFrame;				//桌子框架
	dword				m_dwCustTUUID;

	//接口
	IServerItemSink*	mIServerItemSink;				//房间接口
	IChatSink*			mIChatSink;						//聊天接口
	IStringMessageSink*	mIStringMessageSink;			//信息接口
	
	// 网络连接
	ISocketEngine*		mSocketEngine;
};
#endif // _CServerItem_H_