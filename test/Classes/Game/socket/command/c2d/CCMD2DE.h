#ifndef _CCMD2DE_H_
#define _CCMD2DE_H_
/**
 *�ͻ������󴫳�	
CMSG_WORLD_HERITAGE = 0x2DE
�ͻ���->�����, ���ṹ
Uint8		��������:0 ��ͨ����, 1 ��������
Uint8		Դ��Ʒλ�����ͣ�����/���ϣ�
Uint8		Դ��Ʒ����λ��
Uint32		Դ��Ʒ������ٸ��ΨһID���ڱ�����Ϊ0��
Uint8		Ŀ����Ʒλ�����ͣ�����/���ϣ�
Uint8		Ŀ����Ʒ����λ��
Uint32		Ŀ����Ʒ������ٸ��ΨһID���ڱ�����Ϊ0��
 */

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2DE : public Packet
{
public:
	CCMD2DE() {}
	virtual ~CCMD2DE() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_HERITAGE;}

	virtual	int32		GetMessageSize( ) const { return 0;}
	
	int8 a_type;
	int8 b_sPos;
	int8 c_sSit;
	int d_sRoleId;
	int8 e_sPos;
	int8 f_sSit;
	int g_sRoleId;
};

bool CCMD2DE::Write()
{
	writeByte( a_type );
	writeByte( b_sPos );
	writeByte( c_sSit );
	writeInt( d_sRoleId );
	writeByte( e_sPos );
	writeByte( f_sSit );
	writeInt( g_sRoleId );

	return true;
}


class CCMD2DEFactory: public MessageFactory
{
public :

	virtual ~CCMD2DEFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_HERITAGE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif