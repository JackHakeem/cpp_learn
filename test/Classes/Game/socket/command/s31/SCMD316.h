/**
* The client requests a passive skill to upgrade the return package
* WMSG_WORLD_PASSIVESKILL_UPGRADE = 0x316
* Server -> client package structure
* Uint8 whether the operation was successful
* Uint16 passive skill ID
The uint8 passive skill levels
 */ 

#ifndef _SCMD316_H_
#define _SCMD316_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD316 : public Packet
{
public:
	SCMD316()
	{
		a_isOk = 0;
		b_passiveId = 0;
		c_passiveLel = 0;
	}

	virtual ~SCMD316() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_PASSIVESKILL_UPGRADE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint8 a_isOk ;
	uint16 b_passiveId ;
	uint8 c_passiveLel ;

};


class SCMD316Factory: public MessageFactory
{
public :

	virtual ~SCMD316Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD316();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_PASSIVESKILL_UPGRADE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD316Handler 
{
public:
	static uint32 Execute(SCMD316* pPacket) ;
};

#endif 