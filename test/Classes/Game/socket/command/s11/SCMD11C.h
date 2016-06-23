/**
WMSG_WORLD_RELOCATION: uint = 0x11C; / / 284 players re-positioning
 */

#ifndef _SCMD11C_H_
#define _SCMD11C_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD11C : public Packet
{
public:
	SCMD11C() {}
	virtual ~SCMD11C() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_RELOCATION;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16 a_x;
	int16 b_y;
};


class SCMD11CFactory: public MessageFactory
{
public :
	
	virtual ~SCMD11CFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD11C();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_RELOCATION;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD11CHandler 
{
public:
	static uint32 Execute(SCMD11C* pPacket) ;
};

#endif 