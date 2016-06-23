/** 
 * @author shenzhiqiang
 * @version 1.1.7.0
 * @description 服务端返回-洗蛋响应码
WMSG_EGG_PICK = 0x407
服务端 ->户端, 包结构:
Uint8		响应码
含义:0成功/1包裹空间不足/2系统内部错误
Uint32		物品ID
Uint32		物品数量

 * @data 2012-3-26 上午11:58:29 
 * 
 */ 
#ifndef _SCMD409_H_
#define _SCMD409_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD409 : public Packet
{
public:
	SCMD409()
	{
	}

	virtual ~SCMD409() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_EGG_WASH;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_type;
	int32 b_goodsId;
	int32 c_num;
};


class SCMD409Factory: public MessageFactory
{
public :
	
	virtual ~SCMD409Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD409();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_EGG_WASH;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD409Handler 
{
public:
	static uint32 Execute(SCMD409* pPacket) ;
};

#endif