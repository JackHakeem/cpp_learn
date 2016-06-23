#ifndef _CCMD15B_H_
#define _CCMD15B_H_
#include "socket/network/Packet.h"
#include "socket/message/SocketCMDConst.h"

/**
* Submitted by the client to abandon the mission
* CMSG_WORLD_GIVE_UP_TASK = 0x15B (347),
* Client -> server-side package structure
* Byte: type of task
* Short: Task ID
 */
class CCMD15B : public Packet
{

public:
	CCMD15B(){}
	~CCMD15B(){}

	virtual bool Write();

	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_GIVE_UP_TASK;}

	virtual	int32 GetMessageSize( ) const { return 0;}

	int8 _type;
	int16 _id;
};

#endif