#ifndef _CCMD422_H_
#define _CCMD422_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD422 : public Packet
{
public:
	CCMD422(int taskId, int taskType)
	{
		a_taskId = taskId;
		b_taskType = taskType;
	}
	virtual ~CCMD422() {}


	virtual bool	Write()
	{
		writeByte(a_taskId);
		writeByte(b_taskType);
		return true;
	}

public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_DAILY_TASK_ACCEPT;}

	virtual	int32		GetMessageSize( ) const { return 0;}
	
	uint8 a_taskId;
	uint8 b_taskType;
};

/*
bool CCMD422::Write()
{
	writeByte(a_taskId);
	writeByte(b_taskType);
	return true;
}
*/

#endif