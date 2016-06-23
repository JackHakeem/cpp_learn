#ifndef  _SCMD2C4_H__
#define  _SCMD2C4_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
 *劫商结果
WMSG_WORLD_TRADE_ATTACK_RESULT= 0x2C4 (708)
客户端->服务端, 包结构
Uint32		被劫玩家ID
Uint8		劫商结果（0：失败；1：成功）
Uint8		暴击类型（0：无暴击；1：小暴；2：大暴）
Uint32		获得银币数量
 
 */

class SCMD2C4 : public Packet
{
public:
	SCMD2C4() {}
	virtual ~SCMD2C4() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_TRADE_ATTACK_RESULT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int a_id;
	int8 b_result;
	int8 c_doubleType;
	int d_silver;
};


class SCMD2C4Factory: public MessageFactory
{
public :

	virtual ~SCMD2C4Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2C4();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_TRADE_ATTACK_RESULT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2C4Handler 
{
public:
	static uint32 Execute(SCMD2C4* pPacket) ;
};
#endif