#ifndef _CCMD430_H_
#define _CCMD430_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD430 : public Packet
{
public:
	CCMD430()
	{
	}
	virtual ~CCMD430() {}


	virtual bool	Write() 
	{
		return true;
	}

public :
	virtual PacketID_t getPacketID() const { return CMSG_ORE_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

};

/*
bool CCMD430::Write()
{

	return true;
}
*/


#endif