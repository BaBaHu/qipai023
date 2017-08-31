#ifndef GAME_LOGIC_HEAD_FILE
#define GAME_LOGIC_HEAD_FILE

#pragma once
#include "../Plazz.h"
#include "cocos2d.h"
//////////////////////////////////////////////////////////////////////////

//��ֵ����
#define	LOGIC_MASK_COLOR			0xF0								//��ɫ����
#define	LOGIC_MASK_VALUE			0x0F								//��ֵ����

//////////////////////////////////////////////////////////////////////////


//��Ϸ�˿��߼�
class BaijialeCardlogic
{
	//��������
private:
	static const byte				m_cbCardListData[52*8];				//�˿˶���

	//��������
public:
	//���캯��
	BaijialeCardlogic();
	//��������
	virtual ~BaijialeCardlogic();

	//���ͺ���
public:
	//��ȡ��ֵ
	byte GetCardValue(byte cbCardData) { return cbCardData&LOGIC_MASK_VALUE; }
	//��ȡ��ɫ
	byte GetCardColor(byte cbCardData) { return cbCardData&LOGIC_MASK_COLOR; }

	//���ƺ���
public:
	//�����˿�
	void RandCardList(byte cbCardBuffer[], byte cbBufferCount);

	//�߼�����
public:
	//��ȡ�Ƶ�
	byte GetCardPip(byte cbCardData);
	//��ȡ�Ƶ�
	byte GetCardListPip(const byte cbCardData[], byte cbCardCount);
};

//////////////////////////////////////////////////////////////////////////

#endif
