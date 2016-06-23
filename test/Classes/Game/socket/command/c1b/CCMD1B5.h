

#ifndef _CCMD1B5_H_
#define _CCMD1B5_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD1B5 : public Packet
{
public:
	CCMD1B5() {}
	virtual ~CCMD1B5() {}


	virtual bool	Write() { return true; };
public :
	virtual PacketID_t getPacketID() const { return CMSG_COMMU_GUILD_DISSOLVE;}

	virtual	int32		GetMessageSize( ) const { return 0;}
};


class CCMD1B5Factory: public MessageFactory
{
public :
	
	virtual ~CCMD1B5Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_GUILD_DISSOLVE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif