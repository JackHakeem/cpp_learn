
#ifndef _CCMD31C_H_
#define _CCMD31C_H_
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD31C : public Packet
{
public:
	CCMD31C() {}
	virtual ~CCMD31C() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_WORLD_MERCENARY_FOSTER_SAVE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

	uint32 a_figureId;

};


class CCMD31CFactory: public MessageFactory
{
public :

	virtual ~CCMD31CFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_MERCENARY_FOSTER_SAVE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};






#endif