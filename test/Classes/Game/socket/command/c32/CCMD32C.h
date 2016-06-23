/**
* CMSG_WORLD_GET_IMPOSE_INFO = Ox322
* Client -> server-side package structure
* Empty
 */ 

#ifndef _CCMD32C_H_
#define _CCMD32C_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD32C : public Packet
{
public:
	CCMD32C() {}
	virtual ~CCMD32C() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_TEAM_QUIT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

	int8  a_reason;
};


class CCMD32CFactory: public MessageFactory
{
public :
	
	virtual ~CCMD32CFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_TEAM_QUIT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif