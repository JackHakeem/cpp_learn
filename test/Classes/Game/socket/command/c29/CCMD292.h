/**
CMSG_WORLD_NOTIFY_REQ = 0x292
client->server
 */

#ifndef _CCMD292_H_
#define _CCMD292_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD292 : public Packet
{
public:
	CCMD292() {}
	virtual ~CCMD292() {}


	virtual bool	Write();// { return true; }
public :
	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_NOTIFY_REQ;}	
	virtual	int32		GetMessageSize( ) const { return 0;}

public :
};


class CCMD292Factory: public MessageFactory
{
public :
	
	virtual ~CCMD292Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_NOTIFY_REQ;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif 