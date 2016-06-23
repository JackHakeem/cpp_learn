/**
 */

#ifndef _SCMD42B_H_
#define _SCMD42B_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD42B : public Packet
{
public:

	SCMD42B()
	{
		a_result = 0;
	}

	virtual ~SCMD42B() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_DAILY_TASK_GIVEUP;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_result;
};


class SCMD42BFactory: public MessageFactory
{
public :
	
	virtual ~SCMD42BFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD42B();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_DAILY_TASK_GIVEUP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD42BHandler 
{
public:
	static uint32 Execute(SCMD42B* pPacket) ;
};

#endif