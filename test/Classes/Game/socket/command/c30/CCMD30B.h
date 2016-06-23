/**
* The client requests reborn
* CMSG_WORLD_MERCENARY_RERSIE = 0x30B
* Client -> server-side package structure
* int32, mercenary unique ID
 */

#ifndef _CCMD30B_H_
#define _CCMD30B_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD30B : public Packet
{
public:
	CCMD30B() 
	{
		a_figureId = 0;
	}

	virtual ~CCMD30B() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_WORLD_MERCENARY_RERSIE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	 int32 a_figureId;
};


class CCMD30BFactory: public MessageFactory
{
public :

	virtual ~CCMD30BFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_MERCENARY_RERSIE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif