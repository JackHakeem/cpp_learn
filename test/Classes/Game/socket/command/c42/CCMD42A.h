#ifndef _CCMD42A_H_
#define _CCMD42A_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD42A : public Packet
{
public:
	CCMD42A(int taskId, int taskType)
	{
		a_taskId = taskId;
		b_taskType = taskType;
	}
	virtual ~CCMD42A() {}


	virtual bool	Write()
	{
		writeByte(a_taskId);
		writeByte(b_taskType);
		return true;
	}

public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_DAILY_TASK_GIVEUP;}

	virtual	int32		GetMessageSize( ) const { return 0;}

	uint8 a_taskId;
	uint8 b_taskType;
};

/*
bool CCMD42A::Write()
{
	writeByte(a_taskId);
	writeByte(b_taskType);
	return true;
}
*/


#endif