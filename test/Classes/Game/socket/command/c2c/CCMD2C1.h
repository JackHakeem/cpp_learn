#ifndef _CCMD2C1_H_
#define _CCMD2C1_H_

/*
public static const CMSG_WORLD_TRADE_BUY:uint	= 0X2c1;
*/

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2C1 : public Packet
{
public:
	CCMD2C1() 
	{
		a_buy = 0;
	}

	virtual ~CCMD2C1() {}

	virtual bool	Write()
	{
		writeInt(a_buy);
		return true;
	}

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_TRADE_BUY;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	int a_buy;
};


class CCMD2C1Factory: public MessageFactory
{
public :

	virtual ~CCMD2C1Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_TRADE_BUY;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif