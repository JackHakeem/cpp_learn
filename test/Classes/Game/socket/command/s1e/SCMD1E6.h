/**
	领取委派物品返回包
	WMSG_WORLD_DELEGATE_GET_ITEM_RESULT = 0x1E6,//486
	客户端->服务端, 包结构
	Uint16:		领取的物品原型Id
 */
#ifndef _SCMD1E6_H_
#define _SCMD1E6_H_
#include "../../network/Packet.h"
#include "../../message/MessageFactory.h"
#include "../../message/SocketCMDConst.h"

class SCMD1E6 : public Packet
{
public:
	SCMD1E6() {}
	virtual ~SCMD1E6() {}


	virtual bool Read();
public :
	virtual int32 Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_DELEGATE_GET_ITEM_RESULT;}

	virtual	int32 GetMessageSize( ) const { return 0;}

public:
	int16 a_goodsId;
};


class SCMD1E6Factory: public MessageFactory
{
public :
	virtual ~SCMD1E6Factory ()  {}

	virtual Packet* CreateMessage () {return new SCMD1E6();}

	virtual PacketID_t GetPacketID ()const  {return WMSG_WORLD_DELEGATE_GET_ITEM_RESULT;}

	virtual uint32 GetMessageMaxSize ()const  {return 0;}

};

class SCMD1E6Handler 
{
public:
	static uint32 Execute(SCMD1E6* pPacket) ;
};
#endif