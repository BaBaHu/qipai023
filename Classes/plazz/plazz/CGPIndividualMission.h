#ifndef _CGPIndividualMission_H_
#define _CGPIndividualMission_H_
#include "../Plazz.h"

#define MISSION_INDIVIDUAL_NULL		0
#define MISSION_INDIVIDUAL_QUERY	1
#define MISSION_INDIVIDUAL_MODIFY	2

//////////////////////////////////////////////////////////////////////////
// 用户资料修改结构
//////////////////////////////////////////////////////////////////////////
struct tagModifyIndividual
{
	// 性别
	uint8 cbGender;
	//用户昵称
	char szNickName[LEN_NICKNAME];
	//个性签名
	char szUnderWrite[LEN_UNDER_WRITE];
	//用户备注
	char szUserNote[LEN_USER_NOTE];
	//真实名字
	char szCompellation[LEN_COMPELLATION];
	//固定号码
	char szSeatPhone[LEN_SEAT_PHONE];
	//手机号码
	char szMobilePhone[LEN_MOBILE_PHONE];
	//Q Q 号码
	char szQQ[LEN_QQ];
	//电子邮件
	char szEMail[LEN_EMAIL];
	//详细地址
	char szDwellingPlace[LEN_DWELLING_PLACE];
};


//////////////////////////////////////////////////////////////////////////
// 用户资料修改提示
//////////////////////////////////////////////////////////////////////////
class IGPIndividualMissionSink
{
public:
	virtual ~IGPIndividualMissionSink(){}
	virtual void onGPIndividualInfo(int type){}
	virtual void onGPIndividualSuccess(int type, const char* szDescription){}
	virtual void onGPIndividualFailure(int type, const char* szDescription){}
};

//////////////////////////////////////////////////////////////////////////
// 用户资料修改任务
//////////////////////////////////////////////////////////////////////////
class CGPIndividualMission
	: public CSocketMission
{
public:
	CGPIndividualMission(const std::string& url, int port);
	// 设置回调接口
	void setMissionSink(IGPIndividualMissionSink* pIGPIndividualMissionSink);

	// 查询个人资料
	void query();
	// 修改个人资料
	void modify(const tagModifyIndividual& individual);

	//////////////////////////////////////////////////////////////////////////
	// ISocketEngineSink
public:
	virtual void onEventTCPSocketLink();
	virtual void onEventTCPSocketShut();
	virtual void onEventTCPSocketError(int errorCode);
	virtual bool onEventTCPSocketRead(int main, int sub, void* data, int dataSize);

	//////////////////////////////////////////////////////////////////////////
	// 子消息处理
private:
	// 个人信息
	bool onSubUserIndividual(void* data, int size);
	// 操作成功
	bool onSubOperateSuccess(void* data, int size);
	// 操作失败
	bool onSubOperateFailure(void* data, int size);
	
private:
	// 任务类型
	uint8 mMissionType;
	// 回调
	IGPIndividualMissionSink* mIGPIndividualMissionSink;

	//////////////////////////////////////////////////////////////////////////
	// 修改个人资料
	//////////////////////////////////////////////////////////////////////////
	tagModifyIndividual mModifyIndividual;
}; // CGPIndividualMission

#endif // _CGPIndividualMission_H_