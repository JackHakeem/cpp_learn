#ifndef _CCMD2BA_H_
#define _CCMD2BA_H_


/**пео╒
CMSG_WORLD_TRADE_END	= 0X2BA;
*/

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2BA : public Packet
{
public:
	CCMD2BA() 
	{
	}

	virtual ~CCMD2BA() {}

	virtual bool	Write()
	{
		writeInt(a_mapId);

		return true;
	}

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_TRADE_END;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	int a_mapId;
};


class CCMD2BAFactory: public MessageFactory
{
public :

	virtual ~CCMD2BAFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_TRADE_END;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif