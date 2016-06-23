/**客户端保存临时鉴定结果*/

#ifndef _CCMD2A6_H_
#define _CCMD2A6_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2A6 : public Packet
{
public:
	CCMD2A6() {}
	virtual ~CCMD2A6() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_SAVE_IDENTIFY;}

	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	
};

bool CCMD2A6::Write()
{
	return true;
}


class CCMD2A6Factory: public MessageFactory
{
public :
	
	virtual ~CCMD2A6Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_SAVE_IDENTIFY;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif