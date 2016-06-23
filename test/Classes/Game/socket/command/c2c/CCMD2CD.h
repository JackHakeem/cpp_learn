/*
	玩家使用复活
	CMSG_WORLDBOSS_RELIVE		= 0X2CD			
	客户端->服务端, 包结构：
	Uint8		复活模式（0：立即复活；1：重生）
*/

#ifndef _CCMD2CD_H_
#define _CCMD2CD_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2CD : public Packet
{
public:
	CCMD2CD() {}
	virtual ~CCMD2CD() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLDBOSS_RELIVE;}

	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	uint8 a_mode;		// 复活模式（0：立即复活；1：重生）
};

bool CCMD2CD::Write()
{
	writeByte(a_mode);
	return true;
}


class CCMD2CDFactory: public MessageFactory
{
public :
	
	virtual ~CCMD2CDFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLDBOSS_RELIVE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif