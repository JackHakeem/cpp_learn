/**
* Where a change in training mode
* CMSG_WORLD_TRAIN_CHANGE_MODEL = Ox355
* Client -> server-side package structure
* Int32: Role ID
* Int8: training mode
 */ 
#ifndef __CCMD355_H
#define __CCMD355_H

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD355 : public Packet
{
public:
	CCMD355() {}
	virtual ~CCMD355() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_TRAIN_CHANGE_MODEL;}

	virtual	int32		GetMessageSize( ) const { return 0;}

	int32 a_playerId;
	int8 b_mode;
};


class CCMD355Factory: public MessageFactory
{
public :

	virtual ~CCMD355Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_TRAIN_CHANGE_MODEL;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif