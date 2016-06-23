#ifndef _CCMD2B0_H_
#define _CCMD2B0_H_


/**пео╒
CMSG_WORLD_TRADE_INIT	= 0X2B8;
*/

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2B0 : public Packet
{
public:
	CCMD2B0() 
	{
	}

	virtual ~CCMD2B0() {}

	virtual bool	Write()
	{
		return true;
	}

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_TRADE_INIT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
};


class CCMD2B0Factory: public MessageFactory
{
public :

	virtual ~CCMD2B0Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_TRADE_INIT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif