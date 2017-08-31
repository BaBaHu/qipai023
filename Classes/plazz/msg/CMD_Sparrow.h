#ifndef CMD_SPARROW_HEAD_FILE
#define CMD_SPARROW_HEAD_FILE

//#pragma pack(1)
//////////////////////////////////////////////////////////////////////////
//�����궨��

#define KIND_ID						351									//��Ϸ I D

#define VERSION_SERVER				PROCESS_VERSION(6,0,3)				//����汾
#define VERSION_CLIENT				PROCESS_VERSION(6,0,3)				//����汾


#define GAME_PLAYER					2									//��Ϸ����
#define GAME_NAME					TEXT("���˺��б�")					//��Ϸ����
#define GAME_GENRE					(GAME_GENRE_SCORE|GAME_GENRE_MATCH|GAME_GENRE_GOLD)	//��Ϸ����

//��Ϸ״̬
#define GS_MJ_FREE					GAME_STATUS_FREE								//����״̬
#define GS_MJ_PLAY					(GAME_STATUS_PLAY+1)						//��Ϸ״̬

//��������
#define MAX_WEAVE					4									//������
#define MAX_INDEX					20//34									//�������
#define MAX_COUNT					14									//�����Ŀ
#define MAX_REPERTORY				80//136									//�����
#define MAX_HUA_CARD				0									//���Ƹ���

//�˿˶���
#define HEAP_FULL_COUNT				40//34									//����ȫ��

//#define MAX_RIGHT_COUNT				1									//���ȨλDWORD����		
#define MAX_RIGHT_COUNT				3									//���ȨλDWORD����		


//////////////////////////////////////////////////////////////////////////

//�������
struct CMD_WeaveItem
{
	byte							cbWeaveKind;						//�������
	byte							cbCenterCard;						//�����˿�
	byte							cbPublicCard;						//������־
	word							wProvideUser;						//��Ӧ�û�
	byte							cbCardData[4];						//�������
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
#define SUB_S_REPLACE_CARD			108									//�û�����
#define SUB_S_CHANGE_TABLE_OWNER	110									//��������
#define SUB_S_EXITGAME				111									//�뿪��Ϸ
#define SUB_S_QGang_CARD			112									//����ɾ��

//��������
struct CMD_S_ChangeTableOwner
{
	word							wTableOwner;						//�������
};

//��Ϸ״̬
// struct CMD_S_StatusFree
// {
// 	longlong						lCellScore;							//�������
// 	word							wBankerUser;						//ׯ���û�
// 	bool							bTrustee[GAME_PLAYER];				//�Ƿ��й�
// 	word							wTableOwner;	                    //����λ��
// 	byte							bMatch;								//����
// };

struct CMD_S_StatusFree
{
	//��ʷ����
	longlong						lTurnScore[GAME_PLAYER];			//������Ϣ
	longlong						lCollectScore[GAME_PLAYER];			//������Ϣ

	longlong						lCellScore;							//�������
	word							wBankerUser;						//ׯ���û�
	bool							bTrustee[GAME_PLAYER];				//�Ƿ��й�
};


//��Ϸ״̬
struct CMD_S_StatusPlay
{
	//��Ϸ����
	longlong						lCellScore;									//��Ԫ����
	word							wBankerUser;								//ׯ���û�
	word							wCurrentUser;								//��ǰ�û�
	byte							bMatch;										//����

	//״̬����
	byte							cbActionCard;								//�����˿�
	byte							cbActionMask;								//��������
	byte							cbLeftCardCount;							//ʣ����Ŀ
	bool							bTrustee[GAME_PLAYER];						//�Ƿ��й�

	//������Ϣ
	word							wOutCardUser;								//�����û�
	byte							cbOutCardData;								//�����˿�
	byte							cbDiscardCount[GAME_PLAYER];				//������Ŀ
	byte							cbDiscardCard[GAME_PLAYER][60];				//������¼

	//�˿�����
	byte							cbCardCount;								//�˿���Ŀ
	byte							cbCardData[MAX_COUNT];						//�˿��б�
	byte							cbSendCardData;								//�����˿�

	//����˿�
	byte							cbWeaveCount[GAME_PLAYER];					//�����Ŀ
	CMD_WeaveItem					WeaveItemArray[GAME_PLAYER][MAX_WEAVE];		//����˿�

	//������Ϣ
	word							wHeapHead;									//����ͷ��
	word							wHeapTail;									//����β��
	byte							cbHeapCardInfo[GAME_PLAYER][2];				//������Ϣ
	word							wTableOwner;						        //�������
};

//��Ϸ��ʼ
// struct CMD_S_GameStart
// {
// 	longlong						lSiceCount;									//���ӵ���
// 	word							wBankerUser;								//ׯ���û�
// 	word							wCurrentUser;								//��ǰ�û�
// 	byte							cbUserAction;								//�û�����
// 	byte							cbCardData[MAX_COUNT];						//�˿��б�
// 	word							wHeapHead;									//������ͷ
// 	word							wHeapTail;									//������β
// 	byte							cbHeapCardInfo[GAME_PLAYER][2];				//������Ϣ
// };

//��Ϸ��ʼ
struct CMD_S_GameStart
{
	long							lSiceCount;						//���ӵ���
	word							wBankerUser;						//ׯ���û�
	word							wCurrentUser;						//��ǰ�û�
	word							wReplaceUser;						//�����û�	����
	byte							cbUserAction;						//�û�����
	byte							cbCardData[MAX_COUNT];					//�˿��б�
	byte							cbQuanFeng;						//Ȧ��
	word							wHeapHead;						//������ͷ
	word							wHeapTail;						//������β
	byte							cbTailCount[GAME_PLAYER];		// β����Ŀ
	byte							cbHeapCardInfo[GAME_PLAYER][2];				//������Ϣ
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
	byte							cbCardData;						//�˿�����
	byte							cbGangCardData;						//��������
	byte							cbActionMask;						//��������
	word							wCurrentUser;						//��ǰ�û�
	word							wReplaceUser;						//�����û�
	word							wSendCardUser;						//�����û�
	bool							bTail;							//ĩβ����
};

//������ʾ
struct CMD_S_OperateNotify		// �Ѿ��鿴
{
	word							wResumeUser;						//��ԭ�û�
	byte							cbActionMask;						//��������
	byte							cbActionCard;						//�����˿�
};

//��������
struct CMD_S_OperateResult		// �Ѿ��鿴
{
	word							wOperateUser;						//�����û�
	byte							cbActionMask;						//��������
	word							wProvideUser;						//��Ӧ�û�
	byte							cbOperateCode;						//��������
	byte							cbOperateCard[3];					//�����˿�
};

//��Ϸ����
struct CMD_S_GameEnd			// �Ѿ��鿴
{
	word							wLeftUser;							//�������
	longlong						lGameTax;							//��Ϸ˰��
																		//������Ϣ
	word							wProvideUser;						//��Ӧ�û�
	byte							cbProvideCard;						//��Ӧ�˿�
	dword							dwChiHuKind[GAME_PLAYER];				//��������
	dword							dwChiHuRight[GAME_PLAYER][MAX_RIGHT_COUNT];		//��������
	byte							cbFanCount;							//�ܷ���

																		//������Ϣ
	longlong						lGameScore[GAME_PLAYER];			//��Ϸ����
	longlong						lGangScore[GAME_PLAYER];			//���ƻ���

																		//�˿���Ϣ
	byte							cbCardCount[GAME_PLAYER];			//�˿���Ŀ
	byte							cbCardData[GAME_PLAYER][MAX_COUNT];	//�˿�����

};

struct CMD_S_QGangCard
{
	byte							cbHuCard;							//������
	word							wProvideUser;						//��Ӧ�û�
};

//�û��й�
struct CMD_S_Trustee
{
	bool							bTrustee;							//�Ƿ��й�
	word							wChairID;							//�й��û�
	bool							bSystemSet;							//ϵͳ����
};

//��������
struct CMD_S_ReplaceCard
{
	word							wReplaceUser;						//�����û�
	byte							cbReplaceCard;						//�����˿�
};

//////////////////////////////////////////////////////////////////////////
//�ͻ�������ṹ

#define SUB_C_OUT_CARD				1									//��������
#define SUB_C_OPERATE_CARD			3									//�����˿�
#define SUB_C_TRUSTEE				4									//�û��й�
#define SUB_C_REPLACE_CARD			5									//�û�����
#define SUB_C_SET_BASE_SCORE		6									//���õ�ע

#define SUB_C_GETCARD               7                                   //��ȡ����
#define SUB_S_SETCARD               8                                   //���͵���
#define SUB_C_CARD_CONTROL			9									//�˿˿���

#define SUB_C_SET_LOSER				10									//����
#define SUB_C_ANDROID_EXIT			11									//�������˳�

struct CMD_C_CardControl
{
	byte cbCardIndex;
};

struct CMD_S_SETCARD
{
	byte  cbCardDatap[4][14];
};


//���õ�ע
struct CMD_C_SetBaseScore
{
	longlong						lBaseScore;							//��Ϸ��ע
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
	byte							cbOperateCard[3];					//�����˿�
};

//�û��й�
struct CMD_C_Trustee
{
	bool							bTrustee;							//�Ƿ��й�
	bool							bSystemSet;							//ϵͳ����
};

//��������
struct CMD_C_ReplaceCard
{
	byte							cbCardData;							//�˿�����
};

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

//���ڲ����ת����������ƿ��Դ����������ʹ�ã�����Ϊ����������������ΪMAX_INDEX. ע:����滻����������,������.
#define	INDEX_REPLACE_CARD					MAX_INDEX

//////////////////////////////////////////////////////////////////////////
//�߼�����

#define	MASK_COLOR					0xF0								//��ɫ����
#define	MASK_VALUE					0x0F								//��ֵ����

//////////////////////////////////////////////////////////////////////////
//��������

//������־
#define WIK_NULL					0x00								//û������
#define WIK_LEFT					0x01								//�������	// ���˺��б� û�� ����
#define WIK_CENTER					0x02								//�г�����  // ���˺��б� û�� ����
#define WIK_RIGHT					0x04								//�ҳ�����  // ���˺��б� û�� ����
#define WIK_PENG					0x08								//��������
#define WIK_GANG					0x10								//��������
#define WIK_LISTEN					0x20								//��������
#define WIK_CHI_HU					0x40								//�Ժ�����
#define WIK_REPLACE					0x80								//�����滻

//////////////////////////////////////////////////////////////////////////
//���ƶ���
#define CHR_NULL					0x00000000							//��Ȩλ
#define CHR_JI_HU					0x00000001							//����
#define CHR_PENG_PENG				0x00000004							//������
#define CHR_ZI_MO					0x00000008							//����
#define CHR_QI_XIAO_DUI				0x00000010							//��С����
#define CHR_HH_QI_DUI				0x00000020							//����7��	
#define CHR_CHH_QI_DUI				0x00000040							//������7��	
#define CHR_CCHH_QI_DUI				0x00000080							//��������7��

#define CHR_DI						0x00000100							//�غ�Ȩλ
#define CHR_TIAN					0x00000200							//���Ȩλ
#define CHR_QING_YI_SE				0x00000400							//��һɫ��
#define CHR_QIANG_GANG				0x00000800							//����Ȩλ
#define CHR_HDLY					0x00001000							//��������
#define CHR_ZI_YI_SE				0x00002000							//��һɫ��
#define CHR_FENG_YAO_JIU			0x00004000							//���۾�
#define CHR_QUAN_YAO_JIU			0x00008000							//ȫ�۾� 
#define CHR_LUO_HAN				    0x00040000							//ʮ���޺�	
#define CHR_SHI_SAN_YAO				0x00080000							//ʮ������
#define CHR_KAN_KAN					0x00100000							//������ �İ���
#define CHR_MEN_QI_QING				0x00200000							//����
#define CHR_HUN_YI_SE				0x00400000							//��һɫ	
#define CHR_GSH						0x00800000							//���Ͽ���	
#define CHR_WU_BAOPAI				0x01000000							//�ޱ���		// 2012.2.29

//////////////////////////////////////////////////////////////////////////
#define HONGZHONG_BAOPAI			0x35	

//#pragma pack()
#endif
