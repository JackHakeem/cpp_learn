/**
 * 	hero award result
	WMSG_WORLD_HERO_GET_AWARD = 0x287 
	server->client pack
	Uint8	result£¨0: suc£»non-0: errcode£©
	Uint8	award type£¨0: gold; 1: silver; 2:exp; 3: reputation; 4: strength£©
	Uint32	award value
 */

#ifndef _SCMD287_H_
#define _SCMD287_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "SCMD287Node.h"

class SCMD287 : public Packet
{
public:
	SCMD287() {}
	virtual ~SCMD287() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_HERO_GET_AWARD;}

	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	int8 a_ret;
	std::vector<SCMD287Node> b_rewards; 
};


class SCMD287Factory: public MessageFactory
{
public :
	
	virtual ~SCMD287Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD287();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_HERO_GET_AWARD;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD287Handler 
{
public:
	static uint32 Execute(SCMD287* pPacket) ;
};

#endif 