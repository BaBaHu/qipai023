#ifndef _ClientKernelSink_H_
#define _ClientKernelSink_H_

#pragma once
#include "../Plazz.h"
#include "cocos2d.h"
#include "YvVoiceManager.h"
////////////////////////////////////////////////////////////////////////////////////////
//游戏定时器
#define IDI_START_GAME				200									//开始定时器

#define IDI_OUT_CARD				201									//出牌定时器
#define IDI_OPERATE_CARD			202									//操作定时器
#define IDI_WAIT_CARD				203									//等待定时器
#define IDI_SELECT_CARD				204									//选牌定时器
#define IDI_CHANGE_CARD				205									//换牌定时器
//#define IDI_REPLACE_CARD			205									//补牌定时器

//游戏定时器
#define TIME_START_GAME				30									//开始定时器
#define TIME_OUT_CARD				25									//出牌定时器
#define TIME_OPERATE_CARD			15									//操作定时器	
#define TIME_REPLACE_CARD			1000								//补牌定时器

/////////////////////////////////////////////////////////////////////////////////////////
//时间标识
#define IDI_FREE					301									//空闲时间
#define IDI_PLACE_JETTON			302									//下注时间
#define IDI_DISPATCH_CARD			303									//发牌时间
#define IDI_PLACE_JETTON_BUFFER		304									//发牌时间

#define MAX_TIME_OUT				3									//最大超时次数

enum ChatType
{
	en_ChatType_Text = 0,
	en_ChatType_VoiceText,
	en_ChatType_Voice,
};

//游戏引擎
class ClientKernelSink 
	:public Ref 
	,public IClientKernelSink
	,public IVoicePlaySink
	,public YVSDK::YVListern::YVUpLoadFileListern
{

	//函数定义
public:
	//构造函数
	ClientKernelSink();
	//析构函数
	virtual ~ClientKernelSink();

	virtual void onUpLoadFileListern(YVSDK::UpLoadFileRespond*);
	virtual void onPlayComplete();

	//控制接口
public:
	//启动游戏
	virtual bool SetupGameClient();
	//重置游戏
	virtual void ResetGameClient();
	//关闭游戏
	virtual void CloseGameClient();

	//框架事件
public:
	//系统滚动消息
	virtual bool OnGFTableMessage(const char* szMessage);
	//全局消息
	virtual bool OnGFGlobalMessage(const char* szMessage);
	//公告消息
	virtual bool OnGFNoticeMessage(const char* szMessage);
	//等待提示
	virtual bool OnGFWaitTips(bool bWait);
	//比赛信息
	virtual bool OnGFMatchInfo(tagMatchInfo* pMatchInfo);
	//比赛等待提示
	virtual bool OnGFMatchWaitTips(tagMatchWaitTip* pMatchWaitTip);
	//比赛结果
	virtual bool OnGFMatchResult(tagMatchResult* pMatchResult);
	//房卡结果
	virtual bool OnGFCustomRoomResult(void* data, int dataSize);
	//语音聊天	
	virtual bool OnGFTableVoiceChat(void* data, int dataSize);
	//游戏事件
public:
	//旁观消息
	virtual bool OnEventLookonMode(void* data, int dataSize);
	//场景消息
	virtual bool OnEventSceneMessage(byte cbGameStatus, bool bLookonUser, void* data, int dataSize);
	//游戏消息
	virtual bool OnEventGameMessage(int sub, void* data, int dataSize);
	//管理消息
	virtual bool OnEventManageMessage(int sub, void* data, int dataSize);
	//时钟事件
public:
	//用户时钟
	virtual void OnEventUserClock(word wChairID, word wUserClock);
	//时钟删除
	virtual bool OnEventGameClockKill(word wChairID);
	//时钟信息
	virtual bool OnEventGameClockInfo(word wChairID, uint nElapse, word wClockID);

	//用户事件
public:
	//用户进入
	virtual void OnEventUserEnter(IClientUserItem * pIClientUserItem, bool bLookonUser);
	//用户离开
	virtual void OnEventUserLeave(IClientUserItem * pIClientUserItem, bool bLookonUser);
	//用户积分
	virtual void OnEventUserScore(IClientUserItem * pIClientUserItem, bool bLookonUser);
	//用户状态
	virtual void OnEventUserStatus(IClientUserItem * pIClientUserItem, bool bLookonUser);
	//用户属性
	virtual void OnEventUserAttrib(IClientUserItem * pIClientUserItem, bool bLookonUser);
	//用户头像
	virtual void OnEventCustomFace(IClientUserItem * pIClientUserItem, bool bLookonUser);
	//用户自定义桌子
	virtual void OnEventCustomTable(IClientUserItem * pIClientUserItem, bool bLookonUser);

	//脚本接口
public:
	virtual int getUserTypeByChair(int nChair); //0是普通 1是QQ 2是微信
	virtual const char* getUserIconUrlByChair(int nChair);
	virtual const char* getUserNameByID(int nUserID);
	virtual void startTalk();
	virtual void endTalk(bool bSend);
	virtual void playTalk(int nChair, const char* url);
	virtual void playChat(int nChair, int nIdx, int nSex);

	virtual void setGameOffline();
	//发送进入场景消息
	virtual void enterGame();
	//发送离开场景消息
	virtual void leaveGame();
	//发送准备消息
	virtual void ready();
	//设置时钟
	virtual void setGameClock(int wChairID, int nTimerID, int nTimer);
	//清除时钟
	virtual void clearGameClock(int wChairID);
	//是否可启动时钟
	virtual void setEnableGameClock(bool bEnable);
	//获取桌子玩家最小的金币数量
	virtual int getTableMinGold();
	//获取庄家用户
	virtual int getCurBanker(){ return INVALID_CHAIR; }

	//设置托管
	virtual void setTrustee(bool Trustee){}
	//出牌消息
	virtual void chuPai(int idxPai){}
	//出牌操作消息
	virtual void operatePai(int nOperateCode, int idxPai){}
	//设置抵注消息
	virtual void setDizhu(int nDizhu){}
	//认输消息
	virtual void admitDefeat(){}
	//选牌定缺消息
	virtual void selectPai(int nType){}
	//换三张消息
	virtual void changePai(int nCard1, int nCard2, int nCard3){}

	//用户下注消息
	virtual void placeBet(int cbBetArea, int lBetScore){}
	//申请庄家消息
	virtual void applyBanker(){}
	//取消申请消息
	virtual void cancelBanker(){}
	//管理员命令消息
	virtual void adminCmd(int cbReqType){}
	//最大下注
	virtual unsigned int GetMaxPlayerScore(int cbBetArea){ return 0; }
	//获取总下注
	virtual unsigned int GetAreaTotalScore(int cbBetArea){ return 0; }
	//获取自己总下注
	virtual unsigned int GetAreaPlayerScore(int cbBetArea){ return 0; }
	//获取玩家自由金币
	virtual unsigned int GetPlayerFreeScore(){ return 0; }
	//获取牌点数
	virtual int GetCardPip(int nCardID){ return 0; }
	//
	virtual void getBet(){}
	//LKPY函数
	////////////////////////////////////////////////////////////////////
	//消息处理
protected:
	bool OnGameDismissVoteNotify(void* data, word wSize);
	bool OnGameDismissVoteResult(void* data, word wSize);
public:
	static ClientKernelSink* GetInstance();
	static void Release();
	//设置时钟
	void StartGameClock(int wChairID, int nTimerID, int nTimer);
	//获取系统消息
	std::string GetGlobalMessage();
	void UpdateCustomTableInfo();
	bool				m_bRunning;
private:
	std::string			szGlobalMessage;
	tagCustomTableInfo  mCustomTableInfo;
	bool				m_bEnableTimer;
protected:
	static ClientKernelSink*	s_Instance;
};

#endif // _ClientKernelSink_H_