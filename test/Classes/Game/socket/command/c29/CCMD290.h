/**
CMSG_REP_CAN_HIRE_MAX_MER_NUM = 0x290 (656)
clent->server
 */

#ifndef _CCMD290_H_
#define _CCMD290_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD290 : public Packet
{
public:
	CCMD290() {}
	virtual ~CCMD290() {}


	virtual bool	Write() { return true; }
public :
	virtual PacketID_t getPacketID() const  { return CMSG_REP_CAN_HIRE_MAX_MER_NUM;}	
	virtual	int32		GetMessageSize( ) const { return 0;}
};


class CCMD290Factory: public MessageFactory
{
public :
	
	virtual ~CCMD290Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_REP_CAN_HIRE_MAX_MER_NUM;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif 