/**
* The client requests a mercenary replacement skills
* CMSG_WORLD_MERCENARY_SKILL_ENABLED = 0x30D
* Client -> server-side package structure
* Uint32, mercenary unique ID
* The uint8 skill type
* The uint16 skill ID
 */

#ifndef _CCMD30D_H_
#define _CCMD30D_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD30D : public Packet
{
public:
	CCMD30D() 
	{
		a_merId = 0;
		b_skillRank = 0;
		c_skillId = 0;
	}

	virtual ~CCMD30D() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_WORLD_MERCENARY_SKILL_ENABLED;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	 int32 a_merId;
	 int8 b_skillRank;
	 int16 c_skillId;
};


class CCMD30DFactory: public MessageFactory
{
public :

	virtual ~CCMD30DFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_MERCENARY_SKILL_ENABLED;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif