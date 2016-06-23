/**
������� ����BOSS�BOSS��Ϣ
CMSG_WORLDBOSS_BOSSINFO = 0X2DC		
�����->�ͻ���, ���ṹ:��
*/

#ifndef _CCMD2DC_H_
#define _CCMD2DC_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2DC : public Packet
{
public:
	CCMD2DC() {}
	virtual ~CCMD2DC() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLDBOSS_BOSSINFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	
};

bool CCMD2DC::Write()
{
	return true;
}


class CCMD2DCFactory: public MessageFactory
{
public :
	
	virtual ~CCMD2DCFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLDBOSS_BOSSINFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif