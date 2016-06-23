#ifndef _SCMD38C_H_
#define _SCMD38C_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD38C : public Packet
{
public:
	SCMD38C()
	{

	}

	virtual ~SCMD38C() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_QUALIFYING_BUY_RES;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_buy;
};


class SCMD38CFactory: public MessageFactory
{
public :

	virtual ~SCMD38CFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD38C();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_QUALIFYING_BUY_RES;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD38CHandler 
{
public:
	static uint32 Execute(SCMD38C* pPacket) ;
};

#endif