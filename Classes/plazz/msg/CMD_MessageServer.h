#ifndef CMD_MESSAGE_HEAD_FILE
#define CMD_MESSAGE_HEAD_FILE

#pragma pack(1)


//////////////////////////////////////////////////////////////////////////////////
//携带信息

#define DTP_GP_UI_TASK_TARGET				1									//任务目标
#define DTP_GP_UI_TASK_ORDER				2									//任务说明
#define DTP_GP_UI_TASK_NAME					3									//任务名称
#define DTP_GP_UI_TASK_AWARD				4									//任务奖励


//////////////////////////////////////////////////////////////////////////////////
//聊天消息

#define MDM_GP_MSG_LOGON					1	//登陆消息

#define SUB_GP_MSG_SEND_LOGON				1	//发送登陆
#define SUB_GP_MSG_LOGON_FINISH				100	//登陆完成

//struct CMD_GP_MSGSendLogon
//{
//	DWORD			dwUserID;
//};

#define MDM_GP_CHAT							2	//聊天消息

//客户端发送
#define SUB_GP_C_USER_CHAT					1	//用户聊天
#define SUB_GP_C_USER_EXPRESSION			2	//用户表情

//服务端发送
#define SUB_GP_S_USER_CHAT					100	//用户聊天
#define SUB_GP_S_USER_EXPRESSION			101	//用户表情

////用户聊天
//struct CMD_GP_C_UserChat
//{
//	DWORD							dwUserID;							//用户ID
//	DWORD							dwChatColor;						//信息颜色
//	WORD							wChatLength;						//文字长度
//	TCHAR							szNickName[LEN_NICKNAME];			//用户昵称
//	TCHAR							szChatString[LEN_USER_CHAT];		//聊天信息
//};
//
////用户聊天
//struct CMD_GP_S_UserChat
//{
//	DWORD							dwUserID;							//用户ID
//	DWORD							dwChatColor;						//信息颜色
//	WORD							wChatLength;						//文字长度
//	TCHAR							szNickName[LEN_NICKNAME];			//用户昵称
//	TCHAR							szChatString[LEN_USER_CHAT];		//聊天信息
//};
//
////用户表情
//struct CMD_GP_C_UserExpression
//{
//	DWORD							dwUserID;							//用户ID
//	WORD							wItemIndex;							//表情索引
//	TCHAR							szNickName[LEN_NICKNAME];			//用户昵称
//};
//
////用户表情
//struct CMD_GP_S_UserExpression
//{
//	DWORD							dwUserID;							//用户ID
//	WORD							wItemIndex;							//表情索引
//	TCHAR							szNickName[LEN_NICKNAME];			//用户昵称
//};

#define MDM_GP_MSG_SYSTEM					3	//系统消息
#define SUB_GP_C_BUGLE_MESSAGE				1	//喇叭消息

#define SUB_GP_S_BUGLE_MESSAGE				101	//喇叭消息
#define SUB_GP_S_MESSAGE					102	//系统消息


////喇叭消息
//struct CMD_GP_C_BugleMessage
//{
//	DWORD							dwUserID;							//用户ID
//	BYTE							cbBugleType;						//喇叭类型 0：小喇叭 1：大喇叭
//	BYTE							cbCount;							//数量
//	DWORD							dwDelay;							//延迟
//	DWORD							dwChatColor;						//信息颜色
//	WORD							wChatLength;						//文字长度
//	TCHAR							szNickName[LEN_NICKNAME];			//用户昵称
//	TCHAR							szPassword[LEN_PASSWORD];			//登陆密码
//	TCHAR							szChatString[LEN_USER_CHAT];		//聊天信息
//};
//
////喇叭消息
//struct CMD_GP_S_BugleMessage
//{
//	DWORD							dwUserID;							//用户ID
//	BYTE							cbBugleType;						//喇叭类型
//	DWORD							dwChatColor;						//信息颜色
//	WORD							wChatLength;						//文字长度
//	TCHAR							szNickName[LEN_NICKNAME];			//用户昵称
//	TCHAR							szChatString[LEN_USER_CHAT];		//聊天信息
//};
//
////系统消息
//struct CMD_GP_SystemMessage
//{
//	WORD							wType;								//消息类型
//	WORD							wLength;							//消息长度
//	TCHAR							szMessage[128];						//消息内容
//};


//////////////////////////////////////////////////////////////////////////////////


//任务消息
#define MDM_GP_MSG_TASK								4	//任务消息

#define SUB_GP_C_LOGON_TASK							1	//登陆任务
#define SUB_GP_C_TASK_OPERATION						2	//登陆任务

#define SUB_GP_S_TASK_TYPE							101	//任务类型
#define SUB_GP_S_TASK_LIST							102	//任务列表
#define SUB_GP_S_TASK_OPERATION						103	//任务操作
#define SUB_GP_S_OPERATION_FAILE					104	//任务失败


////获取任务类型
//struct CMD_GP_C_GetTask 
//{
//	DWORD							dwUserID;						//用户ID
//};
//
////任务操作
//struct CMD_GP_C_TaskOperation
//{
//	DWORD							dwUserID;						//用户ID
//	WORD							wTaskID;						//任务ID
//	WORD							wTaskOperation;					//任务操作 0：领取任务 1：领取奖励
//};
//
//
////任务列表
//struct CMD_GP_LoadTaskList
//{
//	WORD							wTaskID;							//任务I	D
//	WORD							wTaskState;							//任务状态
//	WORD							wTaskTypeID;						//任务类型
//	WORD							wKindID;							//目标游戏
//	WORD							wTargetTotal;						//目标总数
//	WORD							wCompletionTotal;					//完成总数
//	WORD							wSortID;							//排序标示
//};
//
//
////任务操作
//struct CMD_GP_S_TaskOperation
//{
//	DWORD							dwUserID;						//用户ID
//	WORD							wTaskID;						//任务ID
//	WORD							wTaskOperation;					//任务操作 0：领取任务 1：领取奖励
//};
//
//
//
////失败消息
//struct CMD_GP_Faile
//{
//	int								nError;								//错误代码
//	TCHAR							szMessage[128];						//错误消息
//};






#pragma pack()

#endif



