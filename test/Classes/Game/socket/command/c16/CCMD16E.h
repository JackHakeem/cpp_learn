/**
//	ITEM_POS_NONE = 0,		// 没有位置
//	ITEM_POS_BAG = 1,		// 包裹
//	ITEM_POS_BANK = 2,		// 仓库
//	ITEM_POS_ROLE = 3,		// 角色身上
//	ITEM_POS_MAIL = 4,		// 邮件
*/
/**
*协议号： 0x16E
* 请求获取物品详细信息
* c -> s；
* Int8：位置类型
* Int8：具体位置
* uint：角色id
*/
#ifndef _CCMD16E_H_
#define _CCMD16E_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD16E : public Packet
{
public:
	CCMD16E() {}
	virtual ~CCMD16E() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_ITEM_INFO;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	int8 a_locationType; //位置类型
	int8 b_sitNum;		//具体位置
	uint c_roleId;		//角色id
};

class CCMD16EFactory: public MessageFactory
{
public :
	
	virtual ~CCMD16EFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_ITEM_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};
#endif 