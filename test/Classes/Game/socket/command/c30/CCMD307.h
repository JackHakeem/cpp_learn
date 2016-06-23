/**
* The client requests a mercenary basis of information
CMSG_WORLD_MERCENARY_BASE_INFO = 0x307 (775)
Client -> server, the package structure
byte 0
 */

#ifndef _CCMD307_H_
#define _CCMD307_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD307 : public Packet
{
public:
	CCMD307() 
	{
		a_byte = 0;
	}

	virtual ~CCMD307() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_WORLD_MERCENARY_BASE_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	 int8 a_byte;

};


class CCMD307Factory: public MessageFactory
{
public :

	virtual ~CCMD307Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_MERCENARY_BASE_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif