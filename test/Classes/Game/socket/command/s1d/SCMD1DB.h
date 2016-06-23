/** 
 * @author shenzhiqiang
 * @version 1.1.4.0
 * @description 服务端返回兑换结果
	WMSG_WORLD_DELEGATE_BGET_BLESS_ITEM_RESP					= 0x1DB,
服务端->客户端, 包结构
Uint16:		兑换物品原型Id
Uint8:		兑换结果(0：失败；1：成功)
 * @data 2012-3-12 下午05:54:45 
 * 
 */ 

#ifndef _SCMD1DB_H_
#define _SCMD1DB_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD1DB : public Packet
{
public:
	SCMD1DB() {}
	virtual ~SCMD1DB() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_DELEGATE_BGET_BLESS_ITEM_RESP;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16 a_id;
	int8 b_type;
};


class SCMD1DBFactory: public MessageFactory
{
public :
	
	virtual ~SCMD1DBFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1DB();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_DELEGATE_BGET_BLESS_ITEM_RESP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1DBHandler 
{
public:
	static uint32 Execute(SCMD1DB* pPacket) ;
};

#endif 