/**
 */

#ifndef _SCMD433_H_
#define _SCMD433_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD433 : public Packet
{
public:

	SCMD433()
	{
		a_flag = 0;
	}

	virtual ~SCMD433() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_ORE_RESPONSE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint32 a_flag;
};


class SCMD433Factory: public MessageFactory
{
public :
	
	virtual ~SCMD433Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD433();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_ORE_RESPONSE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD433Handler 
{
public:
	static uint32 Execute(SCMD433* pPacket) ;
};

#endif