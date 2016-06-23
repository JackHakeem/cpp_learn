/**
* Request by leaps and bounds
* CMSG_WORLD_TRAIN_SPEED_UP_REQUEST = 0x35B
* Client -> server-side package structure
* Int32: Role ID
Int8: suddenly fly type (0: ordinary suddenly fly one: gold coins suddenly fly (vip10 visible))

 */
#ifndef _CCMD35B_H_
#define _CCMD35B_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD35B : public Packet
{
public:
	CCMD35B() {}
	virtual ~CCMD35B() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_TRAIN_SPEED_UP_REQUEST;}

	virtual	int32		GetMessageSize( ) const { return 0;}

	int32 a_playerId;
	int8 b_type;
};


class CCMD35BFactory: public MessageFactory
{
public :
	
	virtual ~CCMD35BFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_TRAIN_SPEED_UP_REQUEST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif