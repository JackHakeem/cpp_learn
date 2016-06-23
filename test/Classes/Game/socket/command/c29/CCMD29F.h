/**
 *客户端请求领取VIP金币返还奖励
CMSG_WORLD_GET_VIP_AWARD_REQ	= 0X29F,			
客户端->服务端, 包结构
Uint32		0
 
 */

#ifndef _CCMD29F_H_
#define _CCMD29F_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD29F : public Packet
{
public:
	CCMD29F() {}
	virtual ~CCMD29F() {}


	virtual bool	Write() 
	{
		writeInt(0);
		return true;
	}
public :
	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_GET_VIP_AWARD_REQ;}	
	virtual	int32		GetMessageSize( ) const { return 0;}
};


class CCMD29FFactory: public MessageFactory
{
public :

	virtual ~CCMD29FFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_GET_VIP_AWARD_REQ;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif 