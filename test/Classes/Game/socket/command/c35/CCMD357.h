/**
* Request to the end of training
* CMSG_WORLD_TRAIN_END = Ox357
* Client -> server-side package structure
* Int32: Role ID
 */ 
#ifndef _CCMD357_H_
#define _CCMD357_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD357 : public Packet
{
public:
	CCMD357() {}
	virtual ~CCMD357() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_TRAIN_END;}

	virtual	int32		GetMessageSize( ) const { return 0;}

	int32 a_playerId;
};


class CCMD357Factory: public MessageFactory
{
public :
	
	virtual ~CCMD357Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_TRAIN_END;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif