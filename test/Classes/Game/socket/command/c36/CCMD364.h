/**
* client requests battle winning streak info
CMSG_WORLD_PVP_QUALIFYING_STAR = 0x360
Client -> server, the package structure
byte 0
 
 */

#ifndef _CCMD364_H_
#define _CCMD364_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD364 : public Packet
{
public:
	CCMD364() 
	{
		
	}

	virtual ~CCMD364() {}

	virtual bool	Write();	 

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_QUALIFYING_AWARD;}
													
	virtual	int32		GetMessageSize( ) const { return 0;}

public :
};


class CCMD364Factory: public MessageFactory
{
public :

	virtual ~CCMD364Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_QUALIFYING_AWARD;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif