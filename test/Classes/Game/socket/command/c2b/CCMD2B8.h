#ifndef _CCMD2B8_H_
#define _CCMD2B8_H_


/**пео╒
CMSG_WORLD_TRADE_BEGIN	= 0X2B8;
*/

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2B8 : public Packet
{
public:
	CCMD2B8() 
	{
		a_mapId = 0;
		//b_buyGood = 0;
	}

	virtual ~CCMD2B8() {}

	virtual bool	Write()
	{
		writeInt(a_mapId);
		//writeInt(b_buyGood);
		return true;
	}

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_TRADE_BEGIN;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	int a_mapId;
	//int b_buyGood;
};


class CCMD2B8Factory: public MessageFactory
{
public :

	virtual ~CCMD2B8Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_TRADE_BEGIN;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif