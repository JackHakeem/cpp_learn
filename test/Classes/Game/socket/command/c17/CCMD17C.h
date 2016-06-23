/**
*/
#ifndef _CCMD17C_H_
#define _CCMD17C_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD17C : public Packet
{
public:
	CCMD17C() {}
	virtual ~CCMD17C() {}


	virtual bool	Write() { return true; };
public :
	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_SYS_EQUIPSTREN_PROB;}

	virtual	int32		GetMessageSize( ) const { return 0;}
};

class CCMD17CFactory: public MessageFactory
{
public :

	virtual ~CCMD17CFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_SYS_EQUIPSTREN_PROB;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};
#endif 