#ifndef _CGPInsureMission_H_
#define _CGPInsureMission_H_
#include "../Plazz.h"

#define INSURE_MISSION_SAVE					1
#define INSURE_MISSION_TAKE					2
#define INSURE_MISSION_TRANSFER				3
#define INSURE_MISSION_TRANSFER_ROOMCARD	4
#define INSURE_MISSION_QUERY				5
#define INSURE_MISSION_MODIFY_LOGON_PASS	6
#define INSURE_MISSION_MODIFY_INSURE_PASS	7

class IGPInsureMissionSink
{
public:
	virtual ~IGPInsureMissionSink(){}
	virtual void onInsureInfo(){}
	virtual void onInsureSuccess(int type, const char* szDescription){}
	virtual void onInsureFailure(int type, const char* szDescription){}
};


class CGPInsureMission
	: public CSocketMission
{
public:
	CGPInsureMission(const std::string& url, int port);
	// 设置回调接口
	void setMissionSink(IGPInsureMissionSink* pIGPInsureMissionSink);
	// 查询
	void query();
	// 存入
	void save(int64 score);
	// 取出
	void take(int64 score, const char* szInsurePass);
	// 转账
	void transfer(int nType, int64 score, const char* szInsurePass, const char* szNickName, uint8 cbByNickName);
	// 修改密码
	void modifyPassword(int nType, const char* szOldPass, const char* szNewPass);
	//////////////////////////////////////////////////////////////////////////
	// ISocketEngineSink
public:
	virtual void onEventTCPSocketLink();
	virtual void onEventTCPSocketShut();
	virtual void onEventTCPSocketError(int errorCode);
	virtual bool onEventTCPSocketRead(int main, int sub, void* data, int dataSize);
private:

	//转账查询
	bool onSubQueryInfoResult(void* data, int size);
	//银行资料
	bool onSubInsureInfo(void* data, int size);
	//银行成功
	bool onSubInsureSuccess(void* data, int size);
	//银行失败
	bool onSubInsureFailure(void* data, int size);
	// 操作成功
	bool onSubOperateSuccess(void* data, int size);
	// 操作失败
	bool onSubOperateFailure(void* data, int size);
	// 房卡转账成功
	bool onSubTransferRoomCardSuccess(void* data, int size);
private:
	// 任务类型
	uint8 mMissionType;

	// 回调接口
	IGPInsureMissionSink* mIGPInsureMissionSink;
	
	// 数量
	int64 mScore;

	// 银行密码
	char mInsurePass[LEN_PASSWORD];
	// ID,昵称标识
	uint8 mByNickName;
	// ID,昵称
	char mNickName[LEN_NICKNAME];
	// 旧密码
	char mOldPass[LEN_PASSWORD];
	// 新密码
	char mNewPass[LEN_PASSWORD];
}; // CGPInsureMission

#endif // _CGPInsureMission_H_