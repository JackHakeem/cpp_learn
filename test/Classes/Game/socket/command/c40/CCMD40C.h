#ifndef _CCMD40C_H_
#define _CCMD40C_H_
/** 
 * @author shenzhiqiang
 * @version 1.1.7.0
 * @description 客户端请求-全部拾取
CMSG_EGG_PICK_ALL= 0x40C
服务端 <- 客户端, 包结构:无
 * 
 * @data 2012-4-7 下午12:58:31 
 * 
 */ 
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD40C : public Packet
{
public:
	CCMD40C()
	{
	}
	virtual ~CCMD40C() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_EGG_PICK_ALL;}

	virtual	int32		GetMessageSize( ) const { return 0;}
	
};

bool CCMD40C::Write()
{
	
	return true;
}


class CCMD40CFactory: public MessageFactory
{
public :

	virtual ~CCMD40CFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_EGG_PICK_ALL;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif