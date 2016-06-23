#ifndef _CCMD15F_H_
#define _CCMD15F_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD15F : public Packet
{

public:

	CCMD15F(){}
	~CCMD15F(){}


	virtual bool Write();

	virtual PacketID_t getPacketID()const { return CMSG_WORLD_ALL_TASK_REQUEST;}
	
};
#endif