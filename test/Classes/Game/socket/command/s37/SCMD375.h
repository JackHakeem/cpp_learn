/**
dungeon info
WMSG_WORLD_DUNGEON_BUY_ENTER_TIMES = 0x375(885),	
Byte		
Byte			
 */

#ifndef _SCMD375_H_
#define _SCMD375_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD375 : public Packet
{
public:
	SCMD375()
	{
		a_errorCode       = 0;
		b_canDungeonTimes = 0;
		c_buyDungeonTimes = 0;
	}

	virtual ~SCMD375() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_DUNGEON_BUY_ENTER_TIMES;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_errorCode;
	int8 b_canDungeonTimes;
	int8 c_buyDungeonTimes;
};


class SCMD375Factory: public MessageFactory
{
public :
	
	virtual ~SCMD375Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD375();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_DUNGEON_BUY_ENTER_TIMES;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD375Handler 
{
public:
	static uint32 Execute(SCMD375* pPacket) ;
};

#endif