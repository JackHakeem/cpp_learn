/**
* Players request to upgrade Crystal
* CMSG_WORLD_UPGRADE_CRYSTAL = 0x184 (388)
* Client -> server-side package structure
* Byte crystal type (ID)
 */

#ifndef _CCMD184_H_
#define _CCMD184_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD184 : public Packet
{
public:
	CCMD184() {}
	virtual ~CCMD184() {}

	virtual bool	Write();	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_UPGRADE_CRYSTAL;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	uint8 a_id;

};


class CCMD184Factory: public MessageFactory
{
public :

	virtual ~CCMD184Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_UPGRADE_CRYSTAL;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif