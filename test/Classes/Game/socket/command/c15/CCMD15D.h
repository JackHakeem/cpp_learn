#ifndef _CCMD15D_H_
#define _CCMD15D_H_
#include "socket/network/Packet.h"
#include "socket/message/SocketCMDConst.h"
/**
* Submitted by the client to refresh task
* CMSG_WORLD_REFRESH_TASK = 0x15D (349),
* Client -> server-side package structure
* Byte: type of task
* (2.0)Byte: use tools? 0 : no, 1 : yes
 */
class CCMD15D : public Packet
{
public:
	CCMD15D(){}
	~CCMD15D(){}

	virtual bool Write();

	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_REFRESH_TASK;}

	virtual	int32 GetMessageSize( ) const { return 0;}

	int8 _type;
	int8 _prop;
};
#endif