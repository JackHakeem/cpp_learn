#ifndef _CCMD40A_H_
#define _CCMD40A_H_
/** 
 * @author shenzhiqiang
 * @version 1.1.7.0
 * @description 客户端请求-仓库
CMSG_EGG_DEPOT = 0x40A
服务端 <- 客户端, 包结构:无

 * @data 2012-3-26 上午11:57:02 
 * 
 */ 
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD40A : public Packet
{
public:
	CCMD40A()
	{
	}
	virtual ~CCMD40A() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_EGG_DEPOT;}

	virtual	int32		GetMessageSize( ) const { return 0;}
	
};

bool CCMD40A::Write()
{
	
	return true;
}


class CCMD40AFactory: public MessageFactory
{
public :

	virtual ~CCMD40AFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_EGG_DEPOT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif