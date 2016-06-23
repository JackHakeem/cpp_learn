/** 
 * @author shenzhiqiang
 * @version 1.0.0.0
 * @data 2012-3-8 下午04:44:35 
 * @description 服务端返回淘宝祝福值
	WMSG_WORLD_DELEGATE_BLESS_INFO					= 0x1DD,
服务端->客户端, 包结构
Int:		现有淘宝祝福值
Int:		当前祝福值上限
Uint8:		是否提示

 * 
 */ 

#ifndef _SCMD1DD_H_
#define _SCMD1DD_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD1DD : public Packet
{
public:
	SCMD1DD() {}
	virtual ~SCMD1DD() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_DELEGATE_BLESS_INFO;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int a_blessValue;
	int b_blessTotal;
	int8 c_isShow;
};


class SCMD1DDFactory: public MessageFactory
{
public :
	
	virtual ~SCMD1DDFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1DD();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_DELEGATE_BLESS_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1DDHandler 
{
public:
	static uint32 Execute(SCMD1DD* pPacket) ;
};

#endif 