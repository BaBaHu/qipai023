#ifndef GAME_LOGIC_HEAD_FILE
#define GAME_LOGIC_HEAD_FILE

#pragma once
#include "../Plazz.h"
#include "cocos2d.h"
//////////////////////////////////////////////////////////////////////////

//数值掩码
#define	LOGIC_MASK_COLOR			0xF0								//花色掩码
#define	LOGIC_MASK_VALUE			0x0F								//数值掩码

//////////////////////////////////////////////////////////////////////////


//游戏扑克逻辑
class BaijialeCardlogic
{
	//变量定义
private:
	static const byte				m_cbCardListData[52*8];				//扑克定义

	//函数定义
public:
	//构造函数
	BaijialeCardlogic();
	//析构函数
	virtual ~BaijialeCardlogic();

	//类型函数
public:
	//获取数值
	byte GetCardValue(byte cbCardData) { return cbCardData&LOGIC_MASK_VALUE; }
	//获取花色
	byte GetCardColor(byte cbCardData) { return cbCardData&LOGIC_MASK_COLOR; }

	//控制函数
public:
	//混乱扑克
	void RandCardList(byte cbCardBuffer[], byte cbBufferCount);

	//逻辑函数
public:
	//获取牌点
	byte GetCardPip(byte cbCardData);
	//获取牌点
	byte GetCardListPip(const byte cbCardData[], byte cbCardCount);
};

//////////////////////////////////////////////////////////////////////////

#endif
