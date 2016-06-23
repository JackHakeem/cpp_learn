#ifndef _CCMD2B5_H_
#define _CCMD2B5_H_


/**пео╒
CMSG_WORLD_TRADE_PRICE	= 0X2B8;
*/

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2B5 : public Packet
{
public:
	CCMD2B5() 
	{
	}

	virtual ~CCMD2B5() {}

	virtual bool	Write()
	{
		writeInt(a);
		return true;
	}

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_TRADE_PRICE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	int a;
};


class CCMD2B5Factory: public MessageFactory
{
public :

	virtual ~CCMD2B5Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_TRADE_PRICE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif