/****************************************************************************
 Copyright (c) 2011 4399
 Copyright (c) 2011 ”‡œ„π§◊˜ “

 author	:zhangcheng
 email	:45612592@qq.com
 web	:http://45612592.qzone.qq.com
 data	:2011/11/19
 ****************************************************************************/

#ifndef __PACKET_H__
#define __PACKET_H__

#include "BaseType.h"

#define  QYMAXLEN 40960
#define  ENGINE_HEAD_LENGTH  (2)
#define  PACKET_TYPE_LENGTH  (2)

class Packet
{
public:
	uint32 m_nLen;
	uint32 m_nCursor;
	char m_body[QYMAXLEN];
	std::string	m_strType;
	//Set up if processing packets
	//static bool m_state;

	Packet();
	Packet(const Packet& packet);
	virtual ~Packet();

	char* encode();



	void writeBoolean( bool data);

	void writeByte( unsigned char data );

	void writeBytes( const char * ba, uint32 nlen);

	void writeBytes( const Packet* data );

	void writeShort( short data);

	void writeInt( int data );

	void writeUint( unsigned int data );

	void writeFloat( float data);

	void writeString( const char* data);

	bool readBoolean();

		/*  -128 ~ 127 */
	unsigned char readByte();

	void readBytes(Packet *data, uint32 beginpos, uint32 subLen);

		/*  0 ~ 255 */
	unsigned char readUbyte();

		/* -32768 ~ 32767 */
	short readShort();

		/* 0 ~ 65536 */
	int16 readUshort();

		/* -2147483648 ~ 2147483647 */
	int readInt();

		/* 0 ~ 4294967259 */
	uint32 readUint();

	float readFloat();

	std::string readString();

	virtual int32 	Execute() {return 0;}
	virtual bool	Write() {return false;}
	virtual bool	Read() {return false;}
	virtual PacketID_t getPacketID() const {return PACKET_MAX_ID;}
};

#endif
