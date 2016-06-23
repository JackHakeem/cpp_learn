/**
* The client request has to learn the formation and passive skills
* CMSG_WORLD_FORMATION_PASSIVESKILL = 0x317 (790)
* Client -> server-side package structure
* Uint8 request the content of 1 formation, 2 all, 3 passive skills
 */

#ifndef _CCMD311_H_
#define _CCMD311_H_
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD317 : public Packet
{
public:
	CCMD317() {}
	virtual ~CCMD317() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_WORLD_FORMATION_PASSIVESKILL;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

	uint8 a_type;


};


class CCMD317Factory: public MessageFactory
{
public :

	virtual ~CCMD317Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_FORMATION_PASSIVESKILL;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};






#endif