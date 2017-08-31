#ifndef CMD_LONGON_HEAD_FILE
#define CMD_LONGON_HEAD_FILE

#pragma pack(1)

//////////////////////////////////////////////////////////////////////////

struct systemtime {
	word wYear;
	word wMonth;
	word wDayOfWeek;
	word wDay;
	word wHour;
	word wMinute;
	word wSecond;
	word wMilliseconds;
};

//////////////////////////////////////////////////////////////////////////////////
//登录命令

#define MDM_GP_LOGON				1									//广场登录

//登录模式
#define SUB_GP_LOGON_GAMEID			1									//I D 登录
#define SUB_GP_LOGON_ACCOUNTS		2									//帐号登录
#define SUB_GP_REGISTER_ACCOUNTS	3									//注册帐号
#define SUB_GP_QQ_LOGON_ACCOUNTS	4									//QQ帐号登录 改动过
#define SUB_GP_WX_LOGON_ACCOUNTS	5									//微信帐号登录改动过
#define SUB_GP_BASEENSURE_TAKE		10									//领取救济金改动过

//登录结果
#define SUB_GP_LOGON_SUCCESS		100									//登录成功
#define SUB_GP_LOGON_FAILURE		101									//登录失败
#define SUB_GP_LOGON_FINISH			102									//登录完成
#define SUB_GP_VALIDATE_MBCARD      103                                 //登录失败
#define SUB_GP_LOGON_TIPS			104                                 //登录提示
//升级提示
#define SUB_GP_UPDATE_NOTIFY		200									//升级提示

//救济金
#define SUB_GP_BASEENSURE_RESULT	300									//救济金结果改动过

//////////////////////////////////////////////////////////////////////////////////
//

#define MB_VALIDATE_FLAGS           0x01                                //效验密保
#define LOW_VER_VALIDATE_FLAGS      0x02                                //效验低版本
//
////I D 登录
//struct CMD_GP_LogonGameID
//{
//	//系统信息
//	byte                            cbDeviceType;                       //设备类型
//	word							wModuleID;							//模块标识(KindID)
//	dword							dwPlazaVersion;						//广场版本
//	tchar							szMachineID[LEN_MACHINE_ID];		//机器序列
//	tchar							szMobilePhone[LEN_MOBILE_PHONE];	//电话号码(手机用)
//
//	//登录信息
//	dword							dwGameID;							//游戏 I D
//	tchar							szPassword[LEN_MD5];				//登录密码
//	byte							cbValidateFlags;			        //校验标识(手机没有密保)
//};
//
////帐号登录
//struct CMD_GP_LogonAccounts
//{
//	//系统信息
//	byte                            cbDeviceType;                       //设备类型
//	word							wModuleID;							//模块标识(KindID)
//	dword							dwPlazaVersion;						//广场版本
//	tchar							szMachineID[LEN_MACHINE_ID];		//机器序列
//	tchar							szMobilePhone[LEN_MOBILE_PHONE];	//电话号码(手机用)
//
//	//登录信息
//	tchar							szPassword[LEN_MD5];				//登录密码
//	tchar							szAccounts[LEN_ACCOUNTS];			//登录帐号
//	byte							cbValidateFlags;			        //校验标识(手机没有密保)
//};
//
//
////注册帐号
//struct CMD_GP_RegisterAccounts
//{
//	//系统信息
//	byte                            cbDeviceType;                       //设备类型
//	word							wModuleID;							//模块标识(KindID)
//	dword							dwPlazaVersion;						//广场版本
//	tchar							szMachineID[LEN_MACHINE_ID];		//机器序列
//	tchar							szMobilePhone[LEN_MOBILE_PHONE];	//电话号码(手机用)
//
//	//密码变量
//	tchar							szLogonPass[LEN_MD5];				//登录密码
//	tchar							szInsurePass[LEN_MD5];				//银行密码
//
//	//注册信息
//	word							wFaceID;							//头像标识
//	byte							cbGender;							//用户性别
//	tchar							szAccounts[LEN_ACCOUNTS];			//登录帐号
//	tchar							szNickName[LEN_NICKNAME];			//用户昵称
//	tchar							szSpreader[LEN_ACCOUNTS];			//推荐帐号(手机目前没有)
//	tchar							szPassPortID[LEN_PASS_PORT_ID];		//证件号码(手机目前没有)
//	tchar							szCompellation[LEN_COMPELLATION];	//真实名字(手机目前没有)
//	byte							cbValidateFlags;			        //校验标识(手机目前没有)
//};


//struct CMD_GP_LogonAccounts_By_QQ//改动过
//{
//	//系统信息
//	DWORD							dwPlazaVersion;						//广场版本
//	DWORD							dwClientAddr;						//客户端IP
//	TCHAR							szMachineID[LEN_MACHINE_ID];		//机器序列
//
//	BYTE							cbGender;							//用户性别
//	TCHAR							szAccounts[LEN_ACCOUNTS];			//登录帐号
//	TCHAR							szNickName[LEN_NICKNAME];			//用户昵称
//	TCHAR							szIconUrl[256];						//用户头像url
//
//	BYTE							cbValidateFlags;			        //校验标识
//};
//
//struct CMD_GP_LogonAccounts_By_WX//改动过
//{
//	//系统信息
//	DWORD							dwPlazaVersion;						//广场版本
//	DWORD							dwClientAddr;						//客户端IP
//	TCHAR							szMachineID[LEN_MACHINE_ID];		//机器序列
//
//	BYTE							cbGender;							//用户性别
//	TCHAR							szAccounts[LEN_ACCOUNTS];			//登录帐号
//	TCHAR							szNickName[LEN_NICKNAME];			//用户昵称
//	TCHAR							szIconUrl[256];						//用户头像url
//
//	BYTE							cbValidateFlags;			        //校验标识
//};

////登录成功
//struct CMD_GP_LogonSuccess
//{
//	//属性资料
//	word							wFaceID;							//头像标识
//	dword							dwUserID;							//用户 I D
//	dword							dwGameID;							//游戏 I D
//	dword							dwGroupID;							//社团标识
//	dword							dwCustomID;							//自定标识
//	dword							dwUserMedal;						//用户奖牌
//	dword							dwExperience;						//经验数值
//	dword							dwLoveLiness;						//用户魅力
//	dword							dwMasterRight;						//管理员权限
//
//	//用户成绩
//	SCORE							lUserScore;							//用户金币
//	SCORE							lUserInsure;						//用户银行
//
//	//用户信息
//	byte							cbGender;							//用户性别
//	byte							cbMoorMachine;						//锁定机器
//	wchar_t 						szAccounts[LEN_ACCOUNTS];			//登录帐号
//	wchar_t 						szNickName[LEN_ACCOUNTS];			//用户昵称
//	wchar_t 						szGroupName[LEN_GROUP_NAME];		//社团名字
//  byte							cbDailiOrder;						//代理等级
//  登录类型
//	byte							cbUserType;							//登录类型

//
//	//配置信息
//	byte                            cbShowServerStatus;                 //显示服务器状态
// //登录地址
//  byte							cbServerIPType;						//服务类型
// //房卡 改动过
//  uint32							lRoomCard;
//};

////登录失败
//struct CMD_GP_LogonFailure
//{
//	uint32							lResultCode;						//错误代码
//	tchar							szDescribeString[128];				//描述消息
//};
//
////登陆完成
//struct CMD_GP_LogonFinish
//{
//	word							wIntermitTime;						//中断时间
//	word							wOnLineCountTime;					//更新时间
//  dword							dwExtData0;							//附加数据 改动过
//};
//
////登录失败
//struct CMD_GP_ValidateMBCard
//{
//	uint								uMBCardID;						//机器序列
//};
//
////升级提示
//struct CMD_GP_UpdateNotify
//{
//	byte							cbMustUpdate;						//强行升级
//	byte							cbAdviceUpdate;						//建议升级
//	dword							dwCurrentVersion;					//当前版本
//};

//////////////////////////////////////////////////////////////////////////////////
//携带信息 CMD_GP_LogonSuccess

#define DTP_GP_GROUP_INFO			1									//社团信息
#define DTP_GP_MEMBER_INFO			2									//会员信息
#define	DTP_GP_UNDER_WRITE			3									//个性签名
#define DTP_GP_STATION_URL			4									//主页信息
#define DTP_GP_ICON_URL				5									
////社团信息
//struct DTP_GP_GroupInfo
//{
//	dword							dwGroupID;							//社团索引
//	tchar							szGroupName[LEN_GROUP_NAME];		//社团名字
//};
//
////会员信息
//struct DTP_GP_MemberInfo
//{
//	byte							cbMemberOrder;						//会员等级
//	systemtime						MemberOverDate;						//到期时间
//};

//////////////////////////////////////////////////////////////////////////////////
//列表命令

#define MDM_GP_SERVER_LIST			2									//列表信息

//获取命令
#define SUB_GP_GET_LIST				1									//获取列表
#define SUB_GP_GET_SERVER			2									//获取房间
#define SUB_GP_GET_ONLINE			3									//获取在线
#define SUB_GP_GET_COLLECTION		4									//获取收藏

//列表信息
#define SUB_GP_LIST_TYPE			100									//类型列表
#define SUB_GP_LIST_KIND			101									//种类列表
#define SUB_GP_LIST_NODE			102									//节点列表
#define SUB_GP_LIST_PAGE			103									//定制列表
#define SUB_GP_LIST_SERVER			104									//房间列表
#define SUB_GP_VIDEO_OPTION			105									//视频配置
#define SUB_GP_LIST_CTSERVER		106									//房间列表 改动过
#define SUB_GP_LIST_CUSTSERVER		107									//自定义房间列表 改动过

//完成信息
#define SUB_GP_LIST_FINISH			200									//发送完成
#define SUB_GP_SERVER_FINISH		201									//房间完成

//在线信息
#define SUB_GR_KINE_ONLINE			300									//类型在线
#define SUB_GR_SERVER_ONLINE		301									//房间在线
#define SUB_GR_ONLINE_FINISH		302									//在线完成

//////////////////////////////////////////////////////////////////////////////////
//
////获取在线
//struct CMD_GP_GetOnline
//{
//	word							wServerCount;						//房间数目
//	word							wOnLineServerID[MAX_SERVER];		//房间标识
//};
//
////类型在线
//struct CMD_GP_KindOnline
//{
//	word							wKindCount;							//类型数目
//	tagOnLineInfoKind				OnLineInfoKind[MAX_KIND];			//类型在线
//};
//
////房间在线
//struct CMD_GP_ServerOnline
//{
//	word							wServerCount;						//房间数目
//	tagOnLineInfoServer				OnLineInfoServer[MAX_SERVER];		//房间在线
//};

//////////////////////////////////////////////////////////////////////////////////
//服务命令

#define MDM_GP_USER_SERVICE			3									//用户服务

//账号服务
#define SUB_GP_MODIFY_MACHINE		100									//修改机器
#define SUB_GP_MODIFY_LOGON_PASS	101									//修改密码
#define SUB_GP_MODIFY_INSURE_PASS	102									//修改密码
#define SUB_GP_MODIFY_UNDER_WRITE	103									//修改签名

//修改头像
#define SUB_GP_USER_FACE_INFO		200									//头像信息
#define SUB_GP_SYSTEM_FACE_INFO		201									//系统头像
#define SUB_GP_CUSTOM_FACE_INFO		202									//自定头像

//个人资料
#define SUB_GP_USER_INDIVIDUAL		301									//个人资料
#define	SUB_GP_QUERY_INDIVIDUAL		302									//查询信息
#define SUB_GP_MODIFY_INDIVIDUAL	303									//修改资料

//银行服务
#define SUB_GP_USER_SAVE_SCORE		400									//存款操作
#define SUB_GP_USER_TAKE_SCORE		401									//取款操作
#define SUB_GP_USER_TRANSFER_SCORE	402									//转账操作
#define SUB_GP_USER_INSURE_INFO		403									//银行资料
#define SUB_GP_QUERY_INSURE_INFO	404									//查询银行
#define SUB_GP_USER_INSURE_SUCCESS	405									//银行成功
#define SUB_GP_USER_INSURE_FAILURE	406									//银行失败
#define SUB_GP_QUERY_USER_INFO_REQUEST	407								//查询用户
#define SUB_GP_QUERY_USER_INFO_RESULT	408								//用户信息
#define SUB_GP_USER_TRANSFER_ROOMC	409									//转账房卡操作 改动过
#define SUB_GP_USER_ROOMC_SUCCESS	410									//房卡成功 改动过

//兑换道具
#define SUB_GP_EXCHANGE				500									//兑换道具
#define SUB_GP_EXCHANGE_RESULT		501									//兑换结果

//客服信息
#define SUB_GP_KEFU					600									//客服信息
#define SUB_GP_KEFU_RESULT			601									//客服信息结果

//邮件信息
#define SUB_GP_MESSAGE_LIST			700									//邮件列表
#define SUB_GP_MESSAGE_LIST_RESULT	701									//邮件列表返回
#define SUB_GP_MESSAGE_AWARD		702									//获取排行榜奖励
#define SUB_GP_MESSAGE_AWARD_RESULT	703									//获取排行榜结果

//操作结果
#define SUB_GP_OPERATE_SUCCESS		900									//操作成功
#define SUB_GP_OPERATE_FAILURE		901									//操作失败

//////////////////////////////////////////////////////////////////////////////////
//
////修改密码
//struct CMD_GP_ModifyLogonPass
//{
//	dword							dwUserID;							//用户 I D
//	tchar							szDesPassword[LEN_PASSWORD];		//用户密码
//	tchar							szScrPassword[LEN_PASSWORD];		//用户密码
//};
//
////修改密码
//struct CMD_GP_ModifyInsurePass
//{
//	dword							dwUserID;							//用户 I D
//	tchar							szDesPassword[LEN_PASSWORD];		//用户密码
//	tchar							szScrPassword[LEN_PASSWORD];		//用户密码
//};
//
////修改签名
//struct CMD_GP_ModifyUnderWrite
//{
//	dword							dwUserID;							//用户 I D
//	tchar							szPassword[LEN_PASSWORD];			//用户密码
//	tchar							szUnderWrite[LEN_UNDER_WRITE];		//个性签名
//};

//////////////////////////////////////////////////////////////////////////////////
//
////用户头像
//struct CMD_GP_UserFaceInfo
//{
//	word							wFaceID;							//头像标识
//	dword							dwCustomID;							//自定标识
//};
//
////修改头像
//struct CMD_GP_SystemFaceInfo
//{
//	word							wFaceID;							//头像标识
//	dword							dwUserID;							//用户 I D
//	tchar							szPassword[LEN_PASSWORD];			//用户密码
//	tchar							szMachineID[LEN_MACHINE_ID];		//机器序列
//};
//
////修改头像
//struct CMD_GP_CustomFaceInfo
//{
//	dword							dwUserID;							//用户 I D
//	tchar							szPassword[LEN_PASSWORD];			//用户密码
//	tchar							szMachineID[LEN_MACHINE_ID];		//机器序列
//	dword							dwCustomFace[FACE_CX*FACE_CY];		//图片信息
//};
//
////////////////////////////////////////////////////////////////////////////////////
//
////绑定机器
//struct CMD_GP_ModifyMachine
//{
//	byte							cbBind;								//绑定标志
//	dword							dwUserID;							//用户标识
//	tchar							szPassword[LEN_PASSWORD];			//用户密码
//	tchar							szMachineID[LEN_MACHINE_ID];		//机器序列
//};
//
////////////////////////////////////////////////////////////////////////////////////
//
////个人资料
//struct CMD_GP_UserIndividual
//{
//	dword							dwUserID;							//用户 I D
//};
//
////查询信息
//struct CMD_GP_QueryIndividual
//{
//	dword							dwUserID;							//用户 I D
//};
//
////修改资料
//struct CMD_GP_ModifyIndividual
//{
//	byte							cbGender;							//用户性别
//	dword							dwUserID;							//用户 I D
//	tchar							szPassword[LEN_PASSWORD];			//用户密码
//};

//////////////////////////////////////////////////////////////////////////////////
//携带信息 CMD_GP_UserIndividual

#define DTP_GP_UI_NICKNAME			1									//用户昵称
#define DTP_GP_UI_USER_NOTE			2									//用户说明
#define DTP_GP_UI_UNDER_WRITE		3									//个性签名
#define DTP_GP_UI_QQ				4									//Q Q 号码
#define DTP_GP_UI_EMAIL				5									//电子邮件
#define DTP_GP_UI_SEAT_PHONE		6									//固定电话
#define DTP_GP_UI_MOBILE_PHONE		7									//移动电话
#define DTP_GP_UI_COMPELLATION		8									//真实名字
#define DTP_GP_UI_DWELLING_PLACE	9									//联系地址

//////////////////////////////////////////////////////////////////////////////////
//
//银行资料
//struct CMD_GP_UserInsureInfo
//{
//	word							wRevenueTake;						//税收比例
//	word							wRevenueTransfer;					//税收比例
//	word							wServerID;							//房间标识
//	SCORE							lUserScore;							//用户金币
//	SCORE							lUserInsure;						//银行金币
//	SCORE							lTransferPrerequisite;				//转账条件
//  dword							dwUserMedal;						//
//  int								nRoomCard;                                //改动过
//};
//
////存入金币
//struct CMD_GP_UserSaveScore
//{
//	dword							dwUserID;							//用户 I D
//	SCORE							lSaveScore;							//存入金币
//	tchar							szMachineID[LEN_MACHINE_ID];		//机器序列
//};
//
////提取金币
//struct CMD_GP_UserTakeScore
//{
//	dword							dwUserID;							//用户 I D
//	SCORE							lTakeScore;							//提取金币
//	tchar							szPassword[LEN_MD5];				//银行密码
//	tchar							szMachineID[LEN_MACHINE_ID];		//机器序列
//};
//
////转账金币
//struct CMD_GP_UserTransferScore
//{
//	dword							dwUserID;							//用户 I D
//	byte                            cbByNickName;                       //昵称赠送
//	SCORE							lTransferScore;						//转账金币
//	tchar							szPassword[LEN_MD5];				//银行密码
//	tchar							szNickName[LEN_NICKNAME];			//目标用户
//	tchar							szMachineID[LEN_MACHINE_ID];		//机器序列
//};
//
////银行成功
//struct CMD_GP_UserInsureSuccess
//{
//	dword							dwUserID;							//用户 I D
//	SCORE							lUserScore;							//用户金币
//	SCORE							lUserInsure;						//银行金币
//	tchar							szDescribeString[128];				//描述消息
//};
//

////房卡成功 改动过
//struct CMD_GP_UserRoomCardSuccess
//{
//	dword							dwUserID;							//用户 I D
//	int								lRoomCard;							//房卡
//	tchar							szDescribeString[128];				//描述消息
//};

////银行失败
//struct CMD_GP_UserInsureFailure
//{
//	uint32							lResultCode;						//错误代码
//	tchar							szDescribeString[128];				//描述消息
//};
//
////提取结果
//struct CMD_GP_UserTakeResult
//{
//	dword							dwUserID;							//用户 I D
//	SCORE							lUserScore;							//用户金币
//	SCORE							lUserInsure;						//银行金币
//};
//
////查询银行
//struct CMD_GP_QueryInsureInfo
//{
//	dword							dwUserID;							//用户 I D
//};
//
////查询用户
//struct CMD_GP_QueryUserInfoRequest
//{
//	byte                            cbByNickName;                       //昵称赠送
//	tchar							szNickName[LEN_NICKNAME];			//目标用户
//};
//
////用户信息
//struct CMD_GP_UserTransferUserInfo
//{
//	dword							dwTargetGameID;						//目标用户
//	tchar							szNickName[LEN_NICKNAME];			//目标用户
//};

//////////////////////////////////////////////////////////////////////////////////
//
////操作失败
//struct CMD_GP_OperateFailure
//{
//	uint32							lResultCode;						//错误代码
//	tchar							szDescribeString[128];				//描述消息
//};
//
////操作成功
//struct CMD_GP_OperateSuccess
//{
//	uint32							lResultCode;						//操作代码
//	tchar							szDescribeString[128];				//成功消息
//};

////领取低保
//struct CMD_GP_BaseEnsureTake
//{
//	DWORD							dwUserID;							//用户 I D
//	TCHAR							szPassword[LEN_PASSWORD];			//登录密码
//	TCHAR							szMachineID[LEN_MACHINE_ID];		//机器序列
//};
//
////低保结果
//struct CMD_GP_BaseEnsureResult
//{
//	bool							bSuccessed;							//成功标识
//	SCORE							lGameScore;							//当前游戏币
//	TCHAR							szNotifyContent[128];				//提示内容
//};

//////////////////////////////////////////////////////////////////////////////////
//远程服务

#define MDM_GP_REMOTE_SERVICE		4									//远程服务

//查找服务
#define SUB_GP_C_SEARCH_DATABASE	100									//数据查找
#define SUB_GP_C_SEARCH_CORRESPOND	101									//协调查找

//时间奖励
#define SUB_GP_C_TIME_AWARD_CHECK	110									//时间奖励信息查询
#define SUB_GP_C_TIME_AWARD_GET		111									//时间奖励领取

//查找服务
#define SUB_GP_S_SEARCH_DATABASE	200									//数据查找
#define SUB_GP_S_SEARCH_CORRESPOND	201									//协调查找


//时间奖励
#define SUB_GP_S_TIME_AWARD_CHECK	210									//时间奖励信息查询结果
#define SUB_GP_S_TIME_AWARD_GET		211									//时间奖励领取结果

//////////////////////////////////////////////////////////////////////////////////
//
////协调查找
//struct CMD_GP_C_SearchCorrespond
//{
//	dword							dwGameID;							//游戏标识
//	tchar							szNickName[LEN_NICKNAME];			//用户昵称
//};
//
////协调查找
//struct CMD_GP_S_SearchCorrespond
//{
//	word							wUserCount;							//用户数目
//	tagUserRemoteInfo				UserRemoteInfo[16];					//用户信息
//};

//////////////////////////////////////////////////////////////////////////////////

//自定义桌子消息
#define SUB_C2L_CUSTOMTABLE_CREATE  10									//创建自定义房间(桌子) 改动过
#define SUB_C2L_CUSTOMTABLE_ENTER   11									//进入自定义房间(桌子) 改动过
#define SUB_C2L_CUSTOMTABLE_LIST    12									//请求自定义桌子列表 ( 大厅登录成功主动请求)改动过
#define SUB_L2C_CUSTOMTABLE_CREATE  210									//创建自定义房间(桌子)回复改动过
#define SUB_L2C_CUSTOMTABLE_ENTER   211									//进入自定义房间(桌子)回复改动过
#define SUB_L2C_CUSTOMTABLE_LIST    212									//请求自定义桌子列表改动过
////列表命令改动过
//struct CMD_C2L_ReqCreateCustomTable
//{
//	DWORD	dwUserID;											//玩家id
//	BYTE		cbRound;												//玩多少局
//	WORD		wKindID;												//游戏类型id
//	SCORE	llBaseScore;											//底分
//};
////改动过
//struct CMD_L2C_AckCreateCustomTable
//{
//	BYTE							cbResult;						//结果(0成功 1,超时)
//	WORD							wServerID;						//房间索引
//	WORD							wKindID;							//类型id
//	WORD							wServerPort;						//房间端口
//	TCHAR						szServerAddr[32];					//房间地址
//	TCHAR						szServerName[LEN_SERVER];			//房间名称
//	DWORD						dwRoomVerifyID;					//房间号码
//};
////改动过
//struct CMD_C2L_ReqEnterCustomTable
//{
//	DWORD						dwRoomVerifyID;					//房间号码						
//};
////改动过
//struct CMD_L2C_AckEnterCustomTable
//{
//	BYTE							cbResult;						//结果
//	WORD							wServerID;						//房间索引
//	WORD							wServerPort;						//房间端口
//	TCHAR						szServerAddr[32];					//房间地址
//};
////改动过
//struct CMD_C2L_ReqCustomTableList
//{
//	DWORD						dwUserID;
//};
#define SUB_MB_PAY_INFO				601
#define SUB_MB_PAY_RESULT			602
#define SUB_MB_SHARE_INFO			603									//分享
#define SUB_MB_SHARE_RESULT			604									//分享结果
#define SUB_MB_PAY_CARD				605									//
#define SUB_MB_PAY_CARD_RESULT		606									//

//struct CMD_MB_PayCard
//{
//	DWORD							dwUserID;							//
//	TCHAR							szMBCard[16];							//
//	TCHAR							szMBPassword[33];						//
//};
////
//struct CMD_MB_PayCardResult
//{
//	DWORD							dwUserID;							//
//  SCORE							lScore;
//	TCHAR							szNotifyContent[128];
//};


////充值
//struct CMD_GP_PayInfo
//{
//	//用户信息
//	DWORD							dwUserID;							//用户ID
//
//	//充值信息
//	BYTE							cbBuyType;							//购买类型
//	LONGLONG						lBuyCount;							//购买数量
//	LONGLONG						lPayRMB;							//支付数量
//
//	//充值渠道
//	BYTE							cbPayType;							//支付渠道
//
//};

//struct CMD_MB_PayResult
//{
//	//用户信息
//	DWORD							dwUserID;							//用户ID
//};

////分享
//struct CMD_MB_Share
//{
//	DWORD							dwUserID;							//
//};
//
//struct CMD_MB_ShareResult
//{
//	DWORD							dwUserID;							//
//  SCORE							lScore;	 //赠送金币（银行）
//  DWORD							dwRoomCard;	 //赠送房卡
//	TCHAR							szNotifyContent[128];
//};

#pragma pack()

#endif