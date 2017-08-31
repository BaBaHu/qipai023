#include "PacketAide.h"

PacketAide::PacketAide(unsigned char* data, int pos)
	: mData(data)
	, mPos(pos)
{}

void PacketAide::setPosition(int pos)
{
	mPos = pos;
}

int PacketAide::getPosition() const
{
	return mPos;
}

unsigned char* PacketAide::getBuffer()
{
	return mData;
}

unsigned int PacketAide::readByte()
{
	unsigned int ret = mData[mPos+0];
	mPos += 1;
	return ret;
}

unsigned int PacketAide::read2Byte()
{
	unsigned int ret = ((unsigned int)((mData[mPos+1]&0xff)<<8) | (mData[mPos+0]&0xff));
	mPos +=2;
	return ret;
}

unsigned int PacketAide::read4Byte()
{
	unsigned int ret = (
		((unsigned int)(mData[mPos+3]&0xff)<<24) | 
		((unsigned int)(mData[mPos+2]&0xff)<<16) |
		((unsigned int)(mData[mPos+1]&0xff)<< 8) |
		((unsigned int)(mData[mPos+0]&0xff)));
	//ipone 会报错 ARM EXC_ARM_DA_ALIGN
	//unsigned int ret = *(unsigned int*)&mData[mPos];
	mPos +=4;
	return ret;
}

unsigned int* PacketAide::read4Bytes(unsigned int* ary, int count)
{
	int size = count*sizeof(unsigned int);
	memcpy(ary, &mData[mPos], size);
	mPos+=size;
	return ary;
}
	
long long PacketAide::read8Byte()
{
	long long ret = (
		((long long)(mData[mPos+7]&0xff)<<56) | 
		((long long)(mData[mPos+6]&0xff)<<48) | 
		((long long)(mData[mPos+5]&0xff)<<40) | 
		((long long)(mData[mPos+4]&0xff)<<32) | 
		((long long)(mData[mPos+3]&0xff)<<24) | 
		((long long)(mData[mPos+2]&0xff)<<16) |
		((long long)(mData[mPos+1]&0xff)<< 8) |
		((long long)(mData[mPos+0]&0xff)));

	mPos +=8;
	return ret;
}

void PacketAide::writeByte(unsigned int val)
{
	mData[mPos+0] = (unsigned char)(val&0xff);
	mPos +=1;
}

void PacketAide::write2Byte(unsigned int val)
{
	mData[mPos+1] = (unsigned char)((val>>8)&0xff);
	mData[mPos+0] = (unsigned char)((val)&0xff);
	mPos +=2;
}

void PacketAide::write4Byte(unsigned int val)
{
	mData[mPos+3] = (unsigned char)((val>>24) & 0xff);
	mData[mPos+2] = (unsigned char)((val>>16) & 0xff);
	mData[mPos+1] = (unsigned char)((val>> 8) & 0xff);
	mData[mPos+0] = (unsigned char)((val)     & 0xff);
	//ipone 会报错 ARM EXC_ARM_DA_ALIGN
	//unsigned int* pVal = (unsigned int*)&mData[mPos];
	//*pVal = val;
	mPos +=4;
}

void PacketAide::write4Bytes(unsigned int* ary, int count)
{
	int size = count*sizeof(unsigned int);
	memcpy(&mData[mPos], ary, size);
	mPos+=size;
}

void PacketAide::write8Byte(long long val)
{
	mData[mPos+7] = (unsigned char)((val>>56) & 0xff);
	mData[mPos+6] = (unsigned char)((val>>48) & 0xff);
	mData[mPos+5] = (unsigned char)((val>>40) & 0xff);
	mData[mPos+4] = (unsigned char)((val>>32) & 0xff);
	mData[mPos+3] = (unsigned char)((val>>24) & 0xff);
	mData[mPos+2] = (unsigned char)((val>>16) & 0xff);
	mData[mPos+1] = (unsigned char)((val>> 8) & 0xff);
	mData[mPos+0] = (unsigned char)( val      & 0xff);
	mPos +=8;
}

void PacketAide::writeString(const std::string& utf8, int len)
{
	std::string ucs2 = u2l(utf8);
	ucs2.resize(len * 2, '\0');
	memcpy(&mData[mPos], &ucs2[0], ucs2.size());
	mPos += ucs2.size();
}

void PacketAide::writeString_UTF8(const std::string& utf8, int len)
{
	std::string ucs2 = utf8;
	ucs2.resize(len , '\0');
	memcpy(&mData[mPos], &ucs2[0], ucs2.size());
	mPos += ucs2.size();
}

std::string PacketAide::readString(int len)
{
	std::string ret;
	ret.resize(len, '\0');
	memcpy(&ret[0], &mData[mPos], len);
	mPos += len;
	return ret;
}

std::string PacketAide::readString_bak(int len)
{
	std::string ret;
	ret.resize(len * 2 + 2, '\0');
	memcpy(&ret[0], &mData[mPos], len * 2);
	mPos += len * 2;
	return l2u(ret);
}

std::string PacketAide::readStringFromAnsi_2(int len)
{
	std::string ret;
	ret.resize(len, '\0');
	memcpy(&ret[0], &mData[mPos], len);
	mPos += len;
	return ret;
}

std::string PacketAide::readStringFromAnsi(int len)
{
	std::string ret;
	ret.resize(len , '\0');
	memcpy(&ret[0], &mData[mPos], len);
	mPos += len ;
	return string_To_UTF8(ret);
}