#ifndef  _SCMD19F_H__
#define _SCMD19F_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/** 
Server response CD reset for gold 
WMSG_WORLD_CLEAR_CD_COST = 0 x19F (415) 
The server-> the client, package structure 
Byte CD type 
Uint16 required number of gold COINS
*/ 

class SCMD19F : public Packet
{
public:
	SCMD19F() {}
	virtual ~SCMD19F() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_CLEAR_CD_COST;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:		 
	int8 a_type;
	int16 b_cost;
};


class SCMD19FFactory: public MessageFactory
{
public :

	virtual ~SCMD19FFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD19F();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_CLEAR_CD_COST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD19FHandler 
{
public:
	static uint32 Execute(SCMD19F* pPacket) ;
};
#endif