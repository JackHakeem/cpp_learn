/**
* WMSG_WORLD_ MAP_SKIP = 0x118, / / ​​root / child map jump results
* Server -> client package structure
* Short: after the jump map Id
* Short: after the jump, the X coordinate
* Of short: Jump Y coordinates
 */

#ifndef _SCMD118_H_
#define _SCMD118_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD118 : public Packet
{
public:
	SCMD118()
	{
		a_mapId = 0;
		b_startX = 0;
		c_startY = 0;
	}

	virtual ~SCMD118() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_MAP_SKIP;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16	a_mapId;
	int16	b_startX;
	int16	c_startY;
};


class SCMD118Factory: public MessageFactory
{
public :
	
	virtual ~SCMD118Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD118();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_MAP_SKIP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD118Handler 
{
public:
	static uint32 Execute(SCMD118* pPacket) ;
};

#endif