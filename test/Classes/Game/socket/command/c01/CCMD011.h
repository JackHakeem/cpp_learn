#ifndef _CCMD011_H_
#define _CCMD011_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD011 : public Packet
{
public:
	CCMD011() {}
	virtual ~CCMD011() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_WORLD_HARTBEAT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

	//int16 a_sitNum ;
};


class CCMD011Factory: public MessageFactory
{
public :

	virtual ~CCMD011Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_HARTBEAT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif