#ifndef CMD_FOURMJ_HEAD_FILE
#define CMD_FOURMJ_HEAD_FILE

//#pragma pack(1)
//////////////////////////////////////////////////////////////////////////
//�����궨��

#define KIND_ID						301							//��Ϸ I D

//�������
#define GAME_PLAYER					4									//��Ϸ����

#define VERSION_SERVER				PROCESS_VERSION(6,0,3)				//����汾
#define VERSION_CLIENT				PROCESS_VERSION(6,0,3)				//����汾

#define GAME_NAME					TEXT("Ѫս�齫")					//��Ϸ����
#define GAME_GENRE					(GAME_GENRE_SCORE|GAME_GENRE_MATCH|GAME_GENRE_GOLD)	//��Ϸ����

//��Ϸ״̬
#define GS_MJ_FREE					GAME_STATUS_FREE							//����״̬
#define GS_MJ_PLAY					(GAME_STATUS_PLAY+1)						//��Ϸ״̬

//��������
#define MAX_WEAVE					4									//������
#define MAX_INDEX					34									//�������
#define MAX_COUNT					14									//�����Ŀ
#define MAX_REPERTORY				108									//�����
#define MAX_GANGCARD				11									//������

//�˿˶���
#define HEAP_FULL_COUNT				26									//����ȫ��

#define MAX_RIGHT_COUNT				1									//���ȨλDWORD����			

//////////////////////////////////////////////////////////////////////////

//�������
struct CMD_WeaveItem
{
	byte							cbWeaveKind;						//�������
	byte							cbCenterCard;						//�����˿�
	byte							cbPublicCard;						//������־
	word							wProvideUser;						//��Ӧ�û�
	byte							cbCombinationCard;					//����˿�
};
//////////////////////////////////////////////////////////////////////////
//����������ṹ
#define SUB_S_MAIN_MSG				200									//�������Ϸ����������

#define SUB_S_GAME_START			100									//��Ϸ��ʼ
#define SUB_S_OUT_CARD				101									//��������
#define SUB_S_SEND_CARD				102									//�����˿�
#define SUB_S_OPERATE_NOTIFY		104									//������ʾ
#define SUB_S_OPERATE_RESULT		105									//��������
#define SUB_S_GAME_END				106									//��Ϸ����
#define SUB_S_TRUSTEE				107									//�û��й�
#define SUB_S_CHI_HU				108									//
#define SUB_S_GANG_SCORE			110									//
#define SUB_S_SELECT   			    111									//��ȱ��ɫ
#define SUB_S_CHANGE_CARD			112									//������

//��Ϸ״̬
struct CMD_S_StatusFree
{
	longlong						lCellScore;							//�������
	word							wBankerUser;						//ׯ���û�
	bool							bTrustee[GAME_PLAYER];				//�Ƿ��й�
	bool                            bAvertCheatMode;                    //�Ƿ������  
};
//��Ϸ״̬
struct CMD_S_StatusPlay
{
	//��Ϸ����
	longlong						lCellScore;									//��Ԫ����
	word							wBankerUser;								//ׯ���û�
	word							wCurrentUser;								//��ǰ�û�

	//״̬����
	byte							cbActionCard;								//�����˿�
	byte							cbActionMask;								//��������
	byte							cbLeftCardCount;							//ʣ����Ŀ
	bool							bTrustee[GAME_PLAYER];						//�Ƿ��й�
	word							wWinOrder[GAME_PLAYER];						//����˳��INVALID_CHAIR ��ʾû�к��ƣ������ʾ˳�򣬴�1��ʼ

	//������Ϣ
	word							wOutCardUser;								//�����û�
	byte							cbOutCardData;								//�����˿�
	byte							cbDiscardCount[GAME_PLAYER];				//������Ŀ
	byte							cbDiscardCard[GAME_PLAYER][55];				//������¼

	//�˿�����
	byte							cbCardCount;								//�˿���Ŀ
	byte							cbCardData[MAX_COUNT];						//�˿��б�
	byte							cbSendCardData;								//�����˿�

	//����˿�
	byte							cbWeaveCount[GAME_PLAYER];					//�����Ŀ
	CMD_WeaveItem					WeaveItemArray[GAME_PLAYER][MAX_WEAVE];		//����˿�

	//������Ϣ
	word							wHeapHand;									//����ͷ��
	word							wHeapTail;									//����β��
	byte							cbHeapCardInfo[GAME_PLAYER][2];				//������Ϣ
	byte							cbSelectCard[GAME_PLAYER];					//��ȱ��ɫ
	word							wProvider[GAME_PLAYER];						//�����ṩ��ң������ж�����������ץ��
	byte							cbProvideCard[GAME_PLAYER];					//����������
	longlong						llChiHuScore[GAME_PLAYER];					//���Ƶ÷�

	bool							bSelectColor;								//��ȱ���
	//BYTE							cbSelectColor;								//��ȱ��ɫ
	bool							bChanged;									//���ƽ��
	//CMD_S_ChangeCard				ChangeCard;									//��������
};

//��Ϸ��ʼ
struct CMD_S_GameStart
{
	byte                            wGameMode;                                  //��Ϸģʽ
	uint32							lSiceCount;									//���ӵ���
	word							wBankerUser;								//ׯ���û�
	word							wCurrentUser;								//��ǰ�û�
	byte							cbUserAction;								//�û�����
	byte							cbCardData[MAX_COUNT*GAME_PLAYER];			//�˿��б�
	word							wHeapHand;									//������ͷ
	word							wHeapTail;									//������β
	byte							cbHeapCardInfo[GAME_PLAYER][2];				//������Ϣ
	byte							cbLeftCardCount;							
	bool							bGameMatch;									//�Ƿ����
	uint32							lCellScore;									//��Ϸ�׷�
};

//��ȱ��ɫ
struct CMD_S_SelectCard
{	
    word							wCurrentUser;								//��ǰ�û�
	byte                            wUserAction;                                //�û�����
	byte                            wSelectCard[GAME_PLAYER];                   //ѡ��ɫ
};

//��������
struct CMD_S_OutCard
{
	word							wOutCardUser;						//�����û�
	byte							cbOutCardData;						//�����˿�
};

//�����˿�
struct CMD_S_SendCard
{
	byte							cbCardData;							//�˿�����
	byte							cbGangCardData[MAX_GANGCARD];		//��������
	byte							cbActionMask;						//��������
	word							wCurrentUser;						//��ǰ�û�
	bool							bTail;								//ĩβ����
};

//������ʾ
struct CMD_S_OperateNotify
{
	word							wResumeUser;						//��ԭ�û�
	byte							cbActionMask;						//��������
	byte							cbActionCard;						//�����˿�
};

//��������
struct CMD_S_OperateResult
{
	word							wOperateUser;						//�����û�
	word							wProvideUser;						//��Ӧ�û�
	byte							cbOperateCode;						//��������
	byte							cbOperateCard;						//�����˿�
	byte							cbCombinationCard;					//����˿�
};

//��Ϸ����
struct CMD_S_GameEnd
{
	byte							cbCardCount[GAME_PLAYER];			//
	byte							cbCardData[GAME_PLAYER][MAX_COUNT];	//
	//������Ϣ
	word							wProvideUser[GAME_PLAYER];			//��Ӧ�û�
	dword							dwChiHuRight[GAME_PLAYER];			//��������

	//������Ϣ
	longlong						lGameScore[GAME_PLAYER];			//��Ϸ����
	uint32							lGameTax[GAME_PLAYER];				//

	word							wWinOrder[GAME_PLAYER];				//��������

	longlong						lGangScore[GAME_PLAYER];			//��ϸ�÷�
	byte							cbGenCount[GAME_PLAYER];			//
	word							wLostFanShu[GAME_PLAYER][GAME_PLAYER];
	word							wWinFanShu[GAME_PLAYER];
	word							wLeftUser;							//
	longlong						lChuShi;
	longlong						lDangQian;
};

//�û��й�
struct CMD_S_Trustee
{
	bool							bTrustee;							//�Ƿ��й�
	word							wChairID;							//�й��û�
};

//
struct CMD_S_ChiHu
{
	word							wChiHuUser;							//
	word							wProviderUser;						//
	byte							cbChiHuCard;						//
	byte							cbCardCount;						//
	longlong						lGameScore;							//
	byte							cbWinOrder;							//
};

//
struct CMD_S_GangScore
{
	word							wChairId;							//
	byte							cbXiaYu;							//
	longlong						lGangScore[GAME_PLAYER];			//
};

struct CMD_S_ChangeCard
{
	word							wChangeDirection;					//�һ�����
	byte							cbCardData[MAX_COUNT*GAME_PLAYER];	//�û�����
	byte							cbChangeCard[GAME_PLAYER][3];		//�һ�����
};

//////////////////////////////////////////////////////////////////////////
//�ͻ�������ṹ

#define SUB_C_OUT_CARD				1									//��������
#define SUB_C_OPERATE_CARD			3									//�����˿�
#define SUB_C_TRUSTEE				4									//�û��й�
#define SUB_C_SELECT   			    5									//��ȱ��ɫ
#define SUB_C_TYPE   				6									//������Ϣ
#define SUB_C_CONTROL   			7									//������Ϣ
#define SUB_C_LEAVE		   			8									//�˳���Ϣ	
#define SUB_C_CHANGE				9									//������

//ѡ������
struct CMD_C_SelectCard
{
	byte							cbCardData;							//��ȱ����
};

//��������
struct CMD_C_OutCard
{
	byte							cbCardData;							//�˿�����
};

//��������
struct CMD_C_OperateCard
{
	byte							cbOperateCode;						//��������
	byte							cbOperateCard;						//�����˿�
};

//�û��й�
struct CMD_C_Trustee
{
	bool							bTrustee;							//�Ƿ��й�	
};

struct CMD_C_Control
{
	uint32							ChuShi;							//��ʼ���
	uint32							DangQian;						//��ǰ���
	bool							bAction;						//�Ƿ�ִ��
};

struct CMD_C_Type
{
	dword							UserID[3];						
	byte							Type1[3];
	bool							bAction;						//�Ƿ�ִ��
};

//���Ʋ���
struct CMD_C_Change
{
	byte							cbCardData[3];						//��������
};

//////////////////////////////////////////////////////////////////////////

//�߼�����

#define	MASK_COLOR					0xF0								//��ɫ����
#define	MASK_VALUE					0x0F								//��ֵ����

//////////////////////////////////////////////////////////////////////////
//��������

//������־
#define WIK_NULL					0x00								//û������
#define WIK_LEFT					0x01								//�������
#define WIK_CENTER					0x02								//�г�����
#define WIK_RIGHT					0x04								//�ҳ�����
#define WIK_PENG					0x08								//��������
#define WIK_GANG					0x10								//��������
#define WIK_LISTEN					0x20								//��������
#define WIK_CHI_HU					0x40								//�Ժ�����
#define WIK_ZI_MO					0x80								//����
#define WIK_QIANG_GANG				0x90								//����ɾ��

//////////////////////////////////////////////////////////////////////////
//���ƶ���

//����
#define CHK_NULL					0x00										//�Ǻ�����
#define CHK_CHI_HU					0x01										//������

#define CHR_QIANG_GANG				0x00000001									//����
#define CHR_GANG_SHANG_PAO			0x00000002									//������
#define CHR_GANG_KAI				0x00000004									//���ϻ�
#define CHR_TIAN_HU					0x00000008									//���
#define CHR_DI_HU					0x00000010									//�غ�
#define CHR_DA_DUI_ZI				0x00000020									//�����
#define CHR_QING_YI_SE				0x00000040									//��һɫ
#define CHR_QI_XIAO_DUI				0x00000080									//���߶�
#define CHR_DAI_YAO				    0x00000100									//����
#define CHR_JIANG_DUI				0x00000200									//����
#define CHR_SHU_FAN					0x00000400									//�ط�
#define CHR_QING_DUI				0x00000800									//���
#define CHR_LONG_QI_DUI				0x00001000									//���߶�
#define CHR_QING_QI_DUI				0x00002000									//���߶�
#define CHR_QING_YAO_JIU			0x00004000									//���۾�
#define CHR_QING_LONG_QI_DUI		0x00008000									//�����߶�
#define CHR_JING_GOU_GOU			0x00010000									//�𹳹�
#define CHR_MENG_QING				0x00020000									//����
#define CHR_ZHONG_JIANG				0x00040000									//�н�
#define CHR_HAI_DI					0x00080000									//��������
#define CHR_DIAN_GANG				0x00100000									//��ܻ�

//#pragma pack()
#endif
