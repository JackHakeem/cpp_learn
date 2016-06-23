/**
战斗开启通知
WMSG_WORLD_GROUPFIGHT = 0x27E 
服务端->客户端, 包结构
Uint16		副本ID
Uint16		战队ID
*/

#ifndef _SCMD27E_H_
#define _SCMD27E_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD27E : public Packet
{
public:
	SCMD27E() {}
	virtual ~SCMD27E() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_GROUPFIGHT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint16 a_fbId;
	uint16 b_teamId;
};


class SCMD27EFactory: public MessageFactory
{
public :

	virtual ~SCMD27EFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD27E();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_GROUPFIGHT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD27EHandler 
{
public:
	static uint32 Execute(SCMD27E* pPacket) ;
};

#endif