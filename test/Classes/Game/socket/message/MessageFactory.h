#ifndef _MESSAGEFACTORY_H_
#define _MESSAGEFACTORY_H_

#include "socket/network/Packet.h"

class MessageFactory 
{
public :
	
	virtual ~MessageFactory ()  {}

	virtual Packet*		CreateMessage ()  {return 0;}

	virtual PacketID_t	GetPacketID ()const {return PACKET_MAX_ID;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};



#endif
