/**客户端请求购买鉴定格子数*/

#ifndef _CCMD2A0_H_
#define _CCMD2A0_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2A0 : public Packet
{
public:
	CCMD2A0() {}
	virtual ~CCMD2A0() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_BUY_IDENTIFY_POS;}

	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	
};

bool CCMD2A0::Write()
{
	return true;
}


class CCMD2A0Factory: public MessageFactory
{
public :
	
	virtual ~CCMD2A0Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_BUY_IDENTIFY_POS;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif