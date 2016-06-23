/**
WMSG_WORLD_DAILY_TASK_ACCEPT
uint8 taskId,
uint8 success  (1 yes, 0 no)
 */

#ifndef _SCMD425_H_
#define _SCMD425_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD425 : public Packet
{
public:

	SCMD425()
	{
		a_taskId = 0;
		b_result = 0;
	}

	virtual ~SCMD425() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_DAILY_TASK_SUBMIT;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_taskId;
	int8 b_result;
};


class SCMD425Factory: public MessageFactory
{
public :
	
	virtual ~SCMD425Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD425();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_DAILY_TASK_SUBMIT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD425Handler 
{
public:
	static uint32 Execute(SCMD425* pPacket) ;
};

#endif