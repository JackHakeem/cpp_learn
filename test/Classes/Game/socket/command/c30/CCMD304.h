/**
* Solution of mercenaries
* CMSG_WORLD_MERCENARY_DISMISS = 0x304
* Client -> server-side package structure
* Uint32, mercenary unique ID
 */ 

#ifndef _CCMD304_H_
#define _CCMD304_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD304 : public Packet
{
public:
	CCMD304() 
	{
		a_mercenaryId = 0;
	}

	virtual ~CCMD304() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_WORLD_MERCENARY_DISMISS;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	 int32 a_mercenaryId;

};


class CCMD304Factory: public MessageFactory
{
public :

	virtual ~CCMD304Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_MERCENARY_DISMISS;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif