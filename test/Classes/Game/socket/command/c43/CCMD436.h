#ifndef _CCMD436_H_
#define _CCMD436_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD436 : public Packet
{
public:
	CCMD436()
	{
		a_oreID = 0;
		b_refreshType;
	}
	virtual ~CCMD436() {}


	virtual bool	Write() 
	{
		writeByte(a_oreID);
		writeByte(b_refreshType);
		return true;
	}

public :
	virtual PacketID_t getPacketID() const { return CMSG_ORE_REFRESH_APPLY;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint8 a_oreID;
	uint8 b_refreshType;
};

/*
bool CCMD436::Write()
{

	return true;
}
*/


#endif