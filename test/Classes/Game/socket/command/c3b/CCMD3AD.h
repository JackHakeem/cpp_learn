#ifndef _CCMD3B6_H_
#define _CCMD3B6_H_

/**客户端开始挑战塔内怪物
public static const CMSG_WORLD_START_CLIMB_TOWER:uint	= 0X3B6;
*/

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD3B6 : public Packet
{
public:
	CCMD3B6() 
	{
		a_isGUA = 0;
	}

	virtual ~CCMD3B6() {}

	virtual bool	Write()
	{
		writeByte(a_isGUA);
		return true;
	}

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_START_CLIMB_TOWER;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	int8 a_isGUA;
};


class CCMD3B6Factory: public MessageFactory
{
public :

	virtual ~CCMD3B6Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_START_CLIMB_TOWER;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif