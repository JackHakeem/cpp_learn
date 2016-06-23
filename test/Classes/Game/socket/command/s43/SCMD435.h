/**
 */

#ifndef _SCMD435_H_
#define _SCMD435_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD435 : public Packet
{
public:

	SCMD435()
	{
		a_plantStates = 0;
	}

	virtual ~SCMD435() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_ORE_PROGRESS;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint32 a_plantStates;
};


class SCMD435Factory: public MessageFactory
{
public :
	
	virtual ~SCMD435Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD435();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_ORE_PROGRESS;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD435Handler 
{
public:
	static uint32 Execute(SCMD435* pPacket) ;
};

#endif