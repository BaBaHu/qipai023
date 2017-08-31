#ifndef DYNAMICPACK_H
#define DYNAMICPACK_H

class CDynamicPack
{
	CDynamicPack()
	{
		m_byBuffRef = NULL;
		m_wRWPos = 0;
	}
public:
	CDynamicPack(byte* pBuffer, word wBuffSize)
	{
		m_byBuffRef = pBuffer;
		m_wRWPos = 0;
		m_wBuffSize = wBuffSize;
	}

	void* Get(void* buf, word bytes)
	{
		if(NULL == buf || m_wRWPos + bytes > m_wBuffSize)
			return NULL;
		memcpy(buf, m_byBuffRef+m_wRWPos, bytes);
		m_wRWPos += bytes;
		return buf;
	}

	bool Put(void* buf, word bytes)
	{
		if(m_wRWPos + bytes > m_wBuffSize)
			return false;
		memcpy(m_byBuffRef+m_wRWPos, buf, bytes);
		m_wRWPos += bytes;
		return true;
	}
	//只支持基本类型 及 只有基本类型组成的结构
	template<typename T>
	T Get()
	{
		T t;
		if(NULL==Get(&t, sizeof(T)))
			return (T)0;
		return t;
	}

	template<typename T>
	bool Put(const T& t)
	{
		return Put((void*)&t, sizeof(T));
	}

	word GetString(char szOut[], word wBufLen)
	{
		word wLen = Get<word>();
		if(wLen < 1)
			return wLen;
		word byts = wLen*2;//TCHAR
		if(m_wRWPos + byts > m_wBuffSize)
			return 0;
		memcpy(szOut, m_byBuffRef+m_wRWPos, wBufLen<byts?wBufLen:byts);
		if(wLen + 1 < wBufLen)
			szOut[wLen] = 0;
		m_wRWPos += byts;
		return wLen;
	}

	word PutString(const char szPut[])
	{
		if(NULL == szPut)
			return 0;
		word wLen = strlen(szPut)*2;
		if(!Put<word>(wLen))
			return 0;
		if(Put((void*)szPut, wLen*2))
			return wLen;
		return 0;
	}

	word	 GetPos()
	{
		return m_wRWPos;
	}

	bool isToEnd()
	{
		return m_wRWPos >= m_wBuffSize;
	}
private:
	byte* m_byBuffRef;
	word  m_wBuffSize;
	word  m_wRWPos;
};

#endif