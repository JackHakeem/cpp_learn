/**
 */

#ifndef _SCMD429_H_
#define _SCMD429_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD429 : public Packet
{
public:

	SCMD429()
	{
		a_result = 0;
	}

	virtual ~SCMD429() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_DAILY_TASK_REFRESH;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_result;
};


class SCMD429Factory: public MessageFactory
{
public :
	
	virtual ~SCMD429Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD429();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_DAILY_TASK_REFRESH;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD429Handler 
{
public:
	static uint32 Execute(SCMD429* pPacket) ;
};

#endif