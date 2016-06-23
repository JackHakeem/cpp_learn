/**
* Request to purchase the training location
* CMSG_WORLD_TRAIN_BUY_PLACE = Ox353
* Client -> server-side package structure
* No
 */ 
#ifndef _CCMD353_H_
#define _CCMD353_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD353 : public Packet
{
public:
	CCMD353() {}
	virtual ~CCMD353() {}


	virtual bool	Write() { return true; };
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_TRAIN_BUY_PLACE;}

	virtual	int32		GetMessageSize( ) const { return 0;}
};


class CCMD353Factory: public MessageFactory
{
public :
	
	virtual ~CCMD353Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_TRAIN_BUY_PLACE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif