/**
* client requests Server to return a packet
CMSG_NETWORK_DELAY_REQ = 0x41E,// ÍøÂçÑÓÊ±Í³¼ÆÉêÇë
Client -> server, the package structure
byte 0
 
 */

#ifndef _CCMD41E_H_
#define _CCMD41E_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD41E : public Packet
{
public:
	CCMD41E() 
	{
		a_req = 0;
		b_delay = 0;
	}

	virtual ~CCMD41E() {}

	virtual bool	Write();	 

	virtual PacketID_t getPacketID() const { return CMSG_NETWORK_DELAY_REQ;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	 int8 a_req;
	 uint32 b_delay;
};


class CCMD41EFactory: public MessageFactory
{
public :

	virtual ~CCMD41EFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_NETWORK_DELAY_REQ;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif