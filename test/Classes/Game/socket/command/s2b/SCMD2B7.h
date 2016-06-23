#ifndef  _SCMD2B7_H__
#define  _SCMD2B7_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
 *达成一个特殊事件
WMSG_WORLD_TRADE_EVENT= 0x2B7 (695)
服务端->客户端, 包结构
byte:	达成事件类型(1, 2, 3分布代表X星事件)
short:	奖励物品Id(目前为银币, Id为2, 今后视情况扩展)
int:	奖励数量
 
 */

class SCMD2B7 : public Packet
{
public:
	SCMD2B7() {}
	virtual ~SCMD2B7() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_TRADE_EVENT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_eventType;
	int16 b_awardType;
	int c_awardNum;
};


class SCMD2B7Factory: public MessageFactory
{
public :

	virtual ~SCMD2B7Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2B7();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_TRADE_EVENT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2B7Handler 
{
public:
	static uint32 Execute(SCMD2B7* pPacket) ;
};
#endif