/*
Update gold sum.
WMSG_WORLD_UPDATE_GOLDSUM = 0x1EE (494)
int32 nowCount
int32 addCount
*/
/**
	 委派信息返回包
	 WMSG_WORLD_DELEGATE_INFO_RETURN = 0x1E1 (481)
	 服务端->客户端, 包结构
	 Uint8:		免费委派次数
	 Uint8:		戒指商人（每个位代表一个商人，0：不存在，1：存在）
	 Uint8:		项链商人（每个位代表一个商人，0：不存在，1：存在）
	 Short:		暂存物品的数量
	 	Uint16:		暂存的物品原型Id 
 */
#ifndef _SCMD1E1_H_
#define _SCMD1E1_H_
#include "../../network/Packet.h"
#include "../../message/MessageFactory.h"
#include "../../message/SocketCMDConst.h"

class SCMD1E1 : public Packet
{
public:
	SCMD1E1() {}
	virtual ~SCMD1E1() {}


	virtual bool Read();
public :
	virtual int32 Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_DELEGATE_INFO_RETURN;}

	virtual	int32 GetMessageSize( ) const { return 0;}

	/*struct SCMD1E1Node
	{
	int16 a_goodsId;
	};*/
public:
	int8 a_freeNum;
	int8 b_ringTrader;
	int8 c_cloakTrader;
	std::list<int16> d_goods;
};


class SCMD1E1Factory: public MessageFactory
{
public :
	virtual ~SCMD1E1Factory ()  {}

	virtual Packet* CreateMessage () {return new SCMD1E1();}

	virtual PacketID_t GetPacketID ()const  {return WMSG_WORLD_DELEGATE_INFO_RETURN;}

	virtual uint32 GetMessageMaxSize ()const  {return 0;}

};

class SCMD1E1Handler 
{
public:
	static uint32 Execute(SCMD1E1* pPacket) ;
};
#endif