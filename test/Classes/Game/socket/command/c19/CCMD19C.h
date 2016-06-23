#ifndef _CCMD19C_H_
#define _CCMD19C_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
Player requests crystal required for the upgrade CD time
CMSG_WORLD_REQ_UPGRADE_TIME = 0x19C (412)
Client -> server, the package structure
Byte type of request, 1: passive skills; 2: formation; 3: Crystal
Short skills (formation / crystal) ID
 */

class CCMD19C : public Packet
{
public:
	CCMD19C() {}
	virtual ~CCMD19C() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_WORLD_REQ_UPGRADE_TIME;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

	uint8 a_type ;
	uint16 b_id;


};


class CCMD19CFactory: public MessageFactory
{
public :

	virtual ~CCMD19CFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_REQ_UPGRADE_TIME;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif