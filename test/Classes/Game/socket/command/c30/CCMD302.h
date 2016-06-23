/**
* Recruitment of mercenaries
* CMSG_WORLD_MERCENARY_RECRUIT = 0x302
* Client -> server-side package structure
* Uint16 mercenaries ID.
 */ 

#ifndef _CCMD302_H_
#define _CCMD302_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD302 : public Packet
{
public:
	CCMD302() 
	{
		a_prototypeId = 0;
	}

	virtual ~CCMD302() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_WORLD_MERCENARY_RECRUIT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	 int16 a_prototypeId;

};


class CCMD302Factory: public MessageFactory
{
public :

	virtual ~CCMD302Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_MERCENARY_RECRUIT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif