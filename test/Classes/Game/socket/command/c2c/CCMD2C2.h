#ifndef _CCMD2C2_H_
#define _CCMD2C2_H_

/*
public static const CMSG_WORLD_TRADE_ATTACK_REQ:uint	= 0X2c2;
*/

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2C2 : public Packet
{
public:
	CCMD2C2() 
	{
		a_trade = 0;
	}

	virtual ~CCMD2C2() {}

	virtual bool	Write()
	{
		writeInt(a_trade);
		return true;
	}

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_TRADE_ATTACK_REQ;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	int a_trade;
};


class CCMD2C2Factory: public MessageFactory
{
public :

	virtual ~CCMD2C2Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_TRADE_ATTACK_REQ;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif