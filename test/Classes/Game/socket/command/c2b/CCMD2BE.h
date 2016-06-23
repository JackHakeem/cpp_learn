#ifndef _CCMD2BE_H_
#define _CCMD2BE_H_


/**пео╒
CMSG_WORLD_TRADE_INFO	= 0X2BE;
*/

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2BE : public Packet
{
public:
	CCMD2BE() 
	{
		a_id = 0;
	}

	virtual ~CCMD2BE() {}

	virtual bool	Write()
	{
		writeInt(a_id);

		return true;
	}

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_TRADE_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	int a_id;
};


class CCMD2BEFactory: public MessageFactory
{
public :

	virtual ~CCMD2BEFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_TRADE_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif