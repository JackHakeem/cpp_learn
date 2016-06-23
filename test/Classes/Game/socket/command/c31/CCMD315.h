/**
* The client requests to upgrade passive skill
* CMSG_WORLD_PASSIVESKILL_UPGRADE = 0x315
* Client -> server-side package structure
* Uint16 passive skill ID.
 */ 


#ifndef _CCMD315_H_
#define _CCMD315_H_
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD315 : public Packet
{
public:
	CCMD315() {a_passiveId = 0;}
	virtual ~CCMD315() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_WORLD_PASSIVESKILL_UPGRADE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

	uint16 a_passiveId;
	 

};


class CCMD315Factory: public MessageFactory
{
public :

	virtual ~CCMD315Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_PASSIVESKILL_UPGRADE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};






#endif