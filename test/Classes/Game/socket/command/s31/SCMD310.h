
/**
* Client requests to replace the mercenary's position in a formation returned package
* WMSG_WORLD_MERCENARY_ALTER_SITE = 0x310
* Server -> client package structure
* Uint8 replacement success.
* Uint16 formations ID.
* Uint32, mercenary unique ID
* The uint8 operating mercenary change the location to
* Uint32, replace the position of the mercenaries on the unique ID
* Uint8 mercenary was traded to the position
 */

#ifndef _SCMD310_H_
#define _SCMD310_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD310 : public Packet
{
public:
	SCMD310() {}
	virtual ~SCMD310() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_MERCENARY_ALTER_SITE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint8 a_isSuccess; // whether to replace a success
	uint16 b_formationId; // formation ID
	uint32 c_srcId; // operation mercenary unique ID
	uint8 d_srcPos; // change to the location of operation mercenary
	uint32 e_destId; // replace the position of mercenary unique ID
	uint8 f_destPos; // mercenary was traded to the position
};


class SCMD310Factory: public MessageFactory
{
public :

	virtual ~SCMD310Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD310();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_MERCENARY_ALTER_SITE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD310Handler 
{
public:
	static uint32 Execute(SCMD310* pPacket) ;
};

#endif