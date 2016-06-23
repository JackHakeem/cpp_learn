#ifndef  _SCMD2B4_H__
#define  _SCMD2B4_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
 *跑商玩家商品购买历史
WMSG_WORLD_TRADE_HISTORY = 0x2B4 (692)
服务端->客户端, 包结构
byte		1号位商品Id1
byte		2号位商品Id2
byte		3号位商品Id3
byte		4号位商品Id4
byte		5号位商品Id5
 
 */
class SCMD2B4 : public Packet
{
public:
	SCMD2B4() {}
	virtual ~SCMD2B4() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_TRADE_HISTORY;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_historyItem1;
	int8 b_historyItem2;
	int8 c_historyItem3;
	int8 d_historyItem4;
	int8 e_historyItem5;
};


class SCMD2B4Factory: public MessageFactory
{
public :

	virtual ~SCMD2B4Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2B4();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_TRADE_HISTORY;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2B4Handler 
{
public:
	static uint32 Execute(SCMD2B4* pPacket) ;
};
#endif