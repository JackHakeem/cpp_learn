/**
 * 	client requests hero rank info
	CMSG_WORLD_HERO_REQ = 0x284 
	client->server no pack
 */

#ifndef _CCMD284_H_
#define _CCMD284_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD284 : public Packet
{
public:
	CCMD284() {}
	virtual ~CCMD284() {}

	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_HERO_REQ;}
	virtual	int32		GetMessageSize( ) const { return 0;}
};

class CCMD284Factory: public MessageFactory
{
public :
	virtual ~CCMD284Factory ()  {}
	virtual Packet*		CreateMessage () {return 0;};
	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_HERO_REQ;}
	virtual uint32		GetMessageMaxSize ()const  {return 0;}
};

#endif 