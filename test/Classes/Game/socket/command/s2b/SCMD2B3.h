#ifndef  _SCMD2B3_H__
#define  _SCMD2B3_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
 *跑商玩家仓位情况及剩余购买次数
WMSG_WORLD_TRADE_BANK = 0x2B3 (691)
服务端->客户端, 包结构
byte		剩余购买次数
short		仓库格子数量(目前为4)
	byte	格子开启状态(1为开启, 0为未开启)
	byte	格子商品Id(0为没有商品)
 
 */ 

class SCMD2B3 : public Packet
{
public:
	SCMD2B3() {}
	virtual ~SCMD2B3() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_TRADE_BANK;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_buyNum;
	int8 b_restPer;
	struct SCMD2B3Node
	{
		int8 a_isActive;
		int8 b_ItemId;
	};
	std::list<SCMD2B3Node> c_bankArr;
};


class SCMD2B3Factory: public MessageFactory
{
public :

	virtual ~SCMD2B3Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2B3();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_TRADE_BANK;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2B3Handler 
{
public:
	static uint32 Execute(SCMD2B3* pPacket) ;
};
#endif