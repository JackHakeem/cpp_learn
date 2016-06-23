#ifndef _CCMD438_H_
#define _CCMD438_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD438 : public Packet
{
public:
	CCMD438()
	{
	}
	virtual ~CCMD438() {}


	virtual bool	Write() 
	{
		return true;
	}

public :
	virtual PacketID_t getPacketID() const { return CMSG_ORE_BUY_STONE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

};

/*
bool CCMD438::Write()
{

	return true;
}
*/


#endif