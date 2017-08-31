#ifndef CMD_BACCARAT_HEAD_FILE
#define CMD_BACCARAT_HEAD_FILE

#pragma pack(1)
//////////////////////////////////////////////////////////////////////////
//�����궨��

#define KIND_ID						122									//��Ϸ I D
#define GAME_PLAYER					MAX_CHAIR							//��Ϸ����
#define GAME_NAME					TEXT("�ټ���")						//��Ϸ����

//�������
//#ifdef DEBUG
	#define VERSION_SERVER				PROCESS_VERSION(6,0,3)				//����汾
	#define VERSION_CLIENT				PROCESS_VERSION(6,0,3)				//����汾
//#else
//	#define VERSION_SERVER				PROCESS_VERSION(12,0,3)				//����汾
//	#define VERSION_CLIENT				PROCESS_VERSION(12,0,3)				//����汾
//#endif

//״̬����
#define GAME_SCENE_FREE				GAME_STATUS_FREE					//�ȴ���ʼ
#define GAME_SCENE_PLAY				GAME_STATUS_PLAY					//��Ϸ����
#define GAME_SCENE_BET				GAME_STATUS_PLAY					//��ע״̬
#define	GAME_SCENE_END				GAME_STATUS_PLAY+1					//����״̬

//�������
#define ID_XIAN_JIA					0									//�м�����
#define ID_PING_JIA					1									//ƽ������
#define ID_ZHUANG_JIA				2									//ׯ������
#define ID_XIAN_TIAN_WANG			3									//������
#define ID_ZHUANG_TIAN_WANG			4									//ׯ����
#define ID_TONG_DIAN_PING			5									//ͬ��ƽ
#define ID_PLAYER_TWO_PAIR			6									//�ж���
#define ID_BANKER_TWO_PAIR			7									//ׯ����

//��������
#define AREA_XIAN					0									//�м�����
#define AREA_PING					1									//ƽ������
#define AREA_ZHUANG					2									//ׯ������
#define AREA_XIAN_TIAN				3									//������
#define AREA_ZHUANG_TIAN			4									//ׯ����
#define AREA_TONG_DUI				5									//ͬ��ƽ
#define AREA_XIAN_DUI				6									//�ж���
#define AREA_ZHUANG_DUI				7									//ׯ����
#define AREA_MAX					8									//�������

//������multiple
#define MULTIPLE_XIAN				2									//�мұ���
#define MULTIPLE_PING				9									//ƽ�ұ���
#define MULTIPLE_ZHUANG				2									//ׯ�ұ���
#define MULTIPLE_XIAN_TIAN			3									//����������
#define MULTIPLE_ZHUANG_TIAN		3									//ׯ��������
#define MULTIPLE_TONG_DIAN			33									//ͬ��ƽ����
#define MULTIPLE_XIAN_PING			12									//�ж��ӱ���
#define MULTIPLE_ZHUANG_PING		12									//ׯ���ӱ���

//��������
#define INDEX_PLAYER				0									//�м�����
#define INDEX_BANKER				1									//ׯ������

//���ʶ���
#define RATE_TWO_PAIR				12									//��������
#define SERVER_LEN					32									//���䳤��

//�������
enum enOperateResult
{
	enOperateResult_NULL,
	enOperateResult_Win,
	enOperateResult_Lost
};

//��¼��Ϣ
struct tagServerGameRecord
{
	byte							cbKingWinner;						//����Ӯ��
	bool							bPlayerTwoPair;						//�мҶ��ӱ�ʶ
	bool							bBankerTwoPair;						//ׯ�Ҷ��ӱ�ʶ
	byte							cbPlayerCount;						//�мҵ���
	byte							cbBankerCount;						//ׯ�ҵ���
};

//////////////////////////////////////////////////////////////////////////
//����������ṹ
#define SUB_S_MAIN_MSG				200									//�������Ϸ����������

#define SUB_S_GAME_FREE				99									//��Ϸ����
#define SUB_S_GAME_START			100									//��Ϸ��ʼ
#define SUB_S_PLACE_JETTON			101									//�û���ע
#define SUB_S_GAME_END				102									//��Ϸ����
#define SUB_S_APPLY_BANKER			103									//����ׯ��
#define SUB_S_CHANGE_BANKER			104									//�л�ׯ��
#define SUB_S_CHANGE_USER_SCORE		105									//���»���
#define SUB_S_SEND_RECORD			106									//��Ϸ��¼
#define SUB_S_PLACE_JETTON_FAIL		107									//��עʧ��
#define SUB_S_CANCEL_BANKER			108									//ȡ������
#define SUB_S_AMDIN_COMMAND			109									//����Ա����
#define SUB_S_TIP_INFO				110									//��ʾ��Ϣ
#define SUB_S_CANCEL_JETTON			111									//ȡ����ע
#define SUB_S_RESORT_BANKER			112									//������ׯ��

//��Ϸ״̬
struct CMD_S_StatusFree
{
	//ȫ����Ϣ
	byte							cbTimeLeave;						//ʣ��ʱ��

	//�����Ϣ
	longlong						lPlayFreeSocre;						//������ɽ��

	//ׯ����Ϣ
	word							wBankerUser;						//��ǰׯ��
	longlong						lBankerScore;						//ׯ�ҷ���
	longlong						lBankerWinScore;					//ׯ��Ӯ��
	word							wBankerTime;						//ׯ�Ҿ���

	//�Ƿ�ϵͳ��ׯ
	bool							bEnableSysBanker;					//ϵͳ��ׯ

	//������Ϣ
	longlong						lApplyBankerCondition;				//��������
	longlong						lAreaLimitScore;					//��������

	//������Ϣ
	char							szGameRoomName[2*SERVER_LEN];			//��������

	word							wFaceID;
};

//��Ϸ״̬
struct CMD_S_StatusPlay
{
	//ȫ����Ϣ
	byte							cbTimeLeave;						//ʣ��ʱ��
	byte							cbGameStatus;						//��Ϸ״̬

	//��ע��
	longlong						lAllBet[AREA_MAX];					//����ע
	longlong						lPlayBet[AREA_MAX];					//�����ע

	//��һ���
	longlong						lPlayBetScore;						//��������ע	
	longlong						lPlayFreeSocre;						//������ɽ��

	//�����Ӯ
	longlong						lPlayScore[AREA_MAX];				//�����Ӯ
	double							lPlayAllScore;						//��ҳɼ�

	//ׯ����Ϣ
	word							wBankerUser;						//��ǰׯ��
	longlong						lBankerScore;						//ׯ�ҷ���
	longlong						lBankerWinScore;					//ׯ��Ӯ��
	word							wBankerTime;						//ׯ�Ҿ���

	//�Ƿ�ϵͳ��ׯ
	bool							bEnableSysBanker;					//ϵͳ��ׯ

	//������Ϣ
	longlong						lApplyBankerCondition;				//��������
	longlong						lAreaLimitScore;					//��������

	//�˿���Ϣ
 	byte							cbCardCount[2];						//�˿���Ŀ
	byte							cbTableCardArray[2][3];				//�����˿�

	//������Ϣ
	char							szGameRoomName[2*SERVER_LEN];			//��������

	word							wFaceID;
};

//��Ϸ����
struct CMD_S_GameFree
{
	byte							cbTimeLeave;						//ʣ��ʱ��
};

//��Ϸ��ʼ
struct CMD_S_GameStart
{
	byte							cbTimeLeave;						//ʣ��ʱ��

	word							wBankerUser;						//ׯ��λ��
	longlong						lBankerScore;						//ׯ�ҽ��

	longlong						lPlayBetScore;						//��������ע	
	longlong						lPlayFreeSocre;						//������ɽ��

	int								nChipRobotCount;					//�������� (��ע������)
};

//�û���ע
struct CMD_S_PlaceBet
{
	word							wChairID;							//�û�λ��
	byte							cbBetArea;							//��������
	longlong						lBetScore;							//��ע��Ŀ
	byte							cbAndroidUser;						//������ʶ
};

//ȡ����ע
struct CMD_S_CancelBet
{
	word							wChairID;							//�û�λ��
	longlong						lPlayBet[AREA_MAX];					//�����ע
};

struct CMD_S_ReSortBanker
{
	word		wCurBanker;					//��ǰׯ��
	word		wUserCount;					//�������
	word		wUserChairID[100];			//�������ID
};

//����ظ�
struct CMD_S_CommandResult
{
	byte cbAckType;					//�ظ�����
#define ACK_SET_WIN_AREA  1
#define ACK_PRINT_SYN     2
#define ACK_RESET_CONTROL 3
	byte cbResult;
#define CR_ACCEPT  2			//����
#define CR_REFUSAL 3			//�ܾ�
	byte cbExtendData[20];			//��������
};

//ʧ�ܽṹ
struct CMD_S_PlaceBetFail
{
	word							wPlaceUser;							//��ע���
	byte							lBetArea;							//��ע����
	longlong						lPlaceScore;						//��ǰ��ע
};

//����ׯ��
struct CMD_S_ApplyBanker
{
	word							wApplyUser;							//�������
};

//ȡ������
struct CMD_S_CancelBanker
{
	word							wCancelUser;						//ȡ�����
};

//�л�ׯ��
struct CMD_S_ChangeBanker
{
	word							wBankerUser;						//��ׯ���
	longlong						lBankerScore;						//ׯ�ҷ���
	word							wFaceID;
};

//��Ϸ����
struct CMD_S_GameEnd
{
	//�¾���Ϣ
	byte							cbTimeLeave;						//ʣ��ʱ��

	//�˿���Ϣ
	byte							cbCardCount[2];						//�˿���Ŀ
	byte							cbTableCardArray[2][3];				//�����˿�
 
	//ׯ����Ϣ
	longlong						lBankerScore;						//ׯ�ҳɼ�
	longlong						lBankerTotallScore;					//ׯ�ҳɼ�
	int								nBankerTime;						//��ׯ����

	//��ҳɼ�
	longlong						lPlayScore[AREA_MAX];				//��ҳɼ�
	double							lPlayAllScore;						//��ҳɼ�

	//ȫ����Ϣ
	longlong						lRevenue;							//��Ϸ˰��
};

//��ʾ��Ϣ
struct CMD_S_TipInfo
{
	byte							cbTimeLeave;						//ʣ��ʱ��
	char							szTipInfo[2*256];					//��ʾ��Ϣ
};

//////////////////////////////////////////////////////////////////////////
//�ͻ�������ṹ

#define SUB_C_PLACE_JETTON			1									//�û���ע
#define SUB_C_APPLY_BANKER			2									//����ׯ��
#define SUB_C_CANCEL_BANKER			3									//ȡ������
#define SUB_C_AMDIN_COMMAND			4									//����Ա����
#define SUB_C_CANCEL_JETTON			5


struct CMD_C_AdminReq
{
	byte cbReqType;
		 #define RQ_SET_WIN_AREA	1
		 #define RQ_RESET_CONTROL	2
		 #define RQ_PRINT_SYN		3
	byte cbExtendData[20];			//��������
};


//struct CMD_C_AdminReq
//{
//	BYTE cbReqType;
//		 #define RQ_SETWINAREA   1 
//	BYTE cbExtendData[120];
//};


//�û���ע
struct CMD_C_PlaceBet
{
	byte							cbBetArea;						//��������
	longlong						lBetScore;						//��ע��Ŀ
};

//////////////////////////////////////////////////////////////////////////
#pragma pack()
#endif
