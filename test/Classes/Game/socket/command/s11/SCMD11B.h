/**
WMSG_WORLD_MOVE_EVENT: uint = 0x11B; / / 283 players move events
 */

#ifndef _SCMD11B_H_
#define _SCMD11B_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD11B : public Packet
{
public:
	SCMD11B() {}
	virtual ~SCMD11B() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_MOVE_EVENT;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8	a_type;  //Event types: one dialogue, animation, 3 battle
	int16	b_id;
};


class SCMD11BFactory: public MessageFactory
{
public :
	
	virtual ~SCMD11BFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD11B();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_MOVE_EVENT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD11BHandler 
{
public:
	static uint32 Execute(SCMD11B* pPacket) ;
};

#endif 