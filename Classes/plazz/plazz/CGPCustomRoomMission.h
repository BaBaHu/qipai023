#ifndef _CGPCustomRoomMission_H_
#define _CGPCustomRoomMission_H_
#include "../Plazz.h"

//////////////////////////////////////////////////////////////////////////
// 创建自定义房间提示
//////////////////////////////////////////////////////////////////////////
class IGPCustomRoomMissionSink
{
public:
	virtual ~IGPCustomRoomMissionSink(){}
	virtual void onGPCreateCustomRoomSuccess(dword dwRoomID, const tagGameServer& server){}
	virtual void onGPCreateCustomRoomFailure(int errorCode){}
	virtual void onGPEnterCustomRoomSuccess(dword dwRoomID, const tagGameServer& server){}
	virtual void onGPEnterCustomRoomFailure(int errorCode){}
};

//创建房间
struct tagGPCreateCustomRoom
{
	byte		cbRound;						//玩多少局
	word		wKindID;						//游戏类型id
	longlong	llBaseScore;					//底分  这个也可以钻石。。
												//其实，还有什么自摸加低呀，等等玩法，也是房间的一个属性。
};

//进入房间
struct tagGPEnterCustomRoom
{
	dword		dwRoomVerifyID;					//房间号码
};

//////////////////////////////////////////////////////////////////////////
// 创建自定义房间
//////////////////////////////////////////////////////////////////////////
class CGPCustomRoomMission
	: public CSocketMission
{
public:
	CGPCustomRoomMission(const std::string& url, int port);
	// 设置回调接口
	void setMissionSink(IGPCustomRoomMissionSink* pIGPCustomRoomMissionSink);
	// 创建房间
	void createCustomRoom(const tagGPCreateCustomRoom& cRoom);
	// 进入房间
	void enterCustomRoom(const tagGPEnterCustomRoom& eRoom);
	// 请求自己创建的房间
	void reqSelfCustomRoom();
private:
	//////////////////////////////////////////////////////////////////////////
	// 发送创建房间
	bool sendCreateCustomRoomPacket(const tagGPCreateCustomRoom& cRoom);
	// 发送进入房间
	bool sendEnterCustomRoomPacket(const tagGPEnterCustomRoom& eRoom);
	// 发送请求自己创建的房间
	bool sendSelfCustomRoomPacket();
	//////////////////////////////////////////////////////////////////////////
	// ISocketEngineSink
public:
	virtual void onEventTCPSocketLink();
	virtual void onEventTCPSocketShut();
	virtual void onEventTCPSocketError(int errorCode);
	virtual bool onEventTCPSocketRead(int main, int sub, void* data, int dataSize);
private:
	//////////////////////////////////////////////////////////////////////////
	//创建自定义房间
	bool onSocketCreateCustomRoom(void* data, int size);
	//进入自定义房间
	bool onSocketEnterCustomRoom(void* data, int size);
	//请求自己创建的房间
	bool onSocketSelfCreateCustomRoom(void* data, int size);
private:
	// 回调
	IGPCustomRoomMissionSink* mIGPCustomRoomMissionSink;

	// 任务类型
	uint8 mMissionType;
	// 创建房间数据
	tagGPCreateCustomRoom	mCreateCustomRoom;
	// 进入房间数据
	tagGPEnterCustomRoom	mEnterCustomRoom;
}; // CGPCustomRoomMission

#endif // _CGPCustomRoomMission_H_