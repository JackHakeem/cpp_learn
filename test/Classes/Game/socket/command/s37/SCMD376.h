/**
pass gift
WMSG_WORLD_DUNGEON_AWARD = 0x376(886),	
Short		map ID
Byte		
Int			
Int			
Int			
Int			
 */

#ifndef _SCMD376_H_
#define _SCMD376_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD376 : public Packet
{
public:
	SCMD376()
	{
		a_mapId = 0;
		b_rank = 0;
		c_silver = 0;
		d_gold = 0;
		e_good1 = 0;
		f_good2 = 0;
	}

	virtual ~SCMD376() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_DUNGEON_AWARD;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16 a_mapId;
	int8 b_rank;
	int c_silver;
	int d_gold;
	int e_good1;
	int f_good2;
};


class SCMD376Factory: public MessageFactory
{
public :
	
	virtual ~SCMD376Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD376();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_DUNGEON_AWARD;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD376Handler 
{
public:
	static uint32 Execute(SCMD376* pPacket) ;
};

#endif