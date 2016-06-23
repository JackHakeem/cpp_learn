#ifndef _CCMD2D8_H_
#define _CCMD2D8_H_
/**
 *客户端请求可传承物品列表	
CMSG_WORLD_INHERITABLE_INFO = 0x2D8 （728）
客户端->服务端, 包结构(无)
 
 */

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2D8 : public Packet
{
public:
	CCMD2D8() {}
	virtual ~CCMD2D8() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_INHERITABLE_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

};

bool CCMD2D8::Write()
{
	return true;
}


class CCMD2D8Factory: public MessageFactory
{
public :

	virtual ~CCMD2D8Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_INHERITABLE_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif