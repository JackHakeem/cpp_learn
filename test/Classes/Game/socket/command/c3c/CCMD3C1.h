#ifndef _CCMD3C1_H_
#define _CCMD3C1_H_


/**пео╒
CMSG_WORLD_REQUEST_TOWER_AWARD	= 0X3C1;
*/

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD3C1 : public Packet
{
public:
	CCMD3C1() 
	{
	}

	virtual ~CCMD3C1() {}

	virtual bool	Write()
	{
		return true;
	}

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_REQUEST_TOWER_AWARD;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
};


class CCMD3C1Factory: public MessageFactory
{
public :

	virtual ~CCMD3C1Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_REQUEST_TOWER_AWARD;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif