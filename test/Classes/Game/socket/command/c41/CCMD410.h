/**
* client requests battle winning streak info
CMSG_WORLD_PVP_QUALIFYING_STAR = 0x37D
Client -> server, the package structure
byte 0
 
 */

#ifndef _CCMD410_H_
#define _CCMD410_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD410 : public Packet
{
public:
	CCMD410() 
	{
		a_dunId = 0;
	}

	virtual ~CCMD410() {}

	virtual bool	Write();	 

	virtual PacketID_t getPacketID() const { return CMSG_DUNGEON_GUA;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	 int32 a_dunId;

};


class CCMD410Factory: public MessageFactory
{
public :

	virtual ~CCMD410Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_DUNGEON_GUA;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif