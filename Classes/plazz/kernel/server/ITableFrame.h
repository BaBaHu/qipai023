#ifndef _ITableFrame_H_
#define _ITableFrame_H_

#include "../../df/types.h"
#include "../../df/Define.h"
#include "../../df/Struct.h"
class IClientUserItem;
class ITableFrame;
class ITable;

class ITableListener
{
public:
	virtual ~ITableListener(){}
	virtual void TableClientUserItem(word wChairID, IClientUserItem* pIClientUserItem)=0;
	virtual void TableTableStatus(bool bPlaying, bool bLocker)=0;
}; // ITableListener

//桌子
class ITable
{
public:
	virtual ~ITable(){};

	//功能接口
public:
	//获取桌子框架
	virtual ITableFrame* GetTableFrame()=0;
	//空椅子数
	virtual word GetNullChairCount(word & wNullChairID)=0;
	//配置函数
	virtual void InitTable(word wTableID, word wChairCount, ITableFrame * pITableFrameView)=0;
	//获取ID
	virtual word GetTableID()=0;
	//设置结果
	virtual void SetTableListener(ITableListener* listener) = 0;

	//用户接口
public:
	//获取用户
	virtual IClientUserItem * GetClientUserItem(word wChairID)=0;
	//设置信息
	virtual bool SetClientUserItem(word wChairID, IClientUserItem * pIClientUserItem)=0;

	//设置接口
public:
	//焦点框架
	virtual void SetFocusFrame(bool bFocusFrame)=0;
	//桌子状态 
	virtual void SetTableStatus(bool bPlaying, bool bLocker)=0;

	//查询接口
public:
	//游戏标志
	virtual bool GetPlayFlag()=0;
	//密码标志
	virtual bool GetLockerFlag()=0;
};

//桌子框架
class ITableFrame
{
public:
	virtual ~ITableFrame(){};

	//配置接口
public:
	//配置桌子
	virtual bool ConfigTableFrame(word wTableCount, word wChairCount, dword dwServerRule, word wServerType, word wServerID)=0;

	//信息接口
public:
	//桌子数目
	virtual word GetTableCount()=0;
	//椅子数目
	virtual word GetChairCount()=0;

	//用户接口
public:
	//获取用户
	virtual IClientUserItem * GetClientUserItem(word wTableID, word wChairID)=0;
	//设置信息
	virtual bool SetClientUserItem(word wTableID, word wChairID, IClientUserItem * pIClientUserItem)=0;

	//状态接口
public:
	//游戏标志
	virtual bool GetPlayFlag(word wTableID)=0;
	//密码标志
	virtual bool GetLockerFlag(word wTableID)=0;
	//焦点框架
	virtual void SetFocusFrame(word wTableID, bool bFocusFrame)=0;
	//桌子状态 
	virtual void SetTableStatus(word wTableID, bool bPlaying, bool bLocker)=0;

	//视图控制
public:
	//闪动桌子
	virtual bool FlashGameTable(word wTableID)=0;
	//闪动椅子
	virtual bool FlashGameChair(word wTableID, word wChairID)=0;

	//功能接口
public:
	//更新桌子
	virtual bool UpdateTable(word wTableID)=0;
	//获取桌子
	virtual ITable * GetTableItem(word wTableID)=0;
	//空椅子数
	virtual word GetNullChairCount(word wTableID, word & wNullChairID)=0;
};

#endif // _ITableFrame_H_