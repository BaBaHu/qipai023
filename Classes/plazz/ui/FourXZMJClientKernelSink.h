#ifndef _FourXZMJClientKernelSink_H_
#define _FourXZMJClientKernelSink_H_

#pragma once
#include "ClientKernelSink.h"
#include "cocos2d.h"


//游戏引擎
class FourXZMJClientKernelSink : public ClientKernelSink
{
	//函数定义
public:
	//构造函数
	FourXZMJClientKernelSink();
	//析构函数
	virtual ~FourXZMJClientKernelSink();

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
	//设置托管
	virtual void setTrustee(bool Trustee);
	//出牌消息
	virtual void chuPai(int idxPai);
	//出牌操作消息
	virtual void operatePai(int nOperateCode, int idxPai);
	//选牌定缺消息
	virtual void selectPai(int nType);
	//换三张消息
	virtual void changePai(int nCard1, int nCard2, int nCard3);
	//消息处理
protected:
	bool OnGameStart(void* data, word wSize);
	bool OnGameSelectPai(void* data, word wSize);
	bool OnGameChuPai(void* data, word wSize);
	bool OnGameSendPai(void* data, word wSize);
	bool OnGameOperateNotify(void* data, word wSize);
	bool OnGameOperateResult(void* data, word wSize);
	bool OnGameChiHu(void* data, word wSize);
	bool OnGameGangScore(void* data, word wSize);
	bool OnGameOver(void* data, word wSize);
	bool OnGameTrustee(void* data, word wSize);
	bool OnGameChangeCard(void* data, word wSize);
};

#endif // _FourXZMJClientKernelSink_H_