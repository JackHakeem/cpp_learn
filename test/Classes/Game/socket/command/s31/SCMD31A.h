/**
* to the client push new passive information
* WMSG_WORLD_PASSIVESKILL_ADD = 0 x31A
* the server-> the client, package structure
* uint16 passive skill ID
* uint8 passive skill level
 */ 

#ifndef _SCMD31A_H_
#define _SCMD31A_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD31A : public Packet
{
public:
	SCMD31A()
	{
		a_passiveId = 0;
		b_passiveLel = 0;
	}
	virtual ~SCMD31A() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_PASSIVESKILL_ADD;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint16 a_passiveId ;
	uint8 b_passiveLel ;

   
};


class SCMD31AFactory: public MessageFactory
{
public :

	virtual ~SCMD31AFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD31A();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_PASSIVESKILL_ADD;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD31AHandler 
{
public:
	static uint32 Execute(SCMD31A* pPacket) ;
};

#endif