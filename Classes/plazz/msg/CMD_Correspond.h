﻿#ifndef CMD_CORRESPOND_HEAD_FILE
#define CMD_CORRESPOND_HEAD_FILE

#pragma pack(1)

//////////////////////////////////////////////////////////////////////////////////
//注册命令

#define MDM_CS_REGISTER				1									//服务注册

//服务注册
#define SUB_CS_C_REGISTER_PLAZA		100									//注册广场
#define SUB_CS_C_REGISTER_SERVER	101									//注册房间

//注册结果
#define SUB_CS_S_REGISTER_FAILURE	200									//注册失败

//////////////////////////////////////////////////////////////////////////////////

////注册广场
//struct CMD_CS_C_RegisterPlaza
//{
//	TCHAR							szServerAddr[32];					//服务地址
//	TCHAR							szServerName[LEN_SERVER];			//服务器名
//};
//
////注册游戏
//struct CMD_CS_C_RegisterServer
//{
//	WORD							wKindID;							//名称索引
//	WORD							wNodeID;							//节点索引
//	WORD							wSortID;							//排序索引
//	WORD							wServerID;							//房间索引
//	WORD							wServerPort;						//房间端口
//	DWORD							dwServerRule;						//房间端口
//	DWORD							dwOnLineCount;						//在线人数
//	DWORD							dwFullCount;						//满员人数
//	TCHAR							szServerAddr[32];					//服务地址
//	TCHAR							szServerName[LEN_SERVER];			//房间名称
//
//
//	LONG							lCellScore;							//单位积分
//
//	//房间配置
//	SCORE							lRestrictScore;						//限制积分
//	SCORE							lMinTableScore;						//最低积分
//	SCORE							lMinEnterScore;						//最低积分
//	SCORE							lMaxEnterScore;						//最高积分
//};
//
////注册失败
//struct CMD_CS_S_RegisterFailure
//{
//	LONG							lErrorCode;							//错误代码
//	TCHAR							szDescribeString[128];				//错误消息
//};

//////////////////////////////////////////////////////////////////////////////////
//服务信息

#define MDM_CS_SERVICE_INFO			2									//服务信息

//房间信息
#define SUB_CS_C_SERVER_ONLINE		1									//房间人数
#define SUB_CS_C_SERVER_MODIFY		2									//房间修改

//广场命令
#define SUB_CS_S_PLAZA_INFO			100									//广场信息
#define SUB_CS_S_PLAZA_INSERT		101									//广场列表
#define SUB_CS_S_PLAZA_REMOVE		103									//广场删除
#define SUB_CS_S_PLAZA_FINISH		104									//广场完成

//房间命令
#define SUB_CS_S_SERVER_INFO		110									//房间信息
#define SUB_CS_S_SERVER_ONLINE		111									//房间人数
#define SUB_CS_S_SERVER_INSERT		112									//房间列表
#define SUB_CS_S_SERVER_MODIFY		113									//房间修改
#define SUB_CS_S_SERVER_REMOVE		114									//房间删除
#define SUB_CS_S_SERVER_FINISH				115									//房间完成


//////////////////////////////////////////////////////////////////////////////////

////房间数据
//struct CMD_CS_C_ServerModify
//{
//	WORD							wSortID;							//排序索引
//	WORD							wKindID;							//类型索引
//	WORD							wNodeID;							//节点索引
//	WORD							wServerPort;						//房间端口
//	DWORD							dwOnLineCount;						//在线人数
//	DWORD							dwFullCount;						//满员人数
//	TCHAR							szServerAddr[32];					//服务地址
//	TCHAR							szServerName[LEN_SERVER];			//房间名称
//};
//
////房间人数
//struct CMD_CS_C_ServerOnLine
//{
//	DWORD							dwOnLineCount;						//在线人数
//};

//比赛房间数据


//////////////////////////////////////////////////////////////////////////////////

////广场删除
//struct CMD_CS_S_PlazaRemove
//{
//	DWORD							dwPlazaID;							//广场标识
//};
//
////房间人数
//struct CMD_CS_S_ServerOnLine
//{
//	WORD							wServerID;							//房间标识
//	DWORD							dwOnLineCount;						//在线人数
//};
//
////房间修改
//struct CMD_CS_S_ServerModify
//{
//	WORD							wSortID;							//排序索引
//	WORD							wKindID;							//类型索引
//	WORD							wNodeID;							//节点索引
//	WORD							wServerID;							//房间标识
//	WORD							wServerPort;						//房间端口
//	DWORD							dwOnLineCount;						//在线人数
//	DWORD							dwFullCount;						//满员人数
//	TCHAR							szServerAddr[32];					//服务地址
//	//TCHAR							szServerAddr1[32];					//服务地址
//	TCHAR							szServerName[LEN_SERVER];			//房间名称
//};
//
////房间删除
//struct CMD_CS_S_ServerRemove
//{
//	WORD							wServerID;							//房间标识
//};

//比赛房间修改
//////////////////////////////////////////////////////////////////////////////////
//用户汇总

#define MDM_CS_USER_COLLECT			3									//用户汇总

//用户状态
#define SUB_CS_C_USER_ENTER			1									//用户进入
#define SUB_CS_C_USER_LEAVE			2									//用户离开
#define SUB_CS_C_USER_FINISH		3									//用户完成

//用户状态
#define SUB_CS_S_COLLECT_REQUEST	100									//汇总请求

//////////////////////////////////////////////////////////////////////////////////

////用户进入
//struct CMD_CS_C_UserEnter
//{
//	//用户信息
//	DWORD							dwUserID;							//用户标识
//	DWORD							dwGameID;							//游戏标识
//	TCHAR							szNickName[LEN_NICKNAME];			//用户昵称
//
//	//辅助信息
//	BYTE							cbGender;							//用户性别
//	BYTE							cbMemberOrder;						//会员等级
//	BYTE							cbMasterOrder;						//管理等级
//};
//
////用户离开
//struct CMD_CS_C_UserLeave
//{
//	DWORD							dwUserID;							//用户标识
//};

//////////////////////////////////////////////////////////////////////////////////
//远程服务

#define MDM_CS_REMOTE_SERVICE		4									//远程服务

//查找服务
#define SUB_CS_C_SEARCH_DATABASE	1									//数据查找
#define SUB_CS_C_SEARCH_CORRESPOND	2									//协调查找
#define SUB_CS_C_CUSTOMTABLE_CREATE 3									//user owner table

//查找结果
#define SUB_CS_S_SEARCH_DATABASE	100									//数据查找
#define SUB_CS_S_SEARCH_CORRESPOND	101									//协调查找
#define SUB_CS_S_CUSTOMTABLE_CREATE 110									//user owner table
#define SUB_GC_CUSTOMTABLE_RECYCLE	111									//自定义桌子回收
#define SUB_GC_UPDATE_ROOMCARD		112									//更新房卡
#define SUB_GL_UPDATE_USERCUST		113									//更新用户所在桌子
//////////////////////////////////////////////////////////////////////////////////

////协调查找
//struct CMD_CS_C_SearchCorrespond
//{
//	//连接参数
//	DWORD							dwSocketID;							//网络标识
//	DWORD							dwClientAddr;						//连接地址
//
//	//查找数据
//	DWORD							dwGameID;							//游戏标识
//	TCHAR							szNickName[LEN_NICKNAME];			//用户昵称
//};
//
////协调查找
//struct CMD_CS_S_SearchCorrespond
//{
//	//连接信息
//	DWORD							dwSocketID;							//网络标识
//	DWORD							dwClientAddr;						//连接地址
//
//	//数据信息
//	WORD							wUserCount;							//用户数目
//	tagUserRemoteInfo				UserRemoteInfo[16];					//用户信息
//};
//
////创建自定义桌子 
//struct CMD_CS_ReqCreateCustomTable
//{
//	DWORD						  dwUserID;						//用户id
//	BYTE							  cbRound;						//玩多少局
//	WORD							  wKindID;						//游戏类型id
//	SCORE						  llBaseScore;					//底分
//};
//
//struct CMD_SC_AckCreateCustomTable
//{
//	BYTE							  cbResult;						//结果 0成功 
//	DWORD						  dwUserID;						//用户id
//	WORD							  wServerID;						//服务器id
//	WORD							  wTableID;						//桌号
//};
//
////回收自定义桌子
//struct CMD_GC_RecycleTable
//{
//	DWORD						 dwUserID;
//	WORD							 wServerID;
//	WORD							 wTableID;
//};
//
////更新房卡
//struct CMD_GC_UpdateUserData
//{
//	enum eUpdataFlag
//	{
//		eUF_Score   =  (1<<0),
//		eUF_CustTT  =  (1<<1)
//	};
//	DWORD						 dwUserID;
//	SCORE						 lScore;
//	DWORD						 dwCustTUUID;
//	WORD							 wUpdateFlag;
//};
//////////////////////////////////////////////////////////////////////////////////
//管理服务

#define MDM_CS_MANAGER_SERVICE		5									//管理服务

#define SUB_CS_C_SYSTEM_MESSAGE 	1									//系统消息
#define SUB_CS_C_PROPERTY_TRUMPET 	2									//喇叭消息

#define SUB_CS_S_SYSTEM_MESSAGE 	100									//系统消息
#define SUB_CS_S_PROPERTY_TRUMPET  	200									//喇叭消息


////发送喇叭
//struct CMD_CS_S_SendTrumpet
//{
//	WORD                           wPropertyIndex;                      //道具索引 
//	DWORD                          dwSendUserID;                         //用户 I D
//	DWORD                          TrumpetColor;                        //喇叭颜色
//	TCHAR                          szSendNickName[32];				    //玩家昵称 
//	TCHAR                          szTrumpetContent[TRUMPET_MAX_CHAR];  //喇叭内容
//};
//////////////////////////////////////////////////////////////////////////////////


#pragma pack()

#endif