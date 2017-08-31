#ifndef _PacketAide_H_
#define _PacketAide_H_

#include <string>
#include "Convert.h"

/**
 * 数据包读取辅助
 */
class PacketAide
{
private:
	unsigned char* mData;
	int mPos;
public:
	/**
	 * @param data 网络数据
	 * @param index 起始下标
	 */
	PacketAide(unsigned char* data, int pos = 0);
	void setPosition(int pos);
	int getPosition() const;
	unsigned char* getBuffer();
	unsigned int readByte();
	unsigned int read2Byte();
	unsigned int read4Byte();
	unsigned int* read4Bytes(unsigned int* ary, int count);
	long long read8Byte();

	void writeByte(unsigned int val);
	void write2Byte(unsigned int val);
	void write4Byte(unsigned int val);
	void write4Bytes(unsigned int* ary, int count);
	void write8Byte(long long val);

	/**
	 * @param len (utf16的长度/2)
	 */
	void writeString(const std::string& utf8, int len);

	void writeString_UTF8(const std::string& utf8, int len);
	/**
	 * @param len (utf16的长度/2)
	 */
	std::string readString(int len);

	std::string readString_bak(int len);

	std::string readStringFromAnsi_2(int len);

	// readStringFrom Ansi to UTF-8
	std::string readStringFromAnsi(int len);

	

};

#define PACKET_AIDE_SIZE(size) unsigned char __PacketBuffer__[size]={0}; PacketAide packet(__PacketBuffer__)
#define PACKET_AIDE_DATA(data) PacketAide packet((unsigned char*)data)
#endif // _PacketAide_H_
