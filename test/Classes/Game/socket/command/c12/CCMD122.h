/**
* The client requests a mercenary basis of information
CMSG_WORLD_PROCESS = 0x122 (290)
Client -> server, the package structure
byte 0
 
 */

#ifndef _CCMD122_H_
#define _CCMD122_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD122 : public Packet
{
public:
	CCMD122()
	{
		a_byte = 0;
	}

	virtual ~CCMD122() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_WORLD_PROCESS;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	 int8 a_byte;

};


class CCMD122Factory: public MessageFactory
{
public :

	virtual ~CCMD122Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_PROCESS;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif