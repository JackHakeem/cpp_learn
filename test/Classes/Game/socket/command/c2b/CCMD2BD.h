#ifndef _CCMD2BD_H_
#define _CCMD2BD_H_


/**пео╒
CMSG_WORLD_TRADE_REFLASH	= 0X2Bd;
*/

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2BD : public Packet
{
public:
	CCMD2BD() 
	{
	}

	virtual ~CCMD2BD() {}

	virtual bool	Write()
	{
		return true;
	}

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_TRADE_REFLASH;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
};


class CCMD2BDFactory: public MessageFactory
{
public :

	virtual ~CCMD2BDFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_TRADE_REFLASH;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif