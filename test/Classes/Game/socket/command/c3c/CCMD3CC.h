#ifndef _CCMD3CC_H_
#define _CCMD3CC_H_

/**
/**客户端请求自己的爬塔排名信息
public static const CMSG_WORLD_REQ_MY_RANK:uint	= 0X3CC;
 */

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD3CC : public Packet
{
public:
	CCMD3CC() 
	{
	}

	virtual ~CCMD3CC() {}

	virtual bool	Write()
	{
		return true;
	}

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_REQ_MY_RANK;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
};


class CCMD3CCFactory: public MessageFactory
{
public :

	virtual ~CCMD3CCFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_REQ_MY_RANK;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif