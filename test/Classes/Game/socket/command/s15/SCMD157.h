#ifndef _SCMD157_H_
#define _SCMD157_H_

#include "socket/network/Packet.h"
#include "socket/message/MessageFactory.h"
#include "socket/message/SocketCMDConst.h"
/**
* To complete the task to return the package
* SMSG_WORLD_COMPLETE_TASK = 0x157 (343),
* Server -> client package structure
* Short: Task ID
* Byte: success (a success)
 */
class SCMD157 : public Packet
{

public:
	SCMD157(){}
	~SCMD157(){}

	int16 _id;
	int8 _succ;

	virtual int32 Execute();

	virtual bool Read();

	virtual PacketID_t getPacketID()const { return WMSG_WORLD_COMPLETE_TASK;}
};

class SCMD157Factory : public MessageFactory
{
	virtual Packet* CreateMessage() {return new SCMD157();}

	virtual PacketID_t GetPacketID()const {return WMSG_WORLD_COMPLETE_TASK;}

	virtual uint32 GetMessageMaxSize()const {return 0;}

};


class SCMD157Handler 
{
public:
	static uint32 Execute(SCMD157 *pPacket) ;
};

#endif