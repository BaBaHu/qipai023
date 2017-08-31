#ifndef _IClientKernelSink_H_
#define _IClientKernelSink_H_

#include "../user/IClientUserItem.h"

class IClientKernelSink
{
public:
	virtual ~IClientKernelSink(){};

	//控制接口
public:
	//启动游戏
	virtual bool SetupGameClient()=0;
	//重置游戏
	virtual void ResetGameClient()=0;
	//关闭游戏
	virtual void CloseGameClient()=0;

	//框架事件
public:
	//系统滚动消息
	virtual bool OnGFTableMessage(const char* szMessage)=0;
	//全局消息
	virtual bool OnGFGlobalMessage(const char* szMessage)=0;
	//公告消息
	virtual bool OnGFNoticeMessage(const char* szMessage) = 0;
	//等待提示
	virtual bool OnGFWaitTips(bool bWait)=0;
	//比赛信息
	virtual bool OnGFMatchInfo(tagMatchInfo* pMatchInfo)=0;
	//比赛等待提示
	virtual bool OnGFMatchWaitTips(tagMatchWaitTip* pMatchWaitTip)=0;
	//比赛结果
	virtual bool OnGFMatchResult(tagMatchResult* pMatchResult)=0;
	//房卡结果
	virtual bool OnGFCustomRoomResult(void* data, int dataSize) = 0;
	//语音聊天	
	virtual bool OnGFTableVoiceChat(void* data, int dataSize) = 0;
	//游戏事件
public:
	//旁观消息
	virtual bool OnEventLookonMode(void* data, int dataSize)=0;
	//场景消息
	virtual bool OnEventSceneMessage(byte cbGameStatus, bool bLookonUser, void* data, int dataSize)=0;
	//场景消息
	virtual bool OnEventGameMessage(int sub, void* data, int dataSize)=0;
	//管理消息
	virtual bool OnEventManageMessage(int sub, void* data, int dataSize)=0;

	//时钟事件
public:
	//用户时钟
	virtual void OnEventUserClock(word wChairID, word wUserClock)=0;
	//时钟删除
	virtual bool OnEventGameClockKill(word wChairID)=0;
	//时钟信息
	virtual bool OnEventGameClockInfo(word wChairID, uint nElapse, word wClockID)=0;

	//用户事件
public:
	//用户进入
	virtual void OnEventUserEnter(IClientUserItem * pIClientUserItem, bool bLookonUser)=0;
	//用户离开
	virtual void OnEventUserLeave(IClientUserItem * pIClientUserItem, bool bLookonUser)=0;
	//用户积分
	virtual void OnEventUserScore(IClientUserItem * pIClientUserItem, bool bLookonUser)=0;
	//用户状态
	virtual void OnEventUserStatus(IClientUserItem * pIClientUserItem, bool bLookonUser)=0;
	//用户属性
	virtual void OnEventUserAttrib(IClientUserItem * pIClientUserItem, bool bLookonUser)=0;
	//用户头像
	virtual void OnEventCustomFace(IClientUserItem * pIClientUserItem, bool bLookonUser)=0;
	//用户自定义桌子
	virtual void OnEventCustomTable(IClientUserItem * pIClientUserItem, bool bLookonUser)=0;
};

#endif // _IClientKernelSink_H_