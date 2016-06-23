/**
Received task information to the client push
* WMSG_WORLD_TASK_ACCEPT = 0x151 (337),
* Server -> client package structure
* Short: the number of tasks
*	Short: task id
*	Byte: type of task
*	Byte: Task status (completion)
*	Short: the number of task conditions
*		Int: Task Condition ID
*		Short: the task number of conditions to complete
 */
#ifndef _SCMD151_H_
#define _SCMD151_H_

#include "socket/network/Packet.h"
#include "socket/message/MessageFactory.h"
#include "socket/message/SocketCMDConst.h"

class SCMD151 : public Packet
{
public:
	SCMD151(){}
	virtual ~SCMD151(){}

	virtual int32 Execute();
	
	virtual bool Read();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_TASK_ACCEPT;}

	struct SCMD151Node1
	{
		int16 _id;
		int16 _nowCount;
	};

	struct SCMD151Node
	{
		int16 _id;
		int8 _type;
		int8 _finish;
		std::vector<SCMD151Node1> _taskTip;
	};

	std::list<SCMD151Node> _tasks;
};

class SCMD151Factory : public MessageFactory
{
public:
	SCMD151Factory(){}
	virtual ~SCMD151Factory(){}

	virtual Packet* CreateMessage() {return new SCMD151();}

	virtual PacketID_t GetPacketID() const {return WMSG_WORLD_TASK_ACCEPT;}

	virtual uint32 GetMessageMaxSize() const {return 0;}

};

class SCMD151Handler 
{
public:
	static uint32 Execute(SCMD151 *pPacket) ;
};

#endif