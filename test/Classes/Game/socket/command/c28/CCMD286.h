/**
 * 	client opens hero award
	CMSG_WORLD_HERO_GET_AWARD = 0x286 
	client->server pack
 */

#ifndef _CCMD286_H_
#define _CCMD286_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD286 : public Packet
{
public:
	CCMD286() {}
	virtual ~CCMD286() {}

	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_HERO_GET_AWARD;}
	virtual	int32		GetMessageSize( ) const { return 0;}
};

class CCMD286Factory: public MessageFactory
{
public :
	virtual ~CCMD286Factory ()  {}
	virtual Packet*		CreateMessage () {return 0;};
	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_HERO_GET_AWARD;}
	virtual uint32		GetMessageMaxSize ()const  {return 0;}
};

#endif 