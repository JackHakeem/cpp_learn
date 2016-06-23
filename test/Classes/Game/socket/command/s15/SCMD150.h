#ifndef _SCMD150_H_
#define _SCMD150_H_
#pragma once
#include "socket/network/Packet.h"
#include "socket/message/MessageFactory.h"
#include "socket/message/SocketCMDConst.h"
/**
* Push players to the client routine tasks to completion
* WMSG_WORLD_TASK_ALL = 0x150 (336)
* Server -> client package structure
* Short: the array size
* Int: combination of task status value of an int on behalf of the 32 tasks that completed the contrary is not completed
 */
class SCMD150 : public Packet
{
public:
	SCMD150(){}
	~SCMD150(){}

	virtual int32 Execute();
	
	virtual bool Read();

	virtual PacketID_t getPacketID()const { return WMSG_WORLD_TASK_ALL;}

	std::list<int> _taskProcess;
	
};


class SCMD150Factory : public MessageFactory
{
	virtual Packet* CreateMessage() {return new SCMD150();}

	virtual PacketID_t GetPacketID()const {return WMSG_WORLD_TASK_ALL;}

	virtual uint32 GetMessageMaxSize()const {return 0;}

};


class SCMD150Handler 
{
public:
	static uint32 Execute(SCMD150 *pPacket) ;
};

#endif