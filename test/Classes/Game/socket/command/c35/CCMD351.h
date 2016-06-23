/**
* Request to the role of training information
* CMSG_WORLD_TRAIN_INFO = Ox351
* Client -> server-side package structure
* Empty
 */ 

#ifndef _CCMD351_H_
#define _CCMD351_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD351 : public Packet
{
public:
	CCMD351() {}
	virtual ~CCMD351() {}


	virtual bool	Write() { return true; };
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_TRAIN_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}
};


class CCMD351Factory: public MessageFactory
{
public :
	
	virtual ~CCMD351Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_TRAIN_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif