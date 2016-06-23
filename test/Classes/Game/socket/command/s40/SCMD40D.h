/** 
 * @author shenzhiqiang
 * @version 1.1.7.0
 * @description 服务端返回-仓库
WMSG_EGG_PICK_ALL = 0x40D
服务端 ->客户端, 包结构:
Uint8	响应码// 0成功 1背包空间不足,还有东西没拾取 3没有可以拾取的东西
 * @data 2012-4-7 下午12:59:20 
 * 
 */ 
#ifndef _SCMD40D_H_
#define _SCMD40D_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD40D : public Packet
{
public:
	SCMD40D()
	{
	}

	virtual ~SCMD40D() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_EGG_PICK_ALL;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_type;
};


class SCMD40DFactory: public MessageFactory
{
public :
	
	virtual ~SCMD40DFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD40D();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_EGG_PICK_ALL;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD40DHandler 
{
public:
	static uint32 Execute(SCMD40D* pPacket) ;
};

#endif