#ifndef MACRO_HEAD_FILE
#define MACRO_HEAD_FILE

//////////////////////////////////////////////////////////////////////////////////
//常用常量

//无效数值
#define INVALID_BYTE				((byte)(0xFF))						//无效数值
#define INVALID_WORD				((word)(0xFFFF))					//无效数值
#define INVALID_DWORD				((dword)(0xFFFFFFFF))				//无效数值

#ifndef INADDR_NONE
#define INADDR_NONE					0xffffffff
#endif // !INADDR_NONE

//////////////////////////////////////////////////////////////////////////////////

//数组维数
#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))

//无效地址
#define INVALID_IP_ADDRESS(IPAddress) (((IPAddress==0L)||(IPAddress==INADDR_NONE)))

//////////////////////////////////////////////////////////////////////////////////

//接口释放
#define SafeRelease(pObject) { if (pObject!=0) { pObject->Release(); pObject=0; } }

//删除指针
#define SafeDelete(pData) { try { delete pData; } catch (...) { ASSERT(FALSE); } pData=0; } 

//删除数组
#define SafeDeleteArray(pData) { try { delete [] pData; } catch (...) { ASSERT(FALSE); } pData=0; } 

//自定义桌子id 转换(5位长度 serverid*100 + tableid,每个服务器的桌子数不能超过100) 改动过
#define MakeCustomTableUUID(serverid,tableid)  ((serverid)*100)+(tableid)
#define ServerIDByUUID(uuid) (uuid)/100
#define TableIDbyUUID(uuid)  (uuid)%100


#define CHECK_STRUCTSIZE(stStruct,wDataSize)  \
	ASSERT(sizeof(stStruct) == (wDataSize));  \
if (sizeof(stStruct) != (wDataSize)) \
	return false;
//////////////////////////////////////////////////////////////////////////////////

#endif