/*
The role of equipment update notification
WMSG_WORLD_EQUIP_ITEM_UPDATE = 0x172 (370)
The service side -> client package structure
uint32 role ID
byte character rigging position (1-6)
uint32 items only Id
the uint16 goods prototype Id
*/

#ifndef _SCMD172_H_
#define _SCMD172_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD172 : public Packet
{
public:
	SCMD172()
	{
		a_figureId = 0;
		b_sitGrid = 0;
		c_eqpId = 0;
		d_eqpGoodsId = 0;
	}

	virtual ~SCMD172() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_EQUIP_ITEM_UPDATE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int32	a_figureId;
	int8	b_sitGrid;
	int32	c_eqpId;
	int16	d_eqpGoodsId;
};


class SCMD172Factory: public MessageFactory
{
public :
	
	virtual ~SCMD172Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD172();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_EQUIP_ITEM_UPDATE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD172Handler 
{
public:
	static uint32 Execute(SCMD172* pPacket) ;
};

#endif