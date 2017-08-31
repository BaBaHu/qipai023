#ifndef CMD_FOURMJ_HEAD_FILE
#define CMD_FOURMJ_HEAD_FILE

//#pragma pack(1)
//////////////////////////////////////////////////////////////////////////
//公共宏定义

#define KIND_ID						301							//游戏 I D

//组件属性
#define GAME_PLAYER					4									//游戏人数

#define VERSION_SERVER				PROCESS_VERSION(6,0,3)				//程序版本
#define VERSION_CLIENT				PROCESS_VERSION(6,0,3)				//程序版本

#define GAME_NAME					TEXT("血战麻将")					//游戏名字
#define GAME_GENRE					(GAME_GENRE_SCORE|GAME_GENRE_MATCH|GAME_GENRE_GOLD)	//游戏类型

//游戏状态
#define GS_MJ_FREE					GAME_STATUS_FREE							//空闲状态
#define GS_MJ_PLAY					(GAME_STATUS_PLAY+1)						//游戏状态

//常量定义
#define MAX_WEAVE					4									//最大组合
#define MAX_INDEX					34									//最大索引
#define MAX_COUNT					14									//最大数目
#define MAX_REPERTORY				108									//最大库存
#define MAX_GANGCARD				11									//最大杠牌

//扑克定义
#define HEAP_FULL_COUNT				26									//堆立全牌

#define MAX_RIGHT_COUNT				1									//最大权位DWORD个数			

//////////////////////////////////////////////////////////////////////////

//组合子项
struct CMD_WeaveItem
{
	byte							cbWeaveKind;						//组合类型
	byte							cbCenterCard;						//中心扑克
	byte							cbPublicCard;						//公开标志
	word							wProvideUser;						//供应用户
	byte							cbCombinationCard;					//组合扑克
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
#define SUB_S_CHI_HU				108									//
#define SUB_S_GANG_SCORE			110									//
#define SUB_S_SELECT   			    111									//定缺花色
#define SUB_S_CHANGE_CARD			112									//换三张

//游戏状态
struct CMD_S_StatusFree
{
	longlong						lCellScore;							//基础金币
	word							wBankerUser;						//庄家用户
	bool							bTrustee[GAME_PLAYER];				//是否托管
	bool                            bAvertCheatMode;                    //是否防作弊  
};
//游戏状态
struct CMD_S_StatusPlay
{
	//游戏变量
	longlong						lCellScore;									//单元积分
	word							wBankerUser;								//庄家用户
	word							wCurrentUser;								//当前用户

	//状态变量
	byte							cbActionCard;								//动作扑克
	byte							cbActionMask;								//动作掩码
	byte							cbLeftCardCount;							//剩余数目
	bool							bTrustee[GAME_PLAYER];						//是否托管
	word							wWinOrder[GAME_PLAYER];						//胡牌顺序INVALID_CHAIR 表示没有胡牌，否则表示顺序，从1开始

	//出牌信息
	word							wOutCardUser;								//出牌用户
	byte							cbOutCardData;								//出牌扑克
	byte							cbDiscardCount[GAME_PLAYER];				//丢弃数目
	byte							cbDiscardCard[GAME_PLAYER][55];				//丢弃记录

	//扑克数据
	byte							cbCardCount;								//扑克数目
	byte							cbCardData[MAX_COUNT];						//扑克列表
	byte							cbSendCardData;								//发送扑克

	//组合扑克
	byte							cbWeaveCount[GAME_PLAYER];					//组合数目
	CMD_WeaveItem					WeaveItemArray[GAME_PLAYER][MAX_WEAVE];		//组合扑克

	//堆立信息
	word							wHeapHand;									//堆立头部
	word							wHeapTail;									//堆立尾部
	byte							cbHeapCardInfo[GAME_PLAYER][2];				//堆牌信息
	byte							cbSelectCard[GAME_PLAYER];					//定缺花色
	word							wProvider[GAME_PLAYER];						//胡牌提供玩家，用来判断是自摸还是抓炮
	byte							cbProvideCard[GAME_PLAYER];					//胡的哪张牌
	longlong						llChiHuScore[GAME_PLAYER];					//胡牌得分

	bool							bSelectColor;								//定缺结果
	//BYTE							cbSelectColor;								//定缺花色
	bool							bChanged;									//换牌结果
	//CMD_S_ChangeCard				ChangeCard;									//换牌数据
};

//游戏开始
struct CMD_S_GameStart
{
	byte                            wGameMode;                                  //游戏模式
	uint32							lSiceCount;									//骰子点数
	word							wBankerUser;								//庄家用户
	word							wCurrentUser;								//当前用户
	byte							cbUserAction;								//用户动作
	byte							cbCardData[MAX_COUNT*GAME_PLAYER];			//扑克列表
	word							wHeapHand;									//堆立牌头
	word							wHeapTail;									//堆立牌尾
	byte							cbHeapCardInfo[GAME_PLAYER][2];				//堆立信息
	byte							cbLeftCardCount;							
	bool							bGameMatch;									//是否比赛
	uint32							lCellScore;									//游戏底分
};

//定缺花色
struct CMD_S_SelectCard
{	
    word							wCurrentUser;								//当前用户
	byte                            wUserAction;                                //用户动作
	byte                            wSelectCard[GAME_PLAYER];                   //选择花色
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
	byte							cbGangCardData[MAX_GANGCARD];		//引杠特殊
	byte							cbActionMask;						//动作掩码
	word							wCurrentUser;						//当前用户
	bool							bTail;								//末尾发牌
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
	word							wProvideUser;						//供应用户
	byte							cbOperateCode;						//操作代码
	byte							cbOperateCard;						//操作扑克
	byte							cbCombinationCard;					//组合扑克
};

//游戏结束
struct CMD_S_GameEnd
{
	byte							cbCardCount[GAME_PLAYER];			//
	byte							cbCardData[GAME_PLAYER][MAX_COUNT];	//
	//结束信息
	word							wProvideUser[GAME_PLAYER];			//供应用户
	dword							dwChiHuRight[GAME_PLAYER];			//胡牌类型

	//积分信息
	longlong						lGameScore[GAME_PLAYER];			//游戏积分
	uint32							lGameTax[GAME_PLAYER];				//

	word							wWinOrder[GAME_PLAYER];				//胡牌排名

	longlong						lGangScore[GAME_PLAYER];			//详细得分
	byte							cbGenCount[GAME_PLAYER];			//
	word							wLostFanShu[GAME_PLAYER][GAME_PLAYER];
	word							wWinFanShu[GAME_PLAYER];
	word							wLeftUser;							//
	longlong						lChuShi;
	longlong						lDangQian;
};

//用户托管
struct CMD_S_Trustee
{
	bool							bTrustee;							//是否托管
	word							wChairID;							//托管用户
};

//
struct CMD_S_ChiHu
{
	word							wChiHuUser;							//
	word							wProviderUser;						//
	byte							cbChiHuCard;						//
	byte							cbCardCount;						//
	longlong						lGameScore;							//
	byte							cbWinOrder;							//
};

//
struct CMD_S_GangScore
{
	word							wChairId;							//
	byte							cbXiaYu;							//
	longlong						lGangScore[GAME_PLAYER];			//
};

struct CMD_S_ChangeCard
{
	word							wChangeDirection;					//兑换方向
	byte							cbCardData[MAX_COUNT*GAME_PLAYER];	//用户手牌
	byte							cbChangeCard[GAME_PLAYER][3];		//兑换手牌
};

//////////////////////////////////////////////////////////////////////////
//客户端命令结构

#define SUB_C_OUT_CARD				1									//出牌命令
#define SUB_C_OPERATE_CARD			3									//操作扑克
#define SUB_C_TRUSTEE				4									//用户托管
#define SUB_C_SELECT   			    5									//定缺花色
#define SUB_C_TYPE   				6									//控制消息
#define SUB_C_CONTROL   			7									//控制消息
#define SUB_C_LEAVE		   			8									//退出消息	
#define SUB_C_CHANGE				9									//换三张

//选牌命令
struct CMD_C_SelectCard
{
	byte							cbCardData;							//定缺数据
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
	byte							cbOperateCard;						//操作扑克
};

//用户托管
struct CMD_C_Trustee
{
	bool							bTrustee;							//是否托管	
};

struct CMD_C_Control
{
	uint32							ChuShi;							//初始库存
	uint32							DangQian;						//当前库存
	bool							bAction;						//是否执行
};

struct CMD_C_Type
{
	dword							UserID[3];						
	byte							Type1[3];
	bool							bAction;						//是否执行
};

//换牌操作
struct CMD_C_Change
{
	byte							cbCardData[3];						//换牌数据
};

//////////////////////////////////////////////////////////////////////////

//逻辑掩码

#define	MASK_COLOR					0xF0								//花色掩码
#define	MASK_VALUE					0x0F								//数值掩码

//////////////////////////////////////////////////////////////////////////
//动作定义

//动作标志
#define WIK_NULL					0x00								//没有类型
#define WIK_LEFT					0x01								//左吃类型
#define WIK_CENTER					0x02								//中吃类型
#define WIK_RIGHT					0x04								//右吃类型
#define WIK_PENG					0x08								//碰牌类型
#define WIK_GANG					0x10								//杠牌类型
#define WIK_LISTEN					0x20								//吃牌类型
#define WIK_CHI_HU					0x40								//吃胡类型
#define WIK_ZI_MO					0x80								//自摸
#define WIK_QIANG_GANG				0x90								//抢杠删除

//////////////////////////////////////////////////////////////////////////
//胡牌定义

//胡牌
#define CHK_NULL					0x00										//非胡类型
#define CHK_CHI_HU					0x01										//胡类型

#define CHR_QIANG_GANG				0x00000001									//抢杠
#define CHR_GANG_SHANG_PAO			0x00000002									//杠上炮
#define CHR_GANG_KAI				0x00000004									//杠上花
#define CHR_TIAN_HU					0x00000008									//天胡
#define CHR_DI_HU					0x00000010									//地胡
#define CHR_DA_DUI_ZI				0x00000020									//大对子
#define CHR_QING_YI_SE				0x00000040									//清一色
#define CHR_QI_XIAO_DUI				0x00000080									//暗七对
#define CHR_DAI_YAO				    0x00000100									//带幺
#define CHR_JIANG_DUI				0x00000200									//将对
#define CHR_SHU_FAN					0x00000400									//素番
#define CHR_QING_DUI				0x00000800									//清对
#define CHR_LONG_QI_DUI				0x00001000									//龙七对
#define CHR_QING_QI_DUI				0x00002000									//清七对
#define CHR_QING_YAO_JIU			0x00004000									//清幺九
#define CHR_QING_LONG_QI_DUI		0x00008000									//清龙七对
#define CHR_JING_GOU_GOU			0x00010000									//金钩钩
#define CHR_MENG_QING				0x00020000									//门清
#define CHR_ZHONG_JIANG				0x00040000									//中将
#define CHR_HAI_DI					0x00080000									//海底捞月
#define CHR_DIAN_GANG				0x00100000									//点杠花

//#pragma pack()
#endif
