#ifndef _CClientKernel_H_
#define _CClientKernel_H_

#include "../../Plazz.h"
#include "../../network/ISocketEngine.h"
#include "../user/ClientUserManager.h"
#include "IClientKernel.h"
#include "TimerEngine.h"

class CClientKernel 
	: public IClientKernel
	, public IUserManagerSink
	, public ITimerEngineSink
{

public:
	CClientKernel();
	~CClientKernel();

	//////////////////////////////////////////////////////////////////////////
	// IClientKernel
	//配置接口
public:
	//设置接口
	virtual bool SetClientKernelSink(IClientKernelSink* pIClientKernelSink);
	//设置接口
	virtual bool SetChatSink(IChatSink* pIChatSink);
	//设置接口
	virtual bool SetStringMessageSink(IStringMessageSink* pIStringMessageSink);
	//内核配置
	virtual bool Init();
	//关闭
	virtual bool Intermit(const std::string& sInfo, bool bExitGame = true);

	//属性接口
public:
	//用户属性
	virtual tagUserAttribute * GetUserAttribute();
	//游戏属性
	virtual tagGameAttribute * GetGameAttribute();
	//房间属性
	virtual tagServerAttribute * GetServerAttribute();
	//自定义房间属性
	virtual tagCustomTableInfo* GetCustomTableInfo();
	//模式接口
public:
	//单机模式
	virtual bool IsSingleMode();
	//旁观状态
	virtual bool IsLookonMode();
	//允许状态
	virtual bool IsAllowLookon();

	//状态接口
public:
	//获取状态
	virtual byte GetGameStatus();
	//设置状态
	virtual void SetGameStatus(byte cbGameStatus);

	//用户接口
public:
	//自己位置
	virtual word GetMeChairID();
	//自己位置
	virtual IClientUserItem * GetMeUserItem();
	//游戏用户
	virtual IClientUserItem * GetTableUserItem(word wChariID);
	//游戏视图用户
	virtual IClientUserItem * GetViewUserItem(word wChariID);
	//查找用户
	virtual IClientUserItem * SearchUserByUserID(dword dwUserID);
	//查找用户
	virtual IClientUserItem * SearchUserByGameID(dword dwGameID);
	//查找用户
	virtual IClientUserItem * SearchUserByNickName(const char* szNickName);
	//旁观用户
	virtual IClientUserItem * EnumLookonUserItem(word wEnumIndex);

	//网络接口
public:
	//发送函数
	virtual bool SendSocketData(word wSubCmdID);
	//发送函数
	virtual bool SendSocketData(word wSubCmdID, void * pData, word wDataSize);
	//发送函数
	virtual bool SendSocketData(word wMainCmdID, word wSubCmdID);
	//发送函数
	virtual bool SendSocketData(word wMainCmdID, word wSubCmdID, void * data, word dataSize);

	//功能接口
public:
	//发送进入场景
	virtual bool SendGameOption();
	//发送准备
	virtual bool SendUserReady(void * data, word dataSize);
	//旁观控制
	virtual bool SendUserLookon(dword dwUserID, bool bAllowLookon);
	//发送表情
	virtual bool SendUserExpression(dword dwTargetUserID, word wItemIndex);
	//发送聊天
	virtual bool SendUserChatMessage(dword dwTargetUserID, const char* pszChatString, dword crColor);

	//时钟接口
public:
	//获取用户时间
	virtual word GetUserClock(word wChairID);
	//设置用户时间
	virtual void SetUserClock(word wChairID, word wUserClock);
	//时钟标识
	virtual uint GetClockID();
	//时钟位置
	virtual word GetClockChairID();
	//删除时钟
	virtual void KillGameClock(word wClockID);
	//设置时钟
	virtual void SetGameClock(word wChairID, word wClockID, uint nElapse);
	//时钟回调
	virtual void OnTimerEngineTick(word id);

	//辅助接口
public:
	//切换椅子
	virtual word SwitchViewChairID(word wChairID);


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
	//IGameFrameSink
	
	//配置接口
public:
	//房间配置
	virtual void OnGFConfigServer(const tagUserAttribute& UserAttribute, const tagServerAttribute& ServerAttribute);
	//配置完成
	virtual void OnGFConfigFinish();

	//Socket接口
public:
	virtual bool OnGFEventSocket(int main, int sub, void* data, int dataSize);

	//用户聊天
	bool OnSocketSubUserChat(void* data, int dataSize);
	//用户表情
	bool OnSocketSubExpression(void* data, int dataSize);
	//游戏状态
	bool OnSocketSubGameStatus(void* data, int dataSize);
	//游戏场景
	bool OnSocketSubGameScene(void* data, int dataSize);
	//旁观状态
	bool OnSocketSubLookonStatus(void* data, int dataSize);
	//系统消息
	bool OnSocketSubSystemMessage(void* data, int dataSize);
	//动作消息
	bool OnSocketSubActionMessage(void* data, int dataSize);

	//用户接口
public:
	//用户进入
	virtual void OnGFUserEnter(IClientUserItem* pIClientUserItem);
	//用户积分
	virtual void OnGFUserScore(dword dwUserID, const tagUserScore& UserScore);
	//用户状态
	virtual void OnGFUserStatus(dword dwUserID, const tagUserStatus& UserStatus);
	//用户属性
	virtual void OnGFUserAttrib(dword dwUserID, const tagUserAttrib& UserAttrib);
	//用户自定义头像
	virtual void OnGFUserCustomFace(dword dwUserID,  dword dwCustomID, const tagCustomFaceInfo& CustomFaceInfo);
	//用户自定义桌子
	virtual void OnGFUserCustomTable(dword dwUserID, const tagCustomTableInfo& CustomTableInfo);
	//////////////////////////////////////////////////////////////////////////
	// 数据
	//////////////////////////////////////////////////////////////////////////
protected:
	//时间信息
	word				m_wClockID;						//时钟标识
	uint				m_nElapseCount;					//时钟计数
	word				m_wClockChairID;				//时钟位置
	word				m_wUserClock[MAX_CHAIR];		//用户时钟
	TimerEngine			mTimerEngine;					//时钟引擎

	bool				mAllowLookon;					//是否允许旁观
	byte				mGameStatus;					//游戏状态

	IClientUserItem*	mMeUserItem;					//自身数据
	CGameUserManager*	mUserManager;					//用户管理

	tagUserAttribute	mUserAttribute;					//用户属性
	tagGameAttribute	mGameAttribute;					//游戏属性
	tagServerAttribute	mServerAttribute;				//房间属性
	tagCustomTableInfo	mCustTInfo;						//自定义房间属性

	//接口
	IClientKernelSink*	mIClientKernelSink;				//内核接口
	IChatSink*			mIChatSink;						//聊天接口
	IStringMessageSink*	mIStringMessageSink;			//信息接口

};
#endif // _CClientKernel_H_