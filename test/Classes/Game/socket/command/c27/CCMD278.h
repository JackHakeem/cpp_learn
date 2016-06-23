/** 退出战队请求
CMSG_WORLD_LEAVEGROUP = 0x278 
客户端->服务端, 包结构
Uint16		副本ID
Uint16		战队ID*/

#ifndef _CCMD278_H_
#define _CCMD278_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD278 : public Packet
{
public:
	CCMD278():a_fbId(0) , b_teamId(0)
	{}
	virtual ~CCMD278() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_LEAVEGROUP;}

	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	uint16 a_fbId;
	uint16 b_teamId;
};

bool CCMD278::Write()
{
	writeShort(a_fbId);
	writeShort(b_teamId);
	return true;
}


class CCMD278Factory: public MessageFactory
{
public :
	
	virtual ~CCMD278Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_LEAVEGROUP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif