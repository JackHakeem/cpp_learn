#ifndef _CCMD428_H_
#define _CCMD428_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD428 : public Packet
{
public:
	CCMD428(uint8 type)
	{
		a_type = type;
	}
	virtual ~CCMD428() {}


	virtual bool	Write()
	{
		writeByte(a_type);
		return true;
	}
private:
	uint8 a_type;
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_DAILY_TASK_REFRESH;}

	virtual	int32		GetMessageSize( ) const { return 0;}

};

/*
bool CCMD428::Write()
{

	return true;
}
*/


#endif