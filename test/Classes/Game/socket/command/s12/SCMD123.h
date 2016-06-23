/**
* Send which map is turned on, which will open
WMSG_WORLD_PROCESS = 0x123 (291),
The service side -> client package structure
uint16: the number of map
uint16: Open the map Id
byte: Map Status: 0 No clearance, a clearance, and 2 perfect, 3 all perfect
 */

#ifndef _SCMD123_H_
#define _SCMD123_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

struct SCMD123Node
{
	int16 a_mapId;
	int8  b_status;

	SCMD123Node()
	{
		a_mapId = 0;
		b_status = 0;
	}
};


class SCMD123 : public Packet
{
public:
	SCMD123()
	{
	}

	virtual ~SCMD123() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_PROCESS;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	std::vector<SCMD123Node>a_openMap;
};


class SCMD123Factory: public MessageFactory
{
public :
	
	virtual ~SCMD123Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD123();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_PROCESS;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD123Handler 
{
public:
	static uint32 Execute(SCMD123* pPacket) ;
};

#endif