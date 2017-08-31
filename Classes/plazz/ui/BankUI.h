#ifndef _BANKUI_H_
#define _BANKUI_H_

#include "cocos2d.h"
#include "../plazz/GPMission.h"
USING_NS_CC;

//���չ�
class BankUI: public Ref, IGPInsureMissionSink 
{
public:
	BankUI();
	~BankUI();
	static BankUI* create(std::string strIp, int iPort);
	// ��ѯ
	void query();
	//����
	void save(int value);
	//ȡ��
	void take(int64 score, const char* szInsurePass);
	// ת��
	void transfer(int nType, int64 score, const char* szInsurePass, const char* szNickName, uint8 cbByNickName);
	// �޸�����
	void modifyPassword(int nType, const char* szOldPass, const char* szNewPass);
	//�ص�����
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