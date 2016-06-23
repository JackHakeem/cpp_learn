/**
* client requests battle winning streak info
CMSG_WORLD_PVP_QUALIFYING_STAR = 0x360
Client -> server, the package structure
byte 0
 
 */

#ifndef _CCMD36F_H_
#define _CCMD36F_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD36F : public Packet
{
public:
	CCMD36F() 
	{
		
	}

	virtual ~CCMD36F() {}

	virtual bool	Write();	 

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_QUALIFYING_BUY;}
													
	virtual	int32		GetMessageSize( ) const { return 0;}

public :
};


class CCMD36FFactory: public MessageFactory
{
public :

	virtual ~CCMD36FFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_QUALIFYING_BUY;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif