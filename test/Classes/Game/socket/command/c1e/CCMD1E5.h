/**
	客户端卖出委派物品
	CMSG_WORLD_DELEGATE_SELL_ITEM = 0x1E5 (485)
	客户端->服务端, 包结构
	Short:		领取物品的数量
		Uint16:		领取的物品原型Id 
 */
#ifndef _CCMD1E5_H_
#define _CCMD1E5_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD1E5 : public Packet
{
public:
	CCMD1E5() 
	{
	}

	virtual ~CCMD1E5() {}

	std::list<int16> a_goods;
	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_DELEGATE_SELL_ITEM;}

	virtual	int32		GetMessageSize( ) const { return 0;}
};

class CCMD1E5Factory: public MessageFactory
{
public :

	virtual ~CCMD1E5Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_DELEGATE_SELL_ITEM;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};
#endif 