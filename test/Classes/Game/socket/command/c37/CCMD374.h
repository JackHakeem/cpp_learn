/**
* client requests battle winning streak info
CMSG_WORLD_DUNGEON_BUY_ENTER_TIMES = 0x374
Client -> server, the package structure
byte 0
 
 */

#ifndef _CCMD374_H_
#define _CCMD374_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD374 : public Packet
{
public:
	CCMD374() 
	{
	}

	virtual ~CCMD374() {}

	virtual bool	Write();	 

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_DUNGEON_BUY_ENTER_TIMES;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

};


class CCMD374Factory: public MessageFactory
{
public :

	virtual ~CCMD374Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_DUNGEON_BUY_ENTER_TIMES;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif