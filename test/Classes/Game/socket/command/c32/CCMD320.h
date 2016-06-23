/**
* CMSG_WORLD_IMPOSE	= 0x320,(800)
client->server
byte levy type£¬1£¬normal levy£»2£¬Qiang zheng
*/	

#ifndef _CCMD320_H_
#define _CCMD320_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD320 : public Packet
{
public:
	CCMD320() {}
	virtual ~CCMD320() {}


	virtual bool	Write();;
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_IMPOSE;}

	virtual	int32		GetMessageSize( ) const { return 0;}
	int8 a_type;
};

bool CCMD320::Write()
{
	writeByte( a_type );
	return true;
}


class CCMD320Factory: public MessageFactory
{
public :
	
	virtual ~CCMD320Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_IMPOSE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif