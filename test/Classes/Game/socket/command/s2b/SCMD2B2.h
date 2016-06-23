#ifndef  _SCMD2B2_H__
#define  _SCMD2B2_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
 *跑商玩家商品列表
WMSG_WORLD_TRADE_QUEUE = 0x2B2 (690)
服务端->客户端, 包结构
byte		商品Id1
short		刷新次数
 
 */
class SCMD2B2 : public Packet
{
public:
	SCMD2B2() {}
	virtual ~SCMD2B2() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_TRADE_QUEUE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_item1;
	int16 b_refreshTimes;
	int16 c_beated;
	int16 d_buyTokenCnt;
	int32 e_robSilver;
	int32 e_robPop;
	int16 f_mapId;
};


class SCMD2B2Factory: public MessageFactory
{
public :

	virtual ~SCMD2B2Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2B2();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_TRADE_QUEUE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2B2Handler 
{
public:
	static uint32 Execute(SCMD2B2* pPacket) ;
};
#endif