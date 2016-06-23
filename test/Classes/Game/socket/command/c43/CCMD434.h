#ifndef _CCMD434_H_
#define _CCMD434_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD434 : public Packet
{
public:
	CCMD434()
	{
	}
	virtual ~CCMD434() {}


	virtual bool	Write() 
	{
		return true;
	}

public :
	virtual PacketID_t getPacketID() const { return CMSG_ORE_PROGRESS;}

	virtual	int32		GetMessageSize( ) const { return 0;}

};

/*
bool CCMD434::Write()
{

	return true;
}
*/


#endif