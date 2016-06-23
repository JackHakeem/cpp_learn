#ifndef _CCMD1D9_H_
#define _CCMD1D9_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
Player requests crystal required for the upgrade CD time
CMSG_WORLD_REQ_UPGRADE_TIME = 0x1D9 (412)
Client -> server, the package structure
Byte type of request, 1: passive skills; 2: formation; 3: Crystal
Short skills (formation / crystal) ID
 */

class CCMD1D9 : public Packet
{
public:
	CCMD1D9() {}
	virtual ~CCMD1D9() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_WORLD_USE_ITEM;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

	int16 a_sitNum ;
};


class CCMD1D9Factory: public MessageFactory
{
public :

	virtual ~CCMD1D9Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_USE_ITEM;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif