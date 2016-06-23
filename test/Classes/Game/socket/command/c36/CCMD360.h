/**
* client requests battle winning streak info
CMSG_WORLD_PVP_QUALIFYING_STAR = 0x360
Client -> server, the package structure
byte 0
 
 */

#ifndef _CCMD360_H_
#define _CCMD360_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD360 : public Packet
{
public:
	CCMD360() 
	{
		a_byte = 0;
	}

	virtual ~CCMD360() {}

	virtual bool	Write();	 

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_QUALIFYING_ENTER;}
													
	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	 int8 a_byte;

};


class CCMD360Factory: public MessageFactory
{
public :

	virtual ~CCMD360Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_QUALIFYING_ENTER;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif