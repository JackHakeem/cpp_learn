/**
	客户端请求活跃天数奖励信息
	CMSG_WORLD_ACTIVEDAY_AWARD_INFO = 0x1E7
	客户端->服务端, 包结构
 */
#ifndef _CCMD1E7_H_
#define _CCMD1E7_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD1E7 : public Packet
{
public:
	CCMD1E7() 
	{
	}

	virtual ~CCMD1E7() {}

	virtual bool Write();

public :
	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_ACTIVEDAY_AWARD_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}
};

class CCMD1E7Factory: public MessageFactory
{
public :

	virtual ~CCMD1E7Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_ACTIVEDAY_AWARD_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};
#endif 