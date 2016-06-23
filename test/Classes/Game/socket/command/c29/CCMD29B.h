/**
CMSG_WORLD_TRADE_BUY_TOKEN = 0x29b
clent->server
 */

#ifndef _CCMD29B_H_
#define _CCMD29B_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD29B : public Packet
{
public:
	CCMD29B() {}
	virtual ~CCMD29B() {}


	virtual bool	Write() { return true; }
public :
	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_TRADE_BUY_TOKEN;}	
	virtual	int32		GetMessageSize( ) const { return 0;}
};


class CCMD29BFactory: public MessageFactory
{
public :
	
	virtual ~CCMD29BFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_TRADE_BUY_TOKEN;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif 