#ifndef _SCMD19D_H_
#define _SCMD19D_H_
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
The server response crystal required for the upgrade CD time
WMSG_WORLD_REQ_UPGRADE_TIME = 0x19D (413)
The service side -> client package structure
Byte type of request, 1: passive skills; 2: formation; 3: Crystal
Short skills (formation / crystal) ID
The Uint32 required time (in seconds)
 */

class SCMD19D : public Packet
{
public:
	SCMD19D() {}
	virtual ~SCMD19D() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_REQ_UPGRADE_TIME	;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	 
	uint8 a_type;
	uint16 b_id ;
	uint32 c_time; 

};


class SCMD19DFactory: public MessageFactory
{
public :

	virtual ~SCMD19DFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD19D();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_REQ_UPGRADE_TIME	;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD19DHandler 
{
public:
	static uint32 Execute(SCMD19D* pPacket) ;
};

#endif 