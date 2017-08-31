#ifndef _FourHZBClientKernelSink_H_
#define _FourHZBClientKernelSink_H_

#pragma once
#include "ClientKernelSink.h"
#include "cocos2d.h"


//游戏引擎
class FourHZBClientKernelSink : public ClientKernelSink
{
	//函数定义
public:
	//构造函数
	FourHZBClientKernelSink();
	//析构函数
	virtual ~FourHZBClientKernelSink();

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
	//设置抵注消息
	virtual void setDizhu(int nDizhu);

	//消息处理
protected:
	bool OnGameStart(void* data, word wSize);
	bool OnGameConfig(void* data, word	wSize);
	bool OnGameChuPai(void* data, word wSize);
	bool OnGameSendPai(void* data, word wSize);
	bool OnGameOperateNotify(void* data, word wSize);
	bool OnGameOperateResult(void* data, word wSize);
	bool OnGameOver(void* data, word wSize);
	bool OnGameTrustee(void* data, word wSize);
	bool OnGameReplaceCard(void* data, word wSize);
	bool OnGameChangeTableOwner(void* data, word wSize);
	bool OnGameExit(void* data, word wSize);
	bool OnGameQianGangResult(void* data, word wSize);
};

#endif // _FourHZBClientKernelSink_H_