/**
* Request the role of training
* CMSG_WORLD_TRAIN_REQUEST = Ox359
* Client -> server-side package structure
* Int32: Role ID
* Int8: the type of training time
 */ 

#ifndef _CCMD359_H_
#define _CCMD359_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD359 : public Packet
{
public:
	CCMD359() {}
	virtual ~CCMD359() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_TRAIN_REQUEST;}

	virtual	int32		GetMessageSize( ) const { return 0;}

	int32 a_playerId;
	int8 b_type;
	int8 c_mode;
};


class CCMD351Factory: public MessageFactory
{
public :
	
	virtual ~CCMD351Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_TRAIN_REQUEST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif