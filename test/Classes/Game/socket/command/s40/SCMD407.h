/** 
 * @author shenzhiqiang
 * @version 1.1.7.0
 * @description 服务端返回-捡蛋响应码
WMSG_EGG_OPEN = 0x405
服务端 -> 客户端, 包结构:
Uint8		响应码
含义:0成功/1包裹空间不足/2银币上限/3金币上限/4精力上限/5系统内部错误

 * @data 2012-3-26 上午11:58:19 
 * 
 */ 
#ifndef _SCMD407_H_
#define _SCMD407_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD407 : public Packet
{
public:
	SCMD407()
	{
	}

	virtual ~SCMD407() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_EGG_PICK;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_type;
};


class SCMD407Factory: public MessageFactory
{
public :
	
	virtual ~SCMD407Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD407();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_EGG_PICK;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD407Handler 
{
public:
	static uint32 Execute(SCMD407* pPacket) ;
};

#endif