/**
*/
#ifndef _CCMD1E0_H_
#define _CCMD1E0_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD1E0 : public Packet
{
public:
	CCMD1E0() {}
	virtual ~CCMD1E0() {}


	virtual bool	Write() { return true; };
public :
	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_DELEGATE_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}
};

class CCMD1E0Factory: public MessageFactory
{
public :

	virtual ~CCMD1E0Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_DELEGATE_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};
#endif 