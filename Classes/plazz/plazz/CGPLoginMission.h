#ifndef _CGPLoginMission_H_
#define _CGPLoginMission_H_
#include "../Plazz.h"

#ifndef LOGIN_MISSION_SINK
#define LOGIN_MISSION_SINK
//////////////////////////////////////////////////////////////////////////
// 登陆提示
//////////////////////////////////////////////////////////////////////////
class IGPLoginMissionSink
{
public:
	virtual ~IGPLoginMissionSink(){}
	virtual void onGPLoginSuccess(){}
	virtual void onGPLoginComplete(){}
	virtual void onGPBaseEnsureComplete(bool bSuccessed, const char* szDescription){}
	virtual void onGPLoginFailure(const char* szDescription){}
	virtual void onGPError(int errorCode){}
};

#endif // LOGIN_MISSION_SINK

//帐号登录
struct tagGPLoginAccount
{
	//登录信息
	char							szAccounts[LEN_ACCOUNTS];			//登录帐号
	char							szPassword[LEN_MD5];				//登录密码
	byte							cbValidateFlags;			        //校验标识
};

//I D登录
struct tagGPLoginGameID
{
	//登录信息
	dword							dwGameID;							//游戏 I D
	char							szPassword[LEN_MD5];				//登录密码
	byte							cbValidateFlags;			        //校验标识
};

//帐号登录
struct tagGPLoginByType
{
	//登录信息
	byte							cbType;								//
	byte							cbSex;								//性别
	char							szAccounts[LEN_ACCOUNTS];			//登录帐号
	char							szNickName[LEN_ACCOUNTS];			//昵称
	char							szIconUrl[256];						//登录密码
	byte							cbValidateFlags;			        //校验标识
};

//注册帐号
struct tagGPRegisterAccount
{
	//密码变量
	char							szLogonPass[LEN_MD5];				//登录密码
	char							szInsurePass[LEN_MD5];				//银行密码

	//注册信息
	word							wFaceID;							//头像标识
	byte							cbGender;							//用户性别
	char							szAccounts[LEN_ACCOUNTS];			//登录帐号
	char							szNickName[LEN_NICKNAME];			//用户昵称
	char							szSpreader[LEN_ACCOUNTS];			//推荐帐号
	char							szPassPortID[LEN_PASS_PORT_ID];		//证件号码
	char							szCompellation[LEN_COMPELLATION];	//真实名字
	byte							cbValidateFlags;			        //校验标识
};


class CGPLoginMission
	: public CSocketMission
{
public:
	CGPLoginMission(const std::string& url, int port);

	//////////////////////////////////////////////////////////////////////////
	// 登陆
public:
	// 设置回调接口
	void setMissionSink(IGPLoginMissionSink* pIGPLoginMissionSink);
	// 账号登陆
	void loginAccount(const tagGPLoginAccount& LoginAccount);
	// I D登陆
	void loginGameID(const tagGPLoginGameID& LoginGameID);
	// 类型登陆
	void loginType(const tagGPLoginByType& LoginType);
	// 注册
	void registerAccount(const tagGPRegisterAccount& RegisterAccount);
	//更新人数
	void updateOnlineInfo();
	//更新类型
	void updateServerInfo(uint16 kind);
	void getBaseEnsureTake();
private:
	//////////////////////////////////////////////////////////////////////////
	// 登陆
	bool sendLoginAccount(const tagGPLoginAccount& LoginAccount);
	// 登陆
	bool sendLoginGameID(const tagGPLoginGameID& LoginGameID);
	// 登陆
	bool sendLoginType(const tagGPLoginByType& LoginType);
	// 注册
	bool sendRegisterPacket(const tagGPRegisterAccount& RegisterAccount);
	// 更新人数
	bool sendUpdateOnlineInfoPacket();
	// 更新类型房间列表
	void sendUpdateServerInfo();
	bool sendBaseEnsureTake();
	//////////////////////////////////////////////////////////////////////////
	// ISocketEngineSink
public:
	virtual void onEventTCPSocketLink();
	virtual void onEventTCPSocketShut();
	virtual void onEventTCPSocketError(int errorCode);
	virtual bool onEventTCPSocketRead(int main, int sub, void* data, int dataSize);
private:
	//////////////////////////////////////////////////////////////////////////
	// 登陆信息
	bool onSocketMainLogon(int sub, void* data, int size);
	//登录成功
	bool onSocketSubLogonSuccess(void* data, int size);
	//登录失败
	bool onSocketSubLogonFailure(void* data, int size);
	//登录完成
	bool onSocketSubLogonFinish(void* data, int size);
	//升级提示
	bool onSocketSubUpdateNotify(void* data, int size);
	//登录失败(密保卡)
	bool onSocketSubLogonValidateMBCard(void* data, int size);
		
	//////////////////////////////////////////////////////////////////////////
	// 列表信息
	bool onSocketMainServerList(int sub, void* data, int size);
	//种类信息
	bool onSocketListType(void* data, int size);
	//类型信息
	bool onSocketListKind(void* data, int size);
	//节点信息
	bool onSocketListNode(void* data, int size);
	//页面信息
	bool onSocketListPage(void* data, int size);
	//房间信息
	bool onSocketListServer(void* data, int size);
	//列表完成
	bool onSocketListFinish(void* data, int size);

	//房间完成
	bool onSocketServerFinish(void* data, int size);
	//视频配置
	bool onSocketVideoOption(void* data, int size);

	//类型在线
	bool onSocketKindOnline(void* data, int size);
	//房间在线
	bool onSocketServerOnline(void* data, int size);
	//在线完成更新完成
	bool onSocketOnlineFinish(void* data, int size);
	//房间列表
	bool OnSubCustomServerList(void* data, int size);
	//自定义房间列表
	bool onSocketListCustomServer(void* data, int size);
	//请求自定义桌子列表
	bool onSocketCustomTableList(void* data, int size);

	bool onSocketBaseEnsureResult(void* data, int size);
private:
	// 回调
	IGPLoginMissionSink* mIGPLoginMissionSink;

	// 任务类型
	uint8 mMissionType;
	// 登陆数据
	tagGPLoginAccount	mLoginAccount;
	// 登陆数据
	tagGPLoginGameID	mLoginGameID;
	// 登陆数据
	tagGPLoginByType	mLoginType;
	// 注册数据
	tagGPRegisterAccount mRegisterAccount;

	// 更新类型
	typedef std::list<uint16>	KIND_LIST;
	typedef KIND_LIST::iterator KIND_ITER;

	KIND_LIST mKindList;
	KIND_LIST mKindWaitList;
}; // CGPLoginMission

#endif // _CGPLoginMission_H_