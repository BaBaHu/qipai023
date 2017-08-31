#ifndef CMD_FOUR_SPARROW_HEAD_FILE
#define CMD_FOUR_SPARROW_HEAD_FILE

//////////////////////////////////////////////////////////////////////////
//公共宏定义

#define KIND_ID						350									//游戏 I D

#define VERSION_SERVER				PROCESS_VERSION(6,0,3)				//程序版本
#define VERSION_CLIENT				PROCESS_VERSION(6,0,3)				//程序版本


#define GAME_PLAYER					4									//游戏人数
#define GAME_NAME					TEXT("四人红中宝")					//游戏名字
#define GAME_GENRE					(GAME_GENRE_SCORE|GAME_GENRE_MATCH|GAME_GENRE_GOLD)	//游戏类型

//游戏状态
#define GS_MJ_FREE					GAME_STATUS_FREE								//空闲状态
#define GS_MJ_PLAY					(GAME_STATUS_PLAY+1)						//游戏状态

//常量定义
#define MAX_WEAVE					4									//最大组合
#define MAX_INDEX					34//20									//最大索引
#define MAX_COUNT					14									//最大数目
#define MAX_REPERTORY				136//80									//最大库存
#define MAX_HUA_CARD				0									//花牌个数

//扑克定义
#define HEAP_FULL_COUNT				34//40									//堆立全牌

#define MAX_RIGHT_COUNT				1									//最大权位DWORD个数		


//////////////////////////////////////////////////////////////////////////

//组合子项
struct CMD_WeaveItem
{
	byte							cbWeaveKind;						//组合类型
	byte							cbCenterCard;						//中心扑克
	byte							cbPublicCard;						//公开标志
	word							wProvideUser;						//供应用户
	byte							cbCardData[4];						//组合数据
};

//////////////////////////////////////////////////////////////////////////
//服务器命令结构
#define SUB_S_MAIN_MSG				200									//服务端游戏操作主命令

#define SUB_S_GAME_START			100									//游戏开始
#define SUB_S_OUT_CARD				101									//出牌命令
#define SUB_S_SEND_CARD				102									//发送扑克
#define SUB_S_OPERATE_NOTIFY		104									//操作提示
#define SUB_S_OPERATE_RESULT		105									//操作命令
#define SUB_S_GAME_END				106									//游戏结束
#define SUB_S_TRUSTEE				107									//用户托管
#define SUB_S_REPLACE_CARD			108									//用户补牌
#define SUB_S_CHANGE_TABLE_OWNER	110									//桌主更换
#define SUB_S_EXITGAME				111									//离开游戏
#define SUB_S_QGang_CARD			112									//抢杠删牌

//桌主更换
struct CMD_S_ChangeTableOwner
{
	word							wTableOwner;						//桌主玩家
};

//游戏状态
struct CMD_S_StatusFree
{
	longlong						lCellScore;							//基础金币
	word							wBankerUser;						//庄家用户
	bool							bTrustee[GAME_PLAYER];				//是否托管
    word							wTableOwner;	                    //房主位置
	byte							bMatch;								//比赛
};

//游戏状态
struct CMD_S_StatusPlay
{
	//游戏变量
	longlong						lCellScore;									//单元积分
	word							wBankerUser;								//庄家用户
	word							wCurrentUser;								//当前用户
	byte							bMatch;										//比赛

	//状态变量
	byte							cbActionCard;								//动作扑克
	byte							cbActionMask;								//动作掩码
	byte							cbLeftCardCount;							//剩余数目
	bool							bTrustee[GAME_PLAYER];						//是否托管

	//出牌信息
	word							wOutCardUser;								//出牌用户
	byte							cbOutCardData;								//出牌扑克
	byte							cbDiscardCount[GAME_PLAYER];				//丢弃数目
	byte							cbDiscardCard[GAME_PLAYER][60];				//丢弃记录

	//扑克数据
	byte							cbCardCount;								//扑克数目
	byte							cbCardData[MAX_COUNT];						//扑克列表
	byte							cbSendCardData;								//发送扑克

	//组合扑克
	byte							cbWeaveCount[GAME_PLAYER];					//组合数目
	CMD_WeaveItem					WeaveItemArray[GAME_PLAYER][MAX_WEAVE];		//组合扑克

	//堆立信息
	word							wHeapHead;									//堆立头部
	word							wHeapTail;									//堆立尾部
	byte							cbHeapCardInfo[GAME_PLAYER][2];				//堆牌信息
    word							wTableOwner;						        //桌主玩家
};

//游戏开始
struct CMD_S_GameStart
{
	longlong						lSiceCount;									//骰子点数
	word							wBankerUser;								//庄家用户
	word							wCurrentUser;								//当前用户
	byte							cbUserAction;								//用户动作
	byte							cbCardData[MAX_COUNT];						//扑克列表
	word							wHeapHead;									//堆立牌头
	word							wHeapTail;									//堆立牌尾
	byte							cbHeapCardInfo[GAME_PLAYER][2];				//堆立信息
};

//出牌命令
struct CMD_S_OutCard
{
	word							wOutCardUser;						//出牌用户
	byte							cbOutCardData;						//出牌扑克
};

//发送扑克
struct CMD_S_SendCard
{
	byte							cbCardData;							//扑克数据
	byte							cbActionMask;						//动作掩码
	word							wCurrentUser;						//当前用户
	word							wSendCardUser;						//发牌用户
	bool							bTail;								//末尾发牌
	byte							cbGangCardData;						//引杠特殊
};

//操作提示
struct CMD_S_OperateNotify
{
	word							wResumeUser;						//还原用户
	byte							cbActionMask;						//动作掩码
	byte							cbActionCard;						//动作扑克
};

//操作命令
struct CMD_S_OperateResult
{
	word							wOperateUser;						//操作用户
	byte							cbActionMask;						//动作掩码
	word							wProvideUser;						//供应用户
	byte							cbOperateCode;						//操作代码
	byte							cbOperateCard[3];					//操作扑克
};

//游戏结束
struct CMD_S_GameEnd
{
	longlong						lGameTax;							//游戏税收
	//结束信息
	word							wProvideUser;						//供应用户
	byte							cbProvideCard;						//供应扑克
	dword							dwChiHuKind[GAME_PLAYER];			//胡牌类型
	dword							dwChiHuRight[GAME_PLAYER][MAX_RIGHT_COUNT];		//胡牌类型

	//积分信息
	longlong						lGameScore[GAME_PLAYER];			//游戏积分
	longlong						lGangScore[GAME_PLAYER];			//杆牌积分

	//扑克信息
	byte							cbCardCount[GAME_PLAYER];			//扑克数目
	byte							cbCardData[GAME_PLAYER][MAX_COUNT];	//扑克数据

	word							wLeftUser;							//玩家逃跑
};

struct CMD_S_QGangCard
{
	byte							cbHuCard;							//胡的牌
	word							wProvideUser;						//供应用户
};

//用户托管
struct CMD_S_Trustee
{	
	bool							bTrustee;							//是否托管
	word							wChairID;							//托管用户
	bool							bSystemSet;							//系统设置
};

//补牌命令
struct CMD_S_ReplaceCard
{
	word							wReplaceUser;						//补牌用户
	byte							cbReplaceCard;						//补牌扑克
};

//////////////////////////////////////////////////////////////////////////
//客户端命令结构

#define SUB_C_OUT_CARD				1									//出牌命令
#define SUB_C_OPERATE_CARD			3									//操作扑克
#define SUB_C_TRUSTEE				4									//用户托管
#define SUB_C_REPLACE_CARD			5									//用户补牌
#define SUB_C_SET_BASE_SCORE		6									//设置底注

#define SUB_C_GETCARD               7                                   //获取底牌
#define SUB_S_SETCARD               8                                   //发送底牌
#define SUB_C_CARD_CONTROL			9									//扑克控制

#define SUB_C_SET_LOSER				10									//认输
#define SUB_C_ANDROID_EXIT			11									//机器人退出

struct CMD_C_CardControl
{
	byte cbCardIndex;
};

struct CMD_S_SETCARD
{
	byte  cbCardDatap[4][14];
};


//设置底注
struct CMD_C_SetBaseScore
{
	longlong						lBaseScore;							//游戏底注
};

//出牌命令
struct CMD_C_OutCard
{
	byte							cbCardData;							//扑克数据
};

//操作命令
struct CMD_C_OperateCard
{
	byte							cbOperateCode;						//操作代码
	byte							cbOperateCard[3];					//操作扑克
};

//用户托管
struct CMD_C_Trustee
{
	bool							bTrustee;							//是否托管
	bool							bSystemSet;							//系统设置
};

//补牌命令
struct CMD_C_ReplaceCard
{
	byte							cbCardData;							//扑克数据
};

//////////////////////////////////////////////////////////////////////////

#endif
