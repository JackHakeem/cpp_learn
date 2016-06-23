/**
 * 玩家使用银矿战鼓舞	
CMSG_SILVERMINE_INSPIRE = 0x368 
客户端->服务端, 包结构
Uint8		鼓舞类型
 */

#ifndef _CCMD368_H_
#define _CCMD368_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD368 : public Packet
{
public:
	CCMD368() 
	{
		a_type = 0;
	}

	virtual ~CCMD368() {}

	virtual bool	Write();	 

	virtual PacketID_t getPacketID() const { return CMSG_SILVERMINE_INSPIRE;}
													
	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	int8 a_type;
};


class CCMD368Factory: public MessageFactory
{
public :

	virtual ~CCMD368Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_SILVERMINE_INSPIRE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif