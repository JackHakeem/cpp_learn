/** 从队伍中删除玩家
CMSG_WORLD_KICKPLAYER = 0x280 
客户端->服务端, 包结构
Uint16		副本ID
Uint16		战队ID
Uint32		玩家ID */

#ifndef _CCMD280_H_
#define _CCMD280_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD280 : public Packet
{
public:
	CCMD280():a_fbId(0) , b_teamId(0),c_playerId(0)
	{}
	virtual ~CCMD280() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_KICKPLAYER;}

	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	uint16 a_fbId;
	uint16 b_teamId;
	int c_playerId;
};

bool CCMD280::Write()
{
	writeShort(a_fbId);
	writeShort(b_teamId);
	writeInt(c_playerId);
	return true;
}


class CCMD280Factory: public MessageFactory
{
public :
	
	virtual ~CCMD280Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_KICKPLAYER;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif