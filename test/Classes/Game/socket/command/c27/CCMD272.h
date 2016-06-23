/**战队信息请求
CMSG_WORLD_GROUPINFO_REQ = 0x272 
客户端->服务端, 包结构
Uint16		副本ID
Uint16		队伍ID*/

#ifndef _CCMD272_H_
#define _CCMD272_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD272 : public Packet
{
public:
	CCMD272():a_fbId(0) , b_teamId(0)
	{}
	virtual ~CCMD272() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_GROUPINFO_REQ;}

	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	uint16 a_fbId;
	uint16 b_teamId;
};

bool CCMD272::Write()
{
	writeShort(a_fbId);
	writeShort(b_teamId);
	return true;
}


class CCMD272Factory: public MessageFactory
{
public :
	
	virtual ~CCMD272Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_GROUPINFO_REQ;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif