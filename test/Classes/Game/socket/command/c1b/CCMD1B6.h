

#ifndef _CCMD1B6_H_
#define _CCMD1B6_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD1B6 : public Packet
{
public:
	CCMD1B6() {}
	virtual ~CCMD1B6() {}


	virtual bool	Write() { return true; };
public :
	virtual PacketID_t getPacketID() const { return CMSG_COMMU_GUILD_DISSOLVE_CANCEL;}

	virtual	int32		GetMessageSize( ) const { return 0;}
};


class CCMD1B6Factory: public MessageFactory
{
public :

	virtual ~CCMD1B6Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_GUILD_DISSOLVE_CANCEL;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif