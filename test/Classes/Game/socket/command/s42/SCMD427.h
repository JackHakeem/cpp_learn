/**
WMSG_WORLD_DAILY_TASK_PROGRESS
uint8 taskId,
uint8 finishcount
uint8 count
 */

#ifndef _SCMD427_H_
#define _SCMD427_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD427 : public Packet
{
public:

	SCMD427()
	{
		a_taskId = 0;
		b_finishCount = 0;
		c_count = 0;
	}

	virtual ~SCMD427() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_DAILY_TASK_PROGRESS;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_taskId;
	int8 b_finishCount;
	int8 c_count;
};


class SCMD427Factory: public MessageFactory
{
public :
	
	virtual ~SCMD427Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD427();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_DAILY_TASK_PROGRESS;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD427Handler 
{
public:
	static uint32 Execute(SCMD427* pPacket) ;
};

#endif