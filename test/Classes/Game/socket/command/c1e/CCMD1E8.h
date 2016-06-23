/**
	领取活跃天数奖励
	CMSG_WORLD_ACTIVEDAY_AWARD_GET = 0x1E8
	客户端->服务端, 包结构
 */
#ifndef _CCMD1E8_H_
#define _CCMD1E8_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD1E8 : public Packet
{
public:
	CCMD1E8() 
	{
	}

	virtual ~CCMD1E8() {}

	virtual bool Write();

public :
	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_ACTIVEDAY_AWARD_GET;}

	virtual	int32		GetMessageSize( ) const { return 0;}
};

class CCMD1E8Factory: public MessageFactory
{
public :

	virtual ~CCMD1E8Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_ACTIVEDAY_AWARD_GET;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};
#endif 