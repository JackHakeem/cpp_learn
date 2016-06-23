#ifndef _CCMD408_H_
#define _CCMD408_H_

/** 
 * @author shenzhiqiang
 * @version 1.1.7.0
 * @description 客户端请求-洗蛋
CMSG_EGG_WASH = 0x408
服务端 <- 客户端, 包结构:
Uint32		蛋ID

 * @data 2012-3-26 上午11:56:51 
 * 
 */ 

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD408 : public Packet
{
public:
	CCMD408()
	{
	}
	virtual ~CCMD408() {}


	virtual bool	Write()
	{
		writeInt(a_id);
		return true;
	}

public :
	virtual PacketID_t getPacketID() const { return CMSG_EGG_WASH;}

	virtual	int32		GetMessageSize( ) const { return 0;}
	
	int32 a_id;
};



class CCMD408Factory: public MessageFactory
{
public :

	virtual ~CCMD408Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_EGG_WASH;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif