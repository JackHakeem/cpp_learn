/*
The role of equipment update notification
WMSG_WORLD_EQUIP_ITEM_UPDATE = 0x172 (370)
The service side -> client package structure
uint32 role ID
byte character rigging position (1-6)
uint32 items only Id
the uint16 goods prototype Id
*/

#ifndef _SCMD17D_H_
#define _SCMD17D_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD17D : public Packet
{
public:
	SCMD17D()
	{
		a_Probability = 0;
		b_Trend = 0;
	}

	virtual ~SCMD17D() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_SYS_EQUIPSTREN_PROB;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_Probability;
	int8 b_Trend;
};


class SCMD17DFactory: public MessageFactory
{
public :

	virtual ~SCMD17DFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD17D();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_SYS_EQUIPSTREN_PROB;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD17DHandler 
{
public:
	static uint32 Execute(SCMD17D* pPacket) ;
};

#endif