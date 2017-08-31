#ifndef GLOBAL_USER_INFO_HEAD_FILE
#define GLOBAL_USER_INFO_HEAD_FILE

#pragma once

#include "../Plazz.h"

//////////////////////////////////////////////////////////////////////////////////
//结构定义

//用户信息
struct tagGlobalUserData
{
	//基本资料
	dword							dwUserID;							//用户 I D
	dword							dwGameID;							//游戏 I D
	dword							dwUserMedal;						//用户奖牌
	dword							dwExperience;						//用户经验
	dword							dwLoveLiness;						//用户魅力
	dword							dwMasterRight;						//管理员权限
	char							szAccounts[LEN_ACCOUNTS];			//登录帐号
	char							szNickName[LEN_NICKNAME];			//用户昵称
	char							szPassword[LEN_PASSWORD];			//登录密码

	//扩展资料
	byte							cbGender;							//用户性别
	byte							cbMoorMachine;						//锁定机器
	char							szUnderWrite[LEN_UNDER_WRITE];		//个性签名
	char							szIconUrl[256];						//头像地址
	byte							cbDailiOrder;						// 是否是代理账户，代理账户用来 转钱的 现在默认都为 非代理账户
	byte							cbUserType;

	//社团资料
	dword							dwGroupID;							//社团索引
	char							szGroupName[LEN_GROUP_NAME];		//社团名字

	uint32							lRoomCard;							//房卡费
	dword							dwRoomExtData;						//房卡UUID

	//会员资料
	byte							cbMemberOrder;						//会员等级
	systemtime						MemberOverDate;						//到期时间

	//头像信息
	word							wFaceID;							//头像索引
	dword							dwCustomID;							//自定标识
	tagCustomFaceInfo				CustomFaceInfo;						//自定头像
};

//登录成功
struct CMD_GP_LogonSuccess
{
	//属性资料
	word							wFaceID;							//头像标识
	dword							dwUserID;							//用户 I D
	dword							dwGameID;							//游戏 I D
	dword							dwGroupID;							//社团标识
	dword							dwCustomID;							//自定标识
	dword							dwUserMedal;						//用户奖牌
	dword							dwExperience;						//经验数值
	dword							dwLoveLiness;						//用户魅力
	dword							dwMasterRight;						//管理员权限

																		//用户成绩
	SCORE							lUserScore;							//用户金币
	SCORE							lUserInsure;						//用户银行

																		//用户信息
	byte							cbGender;							//用户性别
	byte							cbMoorMachine;						//锁定机器
	char							szAccounts[LEN_ACCOUNTS];			//登录帐号
	char							szNickName[LEN_ACCOUNTS];			//用户昵称
	char							szGroupName[LEN_GROUP_NAME];		//社团名字

	byte							cbDailiOrder;						// 是否是代理账户，代理账户用来 转钱的 现在默认都为 非代理账户
	byte							cbUserType;

	byte							cbTemp1;						// 占位用
	byte							cbTemp2;						// 占位用
	unsigned int							lRoomCard;							//房卡费

																				//配置信息
	byte                            cbShowServerStatus;                 //显示服务器状态
};



//扩展资料
struct tagIndividualUserData
{
	//用户信息
	char							szUserNote[LEN_USER_NOTE];			//用户说明
	char							szCompellation[LEN_COMPELLATION];	//真实名字

	//电话号码
	char							szSeatPhone[LEN_SEAT_PHONE];		//固定电话
	char							szMobilePhone[LEN_MOBILE_PHONE];	//移动电话

	//联系资料
	char							szQQ[LEN_QQ];						//Q Q 号码
	char							szEMail[LEN_EMAIL];					//电子邮件
	char							szDwellingPlace[LEN_DWELLING_PLACE];//联系地址
};

//银行信息
struct tagUserInsureInfo
{
	word							wRevenueTake;						//税收比例
	word							wRevenueTransfer;					//税收比例
	word							wServerID;							//房间标识
	SCORE							lUserScore;							//用户游戏币	.. 又是银行的游戏币
	SCORE							lUserInsure;						//银行游戏币
	SCORE							lTransferPrerequisite;				//转账条件
};


//////////////////////////////////////////////////////////////////////////////////

//用户信息
class CGlobalUserInfo
{
	//用户信息
protected:
	tagGlobalUserData				m_GlobalUserData;						//用户资料
	tagIndividualUserData			m_IndividualUserData;					//扩展资料
	tagUserInsureInfo				m_UserInsureInfo;						//银行资料

	//静态变量
protected:
	static CGlobalUserInfo *		m_pGlobalUserInfo;						//用户信息

	//函数定义
public:
	//构造函数
	CGlobalUserInfo();
	//析构函数
	virtual ~CGlobalUserInfo();

	//功能函数
public:
	//重置资料
	void ResetUserInfoData();
	//用户资料
	tagGlobalUserData * GetGlobalUserData() { return &m_GlobalUserData; }
	//扩展资料
	tagIndividualUserData * GetIndividualUserData() { return &m_IndividualUserData; }
	//银行资料
	tagUserInsureInfo * GetUserInsureInfo() { return &m_UserInsureInfo; }

	//静态函数
public:
	//获取对象
	static CGlobalUserInfo * GetInstance() { return m_pGlobalUserInfo; }
};

//////////////////////////////////////////////////////////////////////////////////

#endif