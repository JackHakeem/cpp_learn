#ifndef _CCMD437_H_
#define _CCMD437_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD437 : public Packet
{
public:
	CCMD437()
	{
		a_oreID = 0;
	}
	virtual ~CCMD437() {}


	virtual bool	Write() 
	{
		writeByte(a_oreID);
		return true;
	}

public :
	virtual PacketID_t getPacketID() const { return CMSG_ORE_PLANT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint8 a_oreID;
};

/*
bool CCMD437::Write()
{

	return true;
}
*/


#endif