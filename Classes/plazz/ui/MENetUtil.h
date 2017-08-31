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
	static int getUserType(); //0����ͨ 1��QQ 2��΢��
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
	//�ű��ӿ�
public:
	static int getUserTypeByChair(int nChair); //0����ͨ 1��QQ 2��΢��
	static const char* getUserIconUrlByChair(int nChair);
	static const char* getUserNameByID(int nUserID);
	static void startTalk();
	static void endTalk(bool bSend);
	static void playTalk(int nChair, const char* url);
	static void playChat(int nChair, int nIdx, int nSex);
	static void setGameEnterBackground(bool bEnterBackground);
	static void logoutGame();
	static void setGameOffline();
	//���ͽ��볡����Ϣ
	static void enterGame();
	//�����뿪������Ϣ
	static void leaveGame();
	//����׼����Ϣ
	static void ready();
	//����ʱ��
	static void setGameClock(int wChairID, int nTimerID, int nTimer);
	//���ʱ��
	static void clearGameClock(int wChairID);
	//�Ƿ������ʱ��
	static void setEnableGameClock(bool bEnable);
	//�����й�
	static void setTrustee(bool Trustee);
	//������Ϣ
	static void chuPai(int idxPai);
	//���Ʋ�����Ϣ
	static void operatePai(int nOperateCode, int idxPai);
	//���õ�ע��Ϣ
	static void setDizhu(int nDizhu);
	//��ȡ���������С�Ľ������
	static int getTableMinGold();
	//������Ϣ
	static void admitDefeat();
	//ѡ�ƶ�ȱ��Ϣ
	static void selectPai(int nType);
	//��������Ϣ
	static void changePai(int nCard1, int nCard2, int nCard3);

	//��ȡׯ���û�
	static int getCurBanker();
	//�û���ע��Ϣ
	static void placeBet(int cbBetArea, int lBetScore);
	//����ׯ����Ϣ
	static void applyBanker();
	//ȡ��������Ϣ
	static void cancelBanker();
	//����Ա������Ϣ
	static void adminCmd(int cbReqType);
	//�����ע
	static unsigned int GetMaxPlayerScore(int cbBetArea);
	//��ȡ����ע
	static unsigned int GetAreaTotalScore(int cbBetArea);
	//��ȡ�Լ�����ע
	static unsigned int GetAreaPlayerScore(int cbBetArea);
	//��ȡ������ɽ��
	static unsigned int GetPlayerFreeScore();
	//��ȡ�Ƶ���
	static int GetCardPip(int nCardID);
	//
	static void getBet();
};

#endif // !__ME_NET_UTIL_H__