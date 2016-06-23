/**
* the server to return to melting results 

WMSG_WORLD_SMELT = 0 x2D3 (723) 

The server-> the client, package structure 

Uint8 success: 0, failure; 1, success 

Uint32 currently has the number of crystal 
 */
#ifndef _SCMD2D3_H_
#define _SCMD2D3_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD2D3 : public Packet
{
public:
	SCMD2D3() {}
	virtual ~SCMD2D3() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_SMELT;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_type;
	int b_sparBum;
};


class SCMD2D3Factory: public MessageFactory
{
public :
	
	virtual ~SCMD2D3Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2D3();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_SMELT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2D3Handler 
{
public:
	static uint32 Execute(SCMD2D3* pPacket) ;
};

#endif