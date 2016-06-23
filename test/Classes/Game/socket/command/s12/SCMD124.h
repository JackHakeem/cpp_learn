/**

* / / 292 to open a new map, which will open
WMSG_WORLD_OPEN_NEW_MAP = 0x124 (292),
The service side -> client package structure
uint16: the number of map
uint16: Open the map Id
byte: Map Status: 0 No clearance, a clearance, and 2 perfect, 3 all perfect

 */

#ifndef _SCMD124_H_
#define _SCMD124_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

struct SCMD124Node
{
	int16 a_mapId;
	int8  b_status;

	SCMD124Node()
	{
		a_mapId = 0;
		b_status = 0;
	}
};


class SCMD124 : public Packet
{
public:
	SCMD124()
	{
	}

	virtual ~SCMD124() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_OPEN_NEW_MAP;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	std::vector<SCMD124Node>a_openMap;
};


class SCMD124Factory: public MessageFactory
{
public :
	
	virtual ~SCMD124Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD124();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_OPEN_NEW_MAP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD124Handler 
{
public:
	static uint32 Execute(SCMD124* pPacket) ;
};

#endif