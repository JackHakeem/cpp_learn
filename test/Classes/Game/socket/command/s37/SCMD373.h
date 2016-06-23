/**
dungeon info
WMSG_WORLD_DUNGEON_ENTER_TIMES = 0x373(883),	
Byte		
Byte			
 */

#ifndef _SCMD373_H_
#define _SCMD373_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD373 : public Packet
{
public:
	SCMD373()
	{
		a_canDungeonTimes = 0;
		b_buyDungeonTimes = 0;
	}

	virtual ~SCMD373() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_DUNGEON_ENTER_TIMES;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_canDungeonTimes;
	int8 b_buyDungeonTimes;
};


class SCMD373Factory: public MessageFactory
{
public :
	
	virtual ~SCMD373Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD373();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_DUNGEON_ENTER_TIMES;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD373Handler 
{
public:
	static uint32 Execute(SCMD373* pPacket) ;
};

#endif