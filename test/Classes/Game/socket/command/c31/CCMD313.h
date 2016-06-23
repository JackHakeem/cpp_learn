/**
* The client requests to UPGRADE the formation
* CMSG_WORLD_FORMATION_UPGRADE = 0x313
* Client -> server-side package structure
* Uint16 formations ID.
 */ 


#ifndef _CCMD313_H_
#define _CCMD313_H_
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD313 : public Packet
{
public:
	CCMD313() {}
	virtual ~CCMD313() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_WORLD_FORMATION_UPGRADE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

	uint16 a_formationId;
	 

};


class CCMD313Factory: public MessageFactory
{
public :

	virtual ~CCMD313Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_FORMATION_UPGRADE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};






#endif