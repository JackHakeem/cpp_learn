#ifndef _CCMD2BC_H_
#define _CCMD2BC_H_

/**пео╒
CMSG_WORLD_TRADE_BANK_ADD	= 0X2BC;
*/

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2BC : public Packet
{
public:
	CCMD2BC() 
	{
	}

	virtual ~CCMD2BC() {}

	virtual bool	Write()
	{
		writeInt(a);

		return true;
	}

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_TRADE_BANK_ADD;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	int a;
};


class CCMD2BCFactory: public MessageFactory
{
public :

	virtual ~CCMD2BCFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_TRADE_BANK_ADD;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif