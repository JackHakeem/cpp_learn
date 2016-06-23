#ifndef _CCMD159_H_
#define _CCMD159_H_
#include "socket/network/Packet.h"
#include "socket/message/SocketCMDConst.h"

/**
* Submitted by the client task
* CMSG_WORLD_SUBMIT_TASK = 0x159 (345),
* Client -> server-side package structure
* Byte: type of task
* Short: Task ID
 */
class CCMD159 : public Packet
{

public:
	CCMD159(){}
	~CCMD159(){}

	virtual bool Write();

	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_SUBMIT_TASK;}

	virtual	int32 GetMessageSize( ) const { return 0;}
	
	int8 _type;
	int16 _id;
};

#endif