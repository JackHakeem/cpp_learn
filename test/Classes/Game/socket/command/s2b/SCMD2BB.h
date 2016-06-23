#ifndef  _SCMD2BB_H__
#define  _SCMD2BB_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
	结束跑商回应
	WMSG_WORLD_TRADE_END_RESP= 0x2BB (699)
	客户端->服务端, 包结构
	short: 		结束结果: 0结束成功, >0为结束失败, 代表相关ErrorCode
	int:			获得银币数量
	byte:		是否产生爆击 (0 无爆，1 小爆，2 大爆)
	int:		名声
	byte:       是否双倍时段 (0 否 1 是)
 */

class SCMD2BB : public Packet
{
public:
	SCMD2BB() {}
	virtual ~SCMD2BB() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_TRADE_END_RESP;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16 a_err;
	int b_silver;
	int8 c_bj;
	int d_pop;
	int8 e_doubleTime;
};


class SCMD2BBFactory: public MessageFactory
{
public :

	virtual ~SCMD2BBFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2BB();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_TRADE_END_RESP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2BBHandler 
{
public:
	static uint32 Execute(SCMD2BB* pPacket) ;
};
#endif