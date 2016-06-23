#ifndef _CCMD3B2_H_
#define _CCMD3B2_H_

/**客户端打开幻龙塔面板
public static const CMSG_WORLD_ENTER_TOWER_GATE:uint	= 0X3B2;
*/

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD3B2 : public Packet
{
public:
	CCMD3B2() 
	{
	}

	virtual ~CCMD3B2() {}

	virtual bool	Write()
	{
		return true;
	}

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_ENTER_TOWER_GATE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
};


class CCMD3B2Factory: public MessageFactory
{
public :

	virtual ~CCMD3B2Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_ENTER_TOWER_GATE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif