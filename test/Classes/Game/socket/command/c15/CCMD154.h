#ifndef _CCMD154_H_
#define _CCMD154_H_
#include "socket/network/Packet.h"
#include "socket/message/SocketCMDConst.h"
/**
* Submitted by the client to accept the task
* CMSG_WORLD_ACCEPT_TASK = 0x154 (340),
* Client -> server-side package structure
* Byte: type of task
* Short: Task ID
*/
class CCMD154 : public Packet
{
public:
	CCMD154(){}
	~CCMD154(){}

	virtual bool Write();

	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_ACCEPT_TASK;}

	virtual	int32 GetMessageSize( ) const { return 0;}


	int8 _type;
	int16 _id;
};

#endif