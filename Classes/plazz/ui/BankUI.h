#ifndef _BANKUI_H_
#define _BANKUI_H_

#include "cocos2d.h"
#include "../plazz/GPMission.h"
USING_NS_CC;

//保险柜
class BankUI: public Ref, IGPInsureMissionSink 
{
public:
	BankUI();
	~BankUI();
	static BankUI* create(std::string strIp, int iPort);
	// 查询
	void query();
	//存入
	void save(int value);
	//取出
	void take(int64 score, const char* szInsurePass);
	// 转账
	void transfer(int nType, int64 score, const char* szInsurePass, const char* szNickName, uint8 cbByNickName);
	// 修改密码
	void modifyPassword(int nType, const char* szOldPass, const char* szNewPass);
	//回调函数
public:
	void onInsureInfo();
	void onInsureSuccess(int type, const char* szDescription);
	void onInsureFailure(int type, const char* szDescription);

private:
	bool init(std::string strIp, int iPort);
private:
	// mission
	CGPInsureMission	mInsureMission;
};

#endif // _BANKUI_H_