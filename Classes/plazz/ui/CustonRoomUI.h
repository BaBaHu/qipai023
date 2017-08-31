#ifndef _CustonRoomUI_H_
#define _CustonRoomUI_H_

#include "cocos2d.h"
#include "../plazz/GPMission.h"
USING_NS_CC;

class CustonRoomUI : public Ref, public IGPCustomRoomMissionSink
{
public:
	CustonRoomUI();
	~CustonRoomUI();
	static CustonRoomUI* create(std::string strIp, int iPort);

	void createRoom(int iKindID, int cbRound, int cbWF);
	void enterRoom(int iRoomID);
	void enterCustomRoom(int iRoomID);
	bool checkAutoEnterCustomGame();
	//////////////////////////////////////////////////////////////////////////
	// IGPCustomRoomMissionSink
public:
	virtual void onGPCreateCustomRoomSuccess(dword dwRoomID, const tagGameServer& server);
	virtual void onGPCreateCustomRoomFailure(int errorCode);
	virtual void onGPEnterCustomRoomSuccess(dword dwRoomID, const tagGameServer& server);
	virtual void onGPEnterCustomRoomFailure(int errorCode);
private:
	bool init(std::string strIp, int iPort);

	//////////////////////////////////////////////////////////////////////////
	// mission
	CGPCustomRoomMission	mCustomRoomMission;
};
#endif // _CustonRoomUI_H_