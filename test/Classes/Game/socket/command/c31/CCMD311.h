/**
* The client requests to enable the formation
* CMSG_WORLD_FORMATION_ENABLED = 0x311
* Client -> server-side package structure
* Uint16 formations ID.
 */ 


#ifndef _CCMD311_H_
#define _CCMD311_H_
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD311 : public Packet
{
public:
	CCMD311() {}
	virtual ~CCMD311() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_WORLD_FORMATION_ENABLED;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

	uint16 a_formationId;
	 

};


class CCMD311Factory: public MessageFactory
{
public :

	virtual ~CCMD311Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_FORMATION_ENABLED;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};






#endif