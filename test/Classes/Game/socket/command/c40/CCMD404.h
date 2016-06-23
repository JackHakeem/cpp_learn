#ifndef _CCMD404_H_
#define _CCMD404_H_

/** 
 * @author shenzhiqiang
 * @version 1.1.7.0
 * @description 客户端请求-开蛋
CMSG_EGG_OPEN = 0x404
服务端 <- 客户端, 包结构:
Uint32		蛋ID
 * @data 2012-3-26 上午11:56:25 
 * 
 */ 

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD404 : public Packet
{
public:
	CCMD404()
	{
	}
	virtual ~CCMD404() {}


	virtual bool	Write()
	{
		writeInt(a_id);
		return true;
	}

public :
	virtual PacketID_t getPacketID() const { return CMSG_EGG_OPEN;}

	virtual	int32		GetMessageSize( ) const { return 0;}
	
	int32 a_id;
};



class CCMD404Factory: public MessageFactory
{
public :

	virtual ~CCMD404Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_EGG_OPEN;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif