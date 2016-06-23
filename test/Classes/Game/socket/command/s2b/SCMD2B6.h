#ifndef  _SCMD2B6_H__
#define  _SCMD2B6_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
 *WMSG_WORLD_TRADE_PRICE= 0x2B6 (694)
服务端->客户端, 包结构
short:		城市地图数量
	short:	地图Id	
	short:	价格(如果是200, 显示为200%比如)
 	short:	地图NPC的Id
 */
class SCMD2B6 : public Packet
{
public:
	SCMD2B6() {}
	virtual ~SCMD2B6() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_TRADE_PRICE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	struct SCMD2B6Node
	{
		int16 a_mapId;
		int16 b_price;
		int16 c_npcId;
	};

	std::list<SCMD2B6Node> a_cityPriceArr;
};


class SCMD2B6Factory: public MessageFactory
{
public :

	virtual ~SCMD2B6Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2B6();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_TRADE_PRICE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2B6Handler 
{
public:
	static uint32 Execute(SCMD2B6* pPacket) ;
};
#endif