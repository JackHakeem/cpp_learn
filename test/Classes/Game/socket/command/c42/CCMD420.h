#ifndef _CCMD420_H_
#define _CCMD420_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD420 : public Packet
{
public:
	CCMD420()
	{
	}
	virtual ~CCMD420() {}


	virtual bool	Write() 
	{
		return true;
	}

public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_DAILY_TASK_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

};

/*
bool CCMD420::Write()
{

	return true;
}
*/


#endif