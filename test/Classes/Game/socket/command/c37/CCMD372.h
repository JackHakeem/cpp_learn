/**
* client requests battle winning streak info
CMSG_WORLD_DUNGEON_ENTER_TIMES = 0x372
Client -> server, the package structure
byte 0
 
 */

#ifndef _CCMD372_H_
#define _CCMD372_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD372 : public Packet
{
public:
	CCMD372() 
	{
	}

	virtual ~CCMD372() {}

	virtual bool	Write();	 

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_DUNGEON_ENTER_TIMES;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

};


class CCMD372Factory: public MessageFactory
{
public :

	virtual ~CCMD372Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_DUNGEON_ENTER_TIMES;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif