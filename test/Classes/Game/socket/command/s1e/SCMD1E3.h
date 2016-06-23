/**
	请求委派返回包(委派结果)
	WMSG_WORLD_DELEGATE_RESULT = 0x1E3 (483)
	服务端->客户端, 包结构
	Uint8:		免费委派次数
	Uint16:		产生的物品原型Id
	Uint8:		商人类型
	Uint8:		商人信息（每个位代表一个商人，0：不存在，1：存在）
	Uint8:		新委派商人等级，即选中的商人(0 ~ 3)
 */
#ifndef _SCMD1E3_H_
#define _SCMD1E3_H_
#include "../../network/Packet.h"
#include "../../message/MessageFactory.h"
#include "../../message/SocketCMDConst.h"

class SCMD1E3 : public Packet
{
public:
	SCMD1E3() {}
	virtual ~SCMD1E3() {}


	virtual bool Read();
public :
	virtual int32 Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_DELEGATE_RESULT;}

	virtual	int32 GetMessageSize( ) const { return 0;}

public:
	int8 a_freeNum;
	int16 a_goodsId;
	int8 b_traderType;
	int8 c_trader;
	int8 d_selected;
};


class SCMD1E3Factory: public MessageFactory
{
public :
	virtual ~SCMD1E3Factory ()  {}

	virtual Packet* CreateMessage () {return new SCMD1E3();}

	virtual PacketID_t GetPacketID ()const  {return WMSG_WORLD_DELEGATE_RESULT;}

	virtual uint32 GetMessageMaxSize ()const  {return 0;}

};

class SCMD1E3Handler 
{
public:
	static uint32 Execute(SCMD1E3* pPacket) ;
};
#endif