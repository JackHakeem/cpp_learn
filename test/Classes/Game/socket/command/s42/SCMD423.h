/**
WMSG_WORLD_DAILY_TASK_ACCEPT
uint8 taskId,
uint8 success  (1 yes, 0 no)
 */

#ifndef _SCMD423_H_
#define _SCMD423_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD423 : public Packet
{
public:

	SCMD423()
	{
		a_taskId = 0;
		b_result = 0;
	}

	virtual ~SCMD423() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_DAILY_TASK_ACCEPT;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_taskId;
	int8 b_result;
};


class SCMD423Factory: public MessageFactory
{
public :
	
	virtual ~SCMD423Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD423();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_DAILY_TASK_ACCEPT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD423Handler 
{
public:
	static uint32 Execute(SCMD423* pPacket) ;
};

#endif