#ifndef _CCMD3AF_H_
#define _CCMD3AF_H_

/*客户端鼓舞
/**客户端打隐藏boss
public static const CMSG_WORLD_TOWER_CHALLENGE_HIDDEN_MONSTER:uint	= 0X3AF;
*/

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD3AF : public Packet
{
public:
	CCMD3AF() 
	{
	}

	virtual ~CCMD3AF() {}

	virtual bool	Write()
	{
		return true;
	}

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_TOWER_CHALLENGE_HIDDEN_MONSTER;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
};


class CCMD3AFFactory: public MessageFactory
{
public :

	virtual ~CCMD3AFFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_TOWER_CHALLENGE_HIDDEN_MONSTER;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif