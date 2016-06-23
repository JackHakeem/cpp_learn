/** 战斗开启请求
CMSG_WORLD_GROUPFIGHT = 0x27C 
客户端->服务端, 包结构
Uint16		副本ID
Uint16		战队ID*/

#ifndef _CCMD27C_H_
#define _CCMD27C_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD27C : public Packet
{
public:
	CCMD27C():a_fbId(0) , b_teamId(0)
	{}
	virtual ~CCMD27C() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_GROUPFIGHT;}

	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	uint16 a_fbId;
	uint16 b_teamId;
};

bool CCMD27C::Write()
{
	writeShort(a_fbId);
	writeShort(b_teamId);
	return true;
}


class CCMD27CFactory: public MessageFactory
{
public :
	
	virtual ~CCMD27CFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_GROUPFIGHT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif