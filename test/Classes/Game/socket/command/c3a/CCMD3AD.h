#ifndef _CCMD3AD_H_
#define _CCMD3AD_H_

/**¿Í»§¶Ë¹ÄÎè
public static const CMSG_WORLD_TOWER_INSPIRE:uint	= 0X3AD;
*/

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD3AD : public Packet
{
public:
	CCMD3AD() 
	{
		a = 0;
	}

	virtual ~CCMD3AD() {}

	virtual bool	Write()
	{
		writeByte(a);
		return true;
	}

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_TOWER_INSPIRE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	int8 a;
};


class CCMD3ADFactory: public MessageFactory
{
public :

	virtual ~CCMD3ADFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_TOWER_INSPIRE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif