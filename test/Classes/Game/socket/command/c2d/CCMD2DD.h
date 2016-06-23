/**
 *CMSG_WORLD_ UPGRADE_BALL		= 0X2DD			
�ͻ���->�����, ���ṹ:
Uint8   λ������(��������������Ӷ������)
Uint32�����������Ӷ��ΨһID(����ڱ����У����Ǳ���λ��)
Uint32  ��������ΨһID
Uint8   �������������
 
 */

#ifndef _CCMD2DD_H_
#define _CCMD2DD_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2DD : public Packet
{
public:
	CCMD2DD() {}
	virtual ~CCMD2DD() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLDBOSS_QUIT;}

	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	uint8 a_locType;
	int32 b_mercId;
	int32 c_jadeId;
	uint8 d_spType;
};

bool CCMD2DD::Write()
{
	a_locType = readUbyte();
	b_mercId = readInt();
	c_jadeId = readInt();
	d_spType = readUbyte();
	return true;
}


class CCMD2DDFactory: public MessageFactory
{
public :
	
	virtual ~CCMD2DDFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLDBOSS_QUIT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif