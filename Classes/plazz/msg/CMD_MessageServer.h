#ifndef CMD_MESSAGE_HEAD_FILE
#define CMD_MESSAGE_HEAD_FILE

#pragma pack(1)


//////////////////////////////////////////////////////////////////////////////////
//Я����Ϣ

#define DTP_GP_UI_TASK_TARGET				1									//����Ŀ��
#define DTP_GP_UI_TASK_ORDER				2									//����˵��
#define DTP_GP_UI_TASK_NAME					3									//��������
#define DTP_GP_UI_TASK_AWARD				4									//������


//////////////////////////////////////////////////////////////////////////////////
//������Ϣ

#define MDM_GP_MSG_LOGON					1	//��½��Ϣ

#define SUB_GP_MSG_SEND_LOGON				1	//���͵�½
#define SUB_GP_MSG_LOGON_FINISH				100	//��½���

//struct CMD_GP_MSGSendLogon
//{
//	DWORD			dwUserID;
//};

#define MDM_GP_CHAT							2	//������Ϣ

//�ͻ��˷���
#define SUB_GP_C_USER_CHAT					1	//�û�����
#define SUB_GP_C_USER_EXPRESSION			2	//�û�����

//����˷���
#define SUB_GP_S_USER_CHAT					100	//�û�����
#define SUB_GP_S_USER_EXPRESSION			101	//�û�����

////�û�����
//struct CMD_GP_C_UserChat
//{
//	DWORD							dwUserID;							//�û�ID
//	DWORD							dwChatColor;						//��Ϣ��ɫ
//	WORD							wChatLength;						//���ֳ���
//	TCHAR							szNickName[LEN_NICKNAME];			//�û��ǳ�
//	TCHAR							szChatString[LEN_USER_CHAT];		//������Ϣ
//};
//
////�û�����
//struct CMD_GP_S_UserChat
//{
//	DWORD							dwUserID;							//�û�ID
//	DWORD							dwChatColor;						//��Ϣ��ɫ
//	WORD							wChatLength;						//���ֳ���
//	TCHAR							szNickName[LEN_NICKNAME];			//�û��ǳ�
//	TCHAR							szChatString[LEN_USER_CHAT];		//������Ϣ
//};
//
////�û�����
//struct CMD_GP_C_UserExpression
//{
//	DWORD							dwUserID;							//�û�ID
//	WORD							wItemIndex;							//��������
//	TCHAR							szNickName[LEN_NICKNAME];			//�û��ǳ�
//};
//
////�û�����
//struct CMD_GP_S_UserExpression
//{
//	DWORD							dwUserID;							//�û�ID
//	WORD							wItemIndex;							//��������
//	TCHAR							szNickName[LEN_NICKNAME];			//�û��ǳ�
//};

#define MDM_GP_MSG_SYSTEM					3	//ϵͳ��Ϣ
#define SUB_GP_C_BUGLE_MESSAGE				1	//������Ϣ

#define SUB_GP_S_BUGLE_MESSAGE				101	//������Ϣ
#define SUB_GP_S_MESSAGE					102	//ϵͳ��Ϣ


////������Ϣ
//struct CMD_GP_C_BugleMessage
//{
//	DWORD							dwUserID;							//�û�ID
//	BYTE							cbBugleType;						//�������� 0��С���� 1��������
//	BYTE							cbCount;							//����
//	DWORD							dwDelay;							//�ӳ�
//	DWORD							dwChatColor;						//��Ϣ��ɫ
//	WORD							wChatLength;						//���ֳ���
//	TCHAR							szNickName[LEN_NICKNAME];			//�û��ǳ�
//	TCHAR							szPassword[LEN_PASSWORD];			//��½����
//	TCHAR							szChatString[LEN_USER_CHAT];		//������Ϣ
//};
//
////������Ϣ
//struct CMD_GP_S_BugleMessage
//{
//	DWORD							dwUserID;							//�û�ID
//	BYTE							cbBugleType;						//��������
//	DWORD							dwChatColor;						//��Ϣ��ɫ
//	WORD							wChatLength;						//���ֳ���
//	TCHAR							szNickName[LEN_NICKNAME];			//�û��ǳ�
//	TCHAR							szChatString[LEN_USER_CHAT];		//������Ϣ
//};
//
////ϵͳ��Ϣ
//struct CMD_GP_SystemMessage
//{
//	WORD							wType;								//��Ϣ����
//	WORD							wLength;							//��Ϣ����
//	TCHAR							szMessage[128];						//��Ϣ����
//};


//////////////////////////////////////////////////////////////////////////////////


//������Ϣ
#define MDM_GP_MSG_TASK								4	//������Ϣ

#define SUB_GP_C_LOGON_TASK							1	//��½����
#define SUB_GP_C_TASK_OPERATION						2	//��½����

#define SUB_GP_S_TASK_TYPE							101	//��������
#define SUB_GP_S_TASK_LIST							102	//�����б�
#define SUB_GP_S_TASK_OPERATION						103	//�������
#define SUB_GP_S_OPERATION_FAILE					104	//����ʧ��


////��ȡ��������
//struct CMD_GP_C_GetTask 
//{
//	DWORD							dwUserID;						//�û�ID
//};
//
////�������
//struct CMD_GP_C_TaskOperation
//{
//	DWORD							dwUserID;						//�û�ID
//	WORD							wTaskID;						//����ID
//	WORD							wTaskOperation;					//������� 0����ȡ���� 1����ȡ����
//};
//
//
////�����б�
//struct CMD_GP_LoadTaskList
//{
//	WORD							wTaskID;							//����I	D
//	WORD							wTaskState;							//����״̬
//	WORD							wTaskTypeID;						//��������
//	WORD							wKindID;							//Ŀ����Ϸ
//	WORD							wTargetTotal;						//Ŀ������
//	WORD							wCompletionTotal;					//�������
//	WORD							wSortID;							//�����ʾ
//};
//
//
////�������
//struct CMD_GP_S_TaskOperation
//{
//	DWORD							dwUserID;						//�û�ID
//	WORD							wTaskID;						//����ID
//	WORD							wTaskOperation;					//������� 0����ȡ���� 1����ȡ����
//};
//
//
//
////ʧ����Ϣ
//struct CMD_GP_Faile
//{
//	int								nError;								//�������
//	TCHAR							szMessage[128];						//������Ϣ
//};






#pragma pack()

#endif



