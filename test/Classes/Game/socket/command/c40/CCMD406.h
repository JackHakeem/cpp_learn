#ifndef _CCMD406_H_
#define _CCMD406_H_

/** 
 * @author shenzhiqiang
 * @version 1.1.7.0
 * @description 客户端请求-捡蛋
CMSG_EGG_PICK = 0x406
服务端 <- 客户端, 包结构:
Uint32		蛋ID
Uint32		蛋数 
 * @data 2012-3-26 上午11:56:40 
 * 
 */ 

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD406 : public Packet
{
public:
	CCMD406()
	{
	}
	virtual ~CCMD406() {}


	virtual bool	Write()
	{
		writeInt(a_id);
		writeInt(b_num);
		return true;
	}

public :
	virtual PacketID_t getPacketID() const { return CMSG_EGG_PICK;}

	virtual	int32		GetMessageSize( ) const { return 0;}
	
	int32 a_id;
	int32 b_num;
};



class CCMD406Factory: public MessageFactory
{
public :

	virtual ~CCMD406Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_EGG_PICK;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif