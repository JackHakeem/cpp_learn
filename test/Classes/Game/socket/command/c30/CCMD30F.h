/**
* The client requests a replacement mercenary's position in a formation
* CMSG_WORLD_MERCENARY_ALTER_SITE = 0x30F
* Client -> server-side package structure
* Uint16 formations ID.
* Uint32, mercenary unique ID
* Uint8 mercenary in the formation of the original location
* Uint8 mercenaries want to change the location to
 */

#ifndef _CCMD30F_H_
#define _CCMD30F_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD30F : public Packet
{
public:
	CCMD30F() {}
	virtual ~CCMD30F() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_WORLD_MERCENARY_ALTER_SITE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	 uint16 a_formationId ;
	 uint32 b_mercId ;
	 uint8 c_oldPos  ;
	 uint8 d_newPos ;

};


class CCMD30FFactory: public MessageFactory
{
public :

	virtual ~CCMD30FFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_MERCENARY_ALTER_SITE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif