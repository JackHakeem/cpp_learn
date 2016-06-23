/*
	玩家使用世界BOSS神赐鼓舞
	CMSG_WORLDBOSS_INSPIRE		= 0X2CB			
	客户端->服务端, 包结构：无
*/

#ifndef _CCMD2CB_H_
#define _CCMD2CB_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2CB : public Packet
{
public:
	CCMD2CB() {}
	virtual ~CCMD2CB() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLDBOSS_INSPIRE;}

	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	uint8 type;
};

bool CCMD2CB::Write()
{
	writeByte(type);
	return true;
}


class CCMD2CBFactory: public MessageFactory
{
public :
	
	virtual ~CCMD2CBFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLDBOSS_INSPIRE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif