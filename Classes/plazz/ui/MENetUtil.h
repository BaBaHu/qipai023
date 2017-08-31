#ifndef __ME_NET_UTIL_H__
#define __ME_NET_UTIL_H__

#include <vector>
using namespace std;

class MENetUtil
{
public:
	static bool init(int iKindID, int iPlayers, int iClientVersion, const char* sGameName);

	static const char* getNickName();
	static const char* getPassword();
	static const char* getBankPassword();
	static const char* getEncryptPassword(const char* pwd);
	static int getSex();
	static int getFaceID();
	static int getGameID();
	static int getUserID();
	static int getUserDailiOrder();
	static int getUserType(); //0是普通 1是QQ 2是微信
	static const char* getUserIconUrl();

	static int getUserGold();
	static int getBankGold();
	static int getRoomGold();

	static int setUserGoldOrRoomCard(int nType, long long nValue);

	static int getChairID();
	static int getTableGold(int iKindID, int iServerID);

	static bool checkNetWork();
	static bool exitGameRoom();
	static bool isGamePlaying();
	static int GetGameCurState();
	static void autoJoin();
	static bool isCustomServer();
	static int getCustomRoomID();
	static void dismisCustomServer(bool bRoomCreater);
	static void dismisCustomServerStartVote();
	static void dismisCustomServerVote( int nResult);
	//脚本接口
public:
	static int getUserTypeByChair(int nChair); //0是普通 1是QQ 2是微信
	static const char* getUserIconUrlByChair(int nChair);
	static const char* getUserNameByID(int nUserID);
	static void startTalk();
	static void endTalk(bool bSend);
	static void playTalk(int nChair, const char* url);
	static void playChat(int nChair, int nIdx, int nSex);
	static void setGameEnterBackground(bool bEnterBackground);
	static void logoutGame();
	static void setGameOffline();
	//发送进入场景消息
	static void enterGame();
	//发送离开场景消息
	static void leaveGame();
	//发送准备消息
	static void ready();
	//设置时钟
	static void setGameClock(int wChairID, int nTimerID, int nTimer);
	//清除时钟
	static void clearGameClock(int wChairID);
	//是否可启动时钟
	static void setEnableGameClock(bool bEnable);
	//设置托管
	static void setTrustee(bool Trustee);
	//出牌消息
	static void chuPai(int idxPai);
	//出牌操作消息
	static void operatePai(int nOperateCode, int idxPai);
	//设置抵注消息
	static void setDizhu(int nDizhu);
	//获取桌子玩家最小的金币数量
	static int getTableMinGold();
	//认输消息
	static void admitDefeat();
	//选牌定缺消息
	static void selectPai(int nType);
	//换三张消息
	static void changePai(int nCard1, int nCard2, int nCard3);

	//获取庄家用户
	static int getCurBanker();
	//用户下注消息
	static void placeBet(int cbBetArea, int lBetScore);
	//申请庄家消息
	static void applyBanker();
	//取消申请消息
	static void cancelBanker();
	//管理员命令消息
	static void adminCmd(int cbReqType);
	//最大下注
	static unsigned int GetMaxPlayerScore(int cbBetArea);
	//获取总下注
	static unsigned int GetAreaTotalScore(int cbBetArea);
	//获取自己总下注
	static unsigned int GetAreaPlayerScore(int cbBetArea);
	//获取玩家自由金币
	static unsigned int GetPlayerFreeScore();
	//获取牌点数
	static int GetCardPip(int nCardID);
	//
	static void getBet();
};

#endif // !__ME_NET_UTIL_H__