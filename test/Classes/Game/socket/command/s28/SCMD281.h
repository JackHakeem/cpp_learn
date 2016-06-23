/**
从队伍中删除玩家结果
CMSG_WORLD_KICKPLAYER_RESULT = 0x281 
服务端->客户端, 包结构
Uint16		副本ID
Uint16		战队ID
Uint32		玩家ID
Uint8		操作结果 
*/

#ifndef _SCMD281_H_
#define _SCMD281_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD281 : public Packet
{
public:
	SCMD281() {}
	virtual ~SCMD281() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_KICKPLAYER_RESULT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint16 a_fbId;
	uint16 b_teamId;
	int32 c_playerId;
	uint8 d_ret;
};


class SCMD281Factory: public MessageFactory
{
public :

	virtual ~SCMD281Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD281();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_KICKPLAYER_RESULT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD281Handler 
{
public:
	static uint32 Execute(SCMD281* pPacket) ;
};

#endif