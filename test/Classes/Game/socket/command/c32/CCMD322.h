/**
* CMSG_WORLD_GET_IMPOSE_INFO = Ox322
* Client -> server-side package structure
* Empty
 */ 

#ifndef _CCMD322_H_
#define _CCMD322_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD322 : public Packet
{
public:
	CCMD322() {}
	virtual ~CCMD322() {}


	virtual bool	Write() { return true; };
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_GET_IMPOSE_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}
};


class CCMD322Factory: public MessageFactory
{
public :
	
	virtual ~CCMD322Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_GET_IMPOSE_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif