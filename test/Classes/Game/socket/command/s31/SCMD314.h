/**
* The client requests the formation upgrade return package
* WMSG_WORLD_FORMATION_UPGRADE = 0x314
* Server -> client package structure
* Uint8 whether the operation was successful
* Uint16 formations ID.
* Uint8 formation rating
 */ 

#ifndef _SCMD314_H_
#define _SCMD314_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD314 : public Packet
{
public:
	SCMD314()
	{
		a_isOk = 0;
		b_formationId = 0;
		c_formationLel = 0;
	}

	virtual ~SCMD314() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_FORMATION_UPGRADE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	int8 a_isOk ;
	int16 b_formationId ;
	int8 c_formationLel ;

};


class SCMD314Factory: public MessageFactory
{
public :

	virtual ~SCMD314Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD314();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_FORMATION_UPGRADE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD314Handler 
{
public:
	static uint32 Execute(SCMD314* pPacket) ;
};

#endif 