/**
* client requests battle winning streak info
CMSG_WORLD_PVP_QUALIFYING_STAR = 0x360
Client -> server, the package structure
byte 0
 
 */

#ifndef _CCMD362_H_
#define _CCMD362_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD362 : public Packet
{
public:
	CCMD362() 
	{
		
	}

	virtual ~CCMD362() {}

	virtual bool	Write();	 

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_QUALIFYING_CHALLENGE;}
													
	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	uint32 param;
};


class CCMD362Factory: public MessageFactory
{
public :

	virtual ~CCMD362Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_QUALIFYING_CHALLENGE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif