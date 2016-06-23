#ifndef _CCMD3DE_H_
#define _CCMD3DE_H_


/**пео╒
CMSG_WORLD_REQUEST_TOWER_AWARD	= 0X3DE;
*/

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD3DE : public Packet
{
public:
	CCMD3DE() 
	{
	}

	virtual ~CCMD3DE() {}

	virtual bool	Write()
	{
		return true;
	}

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_TOWER_RECLIMB_REQ;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
};


class CCMD3DEFactory: public MessageFactory
{
public :

	virtual ~CCMD3DEFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_TOWER_RECLIMB_REQ;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif