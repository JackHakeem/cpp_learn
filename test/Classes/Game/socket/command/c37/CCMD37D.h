/**
* client requests battle winning streak info
CMSG_WORLD_PVP_QUALIFYING_STAR = 0x37D
Client -> server, the package structure
byte 0
 
 */

#ifndef _CCMD37D_H_
#define _CCMD37D_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD37D : public Packet
{
public:
	CCMD37D() 
	{
		a_operationType = 0;
		b_mapId = 0;
		c_roomId = 0;
	}

	virtual ~CCMD37D() {}

	virtual bool	Write();	 

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_DUNGEON_ROOM_OP;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	 int8 a_operationType;
	 int16 b_mapId;
	 int32 c_roomId;

};


class CCMD37DFactory: public MessageFactory
{
public :

	virtual ~CCMD37DFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_DUNGEON_ROOM_OP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif