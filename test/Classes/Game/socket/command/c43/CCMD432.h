#ifndef _CCMD432_H_
#define _CCMD432_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD432 : public Packet
{
public:
	CCMD432()
	{
	}
	virtual ~CCMD432() {}


	virtual bool	Write() 
	{
		return true;
	}

public :
	virtual PacketID_t getPacketID() const { return CMSG_ORE_OPEN_APPLY;}

	virtual	int32		GetMessageSize( ) const { return 0;}

};

/*
bool CCMD432::Write()
{

	return true;
}
*/


#endif