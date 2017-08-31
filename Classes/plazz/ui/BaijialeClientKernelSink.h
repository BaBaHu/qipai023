#ifndef _BaijialeClientKernelSink_H_
#define _BaijialeClientKernelSink_H_

#pragma once
#include "ClientKernelSink.h"
#include "cocos2d.h"
#include "BaijialeCardlogic.h"
#include "CommonMutex.h"

struct tagGPBet
{
	int								wChairID;
	int								cbBetArea;
	SCORE							lBetScore;
};

//游戏引擎
class BaijialeClientKernelSink : public ClientKernelSink
{
	//函数定义
public:
	//构造函数
	BaijialeClientKernelSink();
	//析构函数
	virtual ~BaijialeClientKernelSink();

	//游戏事件
public:
	//旁观消息
	virtual bool OnEventLookonMode(void* data, int dataSize);
	//场景消息
	virtual bool OnEventSceneMessage(byte cbGameStatus, bool bLookonUser, void* data, int dataSize);
	//游戏消息
	virtual bool OnEventGameMessage(int sub, void* data, int dataSize);

	//脚本接口
public:
	//获取庄家用户
	virtual int getCurBanker(){ return m_wBankerUser; }
	//用户下注消息
	virtual void placeBet(int cbBetArea, int lBetScore);
	//申请庄家消息
	virtual void applyBanker();
	//取消申请消息
	virtual void cancelBanker();
	//管理员命令消息
	virtual void adminCmd(int cbReqType);
	//最大下注
	virtual unsigned int GetMaxPlayerScore(int cbBetArea);
	//获取总下注
	virtual unsigned int GetAreaTotalScore(int cbBetArea);
	//获取自己总下注
	virtual unsigned int GetAreaPlayerScore(int cbBetArea);
	//获取玩家自由金币
	virtual unsigned int GetPlayerFreeScore(){ return m_lPlayFreeSocre; }
	//获取牌点数
	virtual int GetCardPip(int nCardID);
	//
	virtual void getBet();
	//消息处理
protected:
	bool OnGameFree(void* data, word wSize);
	bool OnGameStart(void* data, word wSize);
	bool OnGamePlaceBet(void* data, word wSize);
	bool OnGameCancelBet(void* data, word wSize);
	bool OnGamePlaceBetFail(void* data, word wSize);
	bool OnGameApplyBanker(void* data, word wSize);
	bool OnGameCancelBanker(void* data, word wSize);
	bool OnGameChangeBanker(void* data, word wSize);
	bool OnGameReSortBanker(void* data, word wSize);
	bool OnGameOver(void* data, word wSize);
	bool OnGameCommandResult(void* data, word wSize);
	bool OnGameTipInfo(void* data, word wSize);
	bool OnGameSendRecord(void* data, word wSize);
private:
	//推断赢家
	void DeduceWinner(byte* pWinArea);
	//推断赢家
	void DeduceWinner(byte &cbWinner, byte &cbKingWinner, bool &bPlayerTwoPair, bool &bBankerTwoPair);
private:
	BaijialeCardlogic	m_CardLogic;			//游戏逻辑

	byte				m_cbCardCount[2];					//扑克数目
	byte				m_cbTableCardArray[2][3];			//桌面扑克

	bool				m_bEnableSysBanker;     //是否允许系统坐庄
	word				m_wBankerUser;			//当前庄家
	longlong			m_lBankerScore;			//当前庄家携带金币量
	longlong			m_lMeMaxScore;			//玩家最大下注
	longlong			m_lAreaLimitScore;		//区域限制
	longlong			m_lPlayBet[8];			//玩家下注
	longlong			m_lAllBet[8];			//总下注
	longlong			m_lPlayFreeSocre;		//玩家自由金币
	std::vector<tagGPBet>	m_vBet;
	CommonMutex			s_Locker;
};

#endif // _BaijialeClientKernelSink_H_