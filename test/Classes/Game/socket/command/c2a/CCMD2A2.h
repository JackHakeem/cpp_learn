/**客户端请求所有俑兵鉴定属性信息*/

#ifndef _CCMD2A2_H_
#define _CCMD2A2_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2A2 : public Packet
{
public:
	CCMD2A2() {}
	virtual ~CCMD2A2() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_REQ_IDENTIFY_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}
public:

};

bool CCMD2A2::Write()
{
	return true;
}


class CCMD2A2Factory: public MessageFactory
{
public :

	virtual ~CCMD2A2Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_REQ_IDENTIFY_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif