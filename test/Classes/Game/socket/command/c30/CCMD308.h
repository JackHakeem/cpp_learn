/**
* The client requests a mercenary equipment information
CMSG_WORLD_MERCENARY_EQUIP_INFO = 0x308 (776)
Client -> server, the package structure
byte 0
 
 */

#ifndef _CCMD308_H_
#define _CCMD308_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD308 : public Packet
{
public:
	CCMD308() 
	{
		a_byte = 0;
	}

	virtual ~CCMD308() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_WORLD_MERCENARY_EQUIP_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	 int8 a_byte;

};


class CCMD308Factory: public MessageFactory
{
public :

	virtual ~CCMD308Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_MERCENARY_EQUIP_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif