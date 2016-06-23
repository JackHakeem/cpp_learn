#ifndef _CCMD21D_H_
#define _CCMD21D_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
Player requests to buy energy
CMSG_WORLD_BUY_VIGOUR = 0x21D
Client -> server, the package structure
 */

class CCMD21D : public Packet
{
public:
	CCMD21D() {}
	virtual ~CCMD21D() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_WORLD_BUY_VIGOUR;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

};


class CCMD21DFactory: public MessageFactory
{
public :

	virtual ~CCMD21DFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_BUY_VIGOUR;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif