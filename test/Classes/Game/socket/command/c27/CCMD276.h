/** 加入战队请求
CMSG_WORLD_JOINGROUP = 0x276 
客户端->服务端, 包结构
Uint16		副本ID
Uint16		战队ID*/

#ifndef _CCMD276_H_
#define _CCMD276_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD276 : public Packet
{
public:
	CCMD276():a_fbId(0) , b_teamId(0)
	{}
	virtual ~CCMD276() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_JOINGROUP;}

	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	uint16 a_fbId;
	uint16 b_teamId;
};

bool CCMD276::Write()
{
	writeShort(a_fbId);
	writeShort(b_teamId);
	return true;
}


class CCMD276Factory: public MessageFactory
{
public :
	
	virtual ~CCMD276Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_JOINGROUP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif