#ifndef _CCMD424_H_
#define _CCMD424_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD424 : public Packet
{
public:
	CCMD424(int taskId, int taskType, int submitType)
	{
		a_taskId = taskId;
		b_taskType = taskType;
		c_submitType = submitType;
	}
	virtual ~CCMD424() {}


	virtual bool	Write()
	{
		writeByte(a_taskId);
		writeByte(b_taskType);
		writeByte(c_submitType);
		return true;
	}

public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_DAILY_TASK_SUBMIT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

	uint8 a_taskId;
	uint8 b_taskType;
	uint8 c_submitType;
};

/*
bool CCMD424::Write()
{
	writeByte(a_taskId);
	writeByte(b_taskType);
	return true;
}
*/


#endif