#ifndef _CCMD1DE_H_
#define _CCMD1DE_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/*
 玩家请求新手引导CD清零
CMSG_WORLD_GUIDE_CDCONDITION = 0x1DE
	客户端->服务端, 包结构
	byte	 	CD类型
*/

class CCMD1DE : public Packet
{
public:
	CCMD1DE() {}
	virtual ~CCMD1DE() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_WORLD_GUIDE_CDCONDITION;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

	int8 a_cdType ;
};

bool CCMD1DE::Write()
{
	writeByte(a_cdType);
	return true;
}

class CCMD1DEFactory: public MessageFactory
{
public :

	virtual ~CCMD1DEFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_GUIDE_CDCONDITION;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif