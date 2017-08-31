#ifndef _IClientKernel_H_
#define _IClientKernel_H_

#include "../IChatSink.h"
#include "../IStringMessageSink.h"
#include "IClientKernelSink.h"

class CGameServerItem;

//客户端内核
class IClientKernel
{
public:
	virtual ~IClientKernel(){};
	//////////////////////////////////////////////////////////////////////////
	//配置接口
public:
	//设置接口
	virtual bool SetClientKernelSink(IClientKernelSink* pIClientKernelSink)=0;
	//设置接口
	virtual bool SetChatSink(IChatSink* pIChatSink)=0;
	//设置接口
	virtual bool SetStringMessageSink(IStringMessageSink* pIStringMessageSink)=0;
	//初始化
	virtual bool Init()=0;
	//关闭
	virtual bool Intermit(const std::string& sInfo, bool bExitGame = true )=0;

	//属性接口
public:
	//用户属性
	virtual tagUserAttribute * GetUserAttribute()=0;
	//游戏属性
	virtual tagGameAttribute * GetGameAttribute()=0;
	//房间属性
	virtual tagServerAttribute * GetServerAttribute()=0;
	//自定义房间属性
	virtual tagCustomTableInfo* GetCustomTableInfo()= 0;
	//模式接口
public:
	//单机模式
	virtual bool IsSingleMode()=0;
	//旁观状态
	virtual bool IsLookonMode()=0;
	//允许状态
	virtual bool IsAllowLookon()=0;

	//状态接口
public:
	//获取状态
	virtual byte GetGameStatus()=0;
	//设置状态
	virtual void SetGameStatus(byte cbGameStatus)=0;

	//用户接口
public:
	//自己位置
	virtual word GetMeChairID()=0;
	//自己位置
	virtual IClientUserItem * GetMeUserItem()=0;
	//游戏用户
	virtual IClientUserItem * GetTableUserItem(word wChariID)=0;
	//游戏视图用户
	virtual IClientUserItem * GetViewUserItem(word wChariID)=0;
	//查找用户
	virtual IClientUserItem * SearchUserByUserID(dword dwUserID)=0;
	//查找用户
	virtual IClientUserItem * SearchUserByGameID(dword dwGameID)=0;
	//查找用户
	virtual IClientUserItem * SearchUserByNickName(const char* szNickName)=0;
	//旁观用户
	virtual IClientUserItem * EnumLookonUserItem(word wEnumIndex)=0;

	//网络接口
public:
	//发送函数
	virtual bool SendSocketData(word wSubCmdID)=0;
	//发送函数
	virtual bool SendSocketData(word wSubCmdID, void * pData, word wDataSize)=0;
	//发送函数
	virtual bool SendSocketData(word wMainCmdID, word wSubCmdID)=0;
	//发送函数
	virtual bool SendSocketData(word wMainCmdID, word wSubCmdID, void * pData, word wDataSize)=0;

	//功能接口
public:
	//发送进入场景
	virtual bool SendGameOption()=0;
	//发送准备
	virtual bool SendUserReady(void * pData, word wDataSize)=0;
	//旁观控制
	virtual bool SendUserLookon(dword dwUserID, bool bAllowLookon)=0;
	//发送表情
	virtual bool SendUserExpression(dword dwTargetUserID, word wItemIndex)=0;
	//发送聊天
	virtual bool SendUserChatMessage(dword dwTargetUserID, const char* pszChatString, dword crColor)=0;

	//时钟接口
public:
	//获取用户时间
	virtual word GetUserClock(word wChairID)=0;
	//设置用户时间
	virtual void SetUserClock(word wChairID, word wUserClock) = 0;
	//时钟标识
	virtual uint GetClockID()=0;
	//时钟位置
	virtual word GetClockChairID()=0;
	//删除时钟
	virtual void KillGameClock(word wClockID)=0;
	//设置时钟
	virtual void SetGameClock(word wChairID, word wClockID, uint nElapse)=0;

	//辅助接口
public:
	//切换椅子
	virtual word SwitchViewChairID(word wChairID)=0;

	//////////////////////////////////////////////////////////////////////////
	//框架接口
	//////////////////////////////////////////////////////////////////////////
	//配置接口
public:
	//房间配置
	virtual void OnGFConfigServer(const tagUserAttribute& UserAttribute, const tagServerAttribute& ServerAttribute )=0;
	//配置完成
	virtual void OnGFConfigFinish()=0;

	//Socket接口
public:
	virtual bool OnGFEventSocket(int main, int sub, void* data, int dataSize)=0;

	//用户接口
public:
	//用户进入
	virtual void OnGFUserEnter(IClientUserItem* pIClientUserItem)=0;
	//用户积分
	virtual void OnGFUserScore(dword dwUserID, const tagUserScore& UserScore)=0;
	//用户状态
	virtual void OnGFUserStatus(dword dwUserID, const tagUserStatus& UserStatus)=0;
	//用户属性
	virtual void OnGFUserAttrib(dword dwUserID, const tagUserAttrib& UserAttrib)=0;
	//用户自定义头像
	virtual void OnGFUserCustomFace(dword dwUserID,  dword dwCustomID, const tagCustomFaceInfo& CustomFaceInfo)=0;
	//用户自定义桌子
	virtual void OnGFUserCustomTable(dword dwUserID, const tagCustomTableInfo& CustomTableInfo) = 0;
public:
	static IClientKernel* create();
	static void destory();
	static IClientKernel* get();
};

#endif // _IClientKernel_H_