#ifndef _CCMD3CE_H_
#define _CCMD3CE_H_


/*客户端请求隐藏boss历练奖励
public static const CMSG_WORLD_REQ_HIDDEN_MONSTER_AWARD:uint	= 0X3CE;
*/

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD3CE : public Packet
{
public:
	CCMD3CE() 
	{
	}

	virtual ~CCMD3CE() {}

	virtual bool	Write()
	{
		return true;
	}

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_REQ_HIDDEN_MONSTER_AWARD;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
};


class CCMD3CEFactory: public MessageFactory
{
public :

	virtual ~CCMD3CEFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_REQ_HIDDEN_MONSTER_AWARD;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif