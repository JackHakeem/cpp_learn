#include "Packet.h"

#define createbuffer(x) new char[QYMAXLEN];memset(x,0, QYMAXLEN);

Packet::Packet()
{
	m_nLen = 0;
	m_nCursor = 0;
	//m_body = createbuffer(m_body);
	//m_state = true;
	memset(m_body, 0, QYMAXLEN);
}

Packet::Packet(const Packet& packet)
{
	//m_body = createbuffer(m_body);
	memset(m_body, 0, QYMAXLEN);
	int len = strlen(packet.m_body);
	strncpy(m_body, packet.m_body, len);
	m_body[len] = '\0';

	m_nLen = packet.m_nLen;
	m_nCursor = packet.m_nCursor;
}

Packet::~Packet()
{
	//if (m_body)
	//	delete []m_body;
}

char* Packet::encode()
{
	char* ba = createbuffer(ba);
	uint16 packetID = getPacketID();
	uint16 len = m_nLen + ENGINE_HEAD_LENGTH + PACKET_TYPE_LENGTH;
	memcpy(ba, (void*)(&len), ENGINE_HEAD_LENGTH);
	memcpy(ba+ENGINE_HEAD_LENGTH, (void*)(&packetID), PACKET_TYPE_LENGTH);
	memcpy(ba+ENGINE_HEAD_LENGTH+PACKET_TYPE_LENGTH, m_body, m_nLen);
	return ba;
}

void Packet::writeBoolean( bool data )
{
	memcpy(m_body+m_nCursor, (const void*)(&data), 1);
	m_nCursor+=1;
	m_nLen+=1;
}

void Packet::writeByte( unsigned char data )
{
	memcpy(m_body+m_nCursor, (const void*)(&data), 1);
	m_nCursor+=1;
	m_nLen+=1;
}

void Packet::writeBytes( const char * ba, uint32 nlen )
{
	/*if (!m_body)
	{
		m_body = createbuffer(m_body);

	}*/

	if (m_nCursor + nlen >= QYMAXLEN)
	{
		// 为什么会有这么大的包？
		return;
		while(1);
	}

	memcpy(m_body+m_nCursor, ba, nlen);
	m_nCursor+=nlen;
	m_nLen+=nlen;
}

void Packet::writeBytes( const Packet* data )
{
	if (m_nCursor + data->m_nLen >= QYMAXLEN)
	{
		// 为什么会有这么大的包？
		return;
		while(1);
	}

	memcpy(m_body+m_nCursor, data->m_body, data->m_nLen);
	m_nCursor+=data->m_nLen;
	m_nLen+=data->m_nLen;
}

void Packet::writeShort( short data )
{
	memcpy(m_body+m_nCursor, (const void*)(&data), 2);
	m_nCursor+=2;
	m_nLen+=2;
}

void Packet::writeInt( int data )
{
	memcpy(m_body+m_nCursor, (const void*)(&data), 4);
	m_nCursor+=4;
	m_nLen+=4;
}

void Packet::writeUint( unsigned int data )
{
	memcpy(m_body+m_nCursor, (const void*)(&data), 4);
	m_nCursor+=4;
	m_nLen+=4;
}

void Packet::writeFloat( float data )
{
	memcpy(m_body+m_nCursor, (const void*)(&data), 4);
	m_nCursor+=4;
	m_nLen+=4;
}

void Packet::writeString( const char* data )
{
	unsigned short len = strlen(data);
	memcpy(m_body+m_nCursor, (void*)(&len), 2);
	m_nCursor+=2;
	m_nLen+=2;

	memcpy(m_body+m_nCursor, data, len);
	m_nCursor+=len;
	m_nLen+=len;
}

bool Packet::readBoolean()
{
    if (m_nCursor >= m_nLen)
    {
        return false;
    }
	bool data;
	memcpy((void*)(&data), m_body+m_nCursor, 1);
	m_nCursor+=1;
	return data;
}

unsigned char Packet::readByte()
{
    if (m_nCursor >= m_nLen)
    {
        return 0;
    }
	unsigned char data;
	memcpy((void*)(&data), m_body+m_nCursor, 1);
	m_nCursor+=1;
	return data;
}

void Packet::readBytes( Packet *data, uint32 beginpos, uint32 subLen )
{
    
    if (m_nCursor >= m_nLen)
    {
        return;
    }
	memcpy(data->m_body + beginpos, m_body+m_nCursor, subLen);
	m_nCursor+=subLen;
	//return data;
}

unsigned char Packet::readUbyte()
{
    if (m_nCursor >= m_nLen)
    {
        return 0;
    }
	unsigned char data;
	memcpy((void*)(&data), m_body+m_nCursor, 1);
	m_nCursor+=1;
	return data;
}

short Packet::readShort()
{
    
    if (m_nCursor >= m_nLen)
    {
        return 0;
    }
	short data;
	memcpy((void*)(&data), m_body+m_nCursor, 2);
	m_nCursor+=2;
	return data;
}

int16 Packet::readUshort()
{
    if (m_nCursor >= m_nLen)
    {
        return 0;
    }
	unsigned short data;
	memcpy((void*)(&data), m_body+m_nCursor, 2);
	m_nCursor+=2;
	return data;
}

int Packet::readInt()
{
    if (m_nCursor >= m_nLen)
    {
        return 0;
    }
	int data;
	memcpy((void*)(&data), m_body+m_nCursor, 4);
	m_nCursor+=4;
	return data;
}

uint32 Packet::readUint()
{
    if (m_nCursor >= m_nLen)
    {
        return 0;
    }
	uint32 data;
	memcpy((void*)(&data), m_body+m_nCursor, 4);
	m_nCursor+=4;
	return data;
}

float Packet::readFloat()
{
    if (m_nCursor >= m_nLen)
    {
        return 0;
    }
	float data;
	memcpy((void*)(&data), m_body+m_nCursor, 4);
	m_nCursor+=4;
	return data;
}

std::string  Packet::readString()
{
    if (m_nCursor >= m_nLen)
    {
        return "";
    }
	unsigned int len = 0;
	memcpy((void*)(&len) , m_body+m_nCursor, 2);
	m_nCursor+=2;

	char data[1024] = {0};
	memcpy(data, m_body+m_nCursor, len);
	m_nCursor+=len;
	return std::string(data);
}
