#ifndef  _SCMD187_H__
#define _SCMD187_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/** 
Server response CD reset for gold 
WMSG_WORLD_CLEAR_CD_COST = 0 x19F (415) 
The server-> the client, package structure 
Byte CD type 
Uint16 required number of gold COINS
*/ 

class SCMD187 : public Packet
{
public:
	SCMD187() {}
	virtual ~SCMD187() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_UPDATE_CD;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:		 
	int8 a_type;
	int8 b_incd;
	int c_time;
};


class SCMD187Factory: public MessageFactory
{
public :

	virtual ~SCMD187Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD187();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_UPDATE_CD;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD187Handler 
{
public:
	static uint32 Execute(SCMD187* pPacket) ;
};
#endif