#ifndef _SCMD155_H_
#define _SCMD155_H_

#include "socket/network/Packet.h"
#include "socket/message/MessageFactory.h"
#include "socket/message/SocketCMDConst.h"
/**
* The task to return the package
* WMSG_WORLD_ACCEPT_TASK = 0x155 (341),
* Server -> client package structure
* Short: Task ID
* Byte: success (a success)
 */

class SCMD155 : public Packet
{

public:
	SCMD155(){}
	~SCMD155(){}

	int16 _id;
	int8 _succ;

	virtual int32 Execute();

	virtual bool Read();

	virtual PacketID_t getPacketID()const { return WMSG_WORLD_ACCEPT_TASK;}
};

class SCMD155Factory : public MessageFactory
{
	virtual Packet* CreateMessage() {return new SCMD155();}

	virtual PacketID_t GetPacketID()const {return WMSG_WORLD_ACCEPT_TASK;}

	virtual uint32 GetMessageMaxSize()const {return 0;}

};


class SCMD155Handler 
{
public:
	static uint32 Execute(SCMD155 *pPacket) ;
};

#endif