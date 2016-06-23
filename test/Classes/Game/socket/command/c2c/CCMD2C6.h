/**
 * 客户端获取世界BOSS活动开启时间
 * CMSG_WORLDBOSS_GETOPENTIME	= 0X2C6			
 * 客户端->服务端, 包结构：无
*/

#ifndef _CCMD2C6_H_
#define _CCMD2C6_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2C6 : public Packet
{
public:
	CCMD2C6() {}
	virtual ~CCMD2C6() {}


	virtual bool	Write()
	{
		return true;
	}
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLDBOSS_GETOPENTIME;}

	virtual	int32		GetMessageSize( ) const { return 0;}

};


class CCMD2C6Factory: public MessageFactory
{
public :
	
	virtual ~CCMD2C6Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLDBOSS_GETOPENTIME;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif