/**
CMSG_WORLD_INCREASE_PRICE = 0x294 
client->server
 */

#ifndef _CCMD294_H_
#define _CCMD294_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD294 : public Packet
{
public:
	CCMD294() {a_type = 0;}
	virtual ~CCMD294() {}


	virtual bool	Write();// { return true; }
public :
	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_INCREASE_PRICE;}	
	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	int32 a_type;
};


class CCMD294Factory: public MessageFactory
{
public :
	
	virtual ~CCMD294Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_INCREASE_PRICE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif 