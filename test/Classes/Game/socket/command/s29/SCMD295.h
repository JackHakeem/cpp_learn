/**
WMSG_WORLD_INCREASE_PRICE = 0x295
byte
*/

#ifndef _SCMD295_H_
#define _SCMD295_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD295 : public Packet
{
public:
	SCMD295() 
	{
		a_type = 0;
		b_price = 0;
	}
	virtual ~SCMD295() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_INCREASE_PRICE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint8 a_type;
	uint32 b_price;
};


class SCMD295Factory: public MessageFactory
{
public :

	virtual ~SCMD295Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD295();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_INCREASE_PRICE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD295Handler 
{
public:
	static uint32 Execute(SCMD295* pPacket) ;
};

#endif 