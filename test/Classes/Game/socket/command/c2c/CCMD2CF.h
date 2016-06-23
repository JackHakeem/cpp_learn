/*
������� ����BOSS������Ϣ
CMSG_WORLDBOSS_PLAYERINFO = 0X2CF			
�����->�ͻ���, ���ṹ:��
*/

#ifndef _CCMD2CF_H_
#define _CCMD2CF_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2CF : public Packet
{
public:
	CCMD2CF() {}
	virtual ~CCMD2CF() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLDBOSS_PLAYERINFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	
};

bool CCMD2CF::Write()
{
	return true;
}


class CCMD2CDFactory: public MessageFactory
{
public :
	
	virtual ~CCMD2CDFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLDBOSS_PLAYERINFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif