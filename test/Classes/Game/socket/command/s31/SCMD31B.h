
 /**
 * to the client push new formation information
 * WMSG_WORLD_FORMATION_ADD = 0 x31B
 * the server-> the client, package structure
 * uint16 formation ID
 * uint8 formation level
 * uint8 leading role position
 */ 

#ifndef _SCMD31B_H_
#define _SCMD31B_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD31B : public Packet
{
public:
	SCMD31B() {}
	virtual ~SCMD31B() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_FORMATION_ADD;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint16 a_formationId ;
	uint8 b_formationLel ;
	uint8 c_roleSit ;

   
};


class SCMD31BFactory: public MessageFactory
{
public :

	virtual ~SCMD31BFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD31B();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_FORMATION_ADD;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD31BHandler 
{
public:
	static uint32 Execute(SCMD31B* pPacket) ;
};

#endif