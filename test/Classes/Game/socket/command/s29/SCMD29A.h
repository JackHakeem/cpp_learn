/**
WMSG_WORLD_GET_VIP_AWARD_REQ = 0x29A, // vip reward
byte
*/

#ifndef _SCMD29A_H_
#define _SCMD29A_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD29A : public Packet
{
public:
	SCMD29A() {}
	virtual ~SCMD29A() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_GET_VIP_AWARD_REQ;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16	a_reward;
};


class SCMD29AFactory: public MessageFactory
{
public :

	virtual ~SCMD29AFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD29A();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_GET_VIP_AWARD_REQ;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD29AHandler 
{
public:
	static uint32 Execute(SCMD29A* pPacket) ;
};

#endif 