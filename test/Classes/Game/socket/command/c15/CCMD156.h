#ifndef _CCMD156_H_
#define _CCMD156_H_
#include "socket/network/Packet.h"
#include "socket/message/SocketCMDConst.h"
/**
 * Submitted by the client directly to complete the task
 * CMSG_WORLD_COMPLETE_TASK = 0x156 (342),
 * Client -> server-side package structure
 * Byte: type of task
 * Short: Task ID
 */
class CCMD156 : public Packet
{

public:
	CCMD156(){}
	~CCMD156(){}

	virtual bool Write();

	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_COMPLETE_TASK;}

	virtual	int32 GetMessageSize( ) const { return 0;}

	int8 _type;
	int16 _id;
};

#endif