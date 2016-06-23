/** 
 * @author shenzhiqiang
 * @version 1.1.7.0
 * @description 服务端返回-许愿响应码
WMSG_EGG_PLEGE = 0x403
服务端 -> 客户端, 包结构:
Uint8		响应码
含义:0成功/1金币不足/2临时仓库空间不足/3系统内部错误

 * @data 2012-3-26 上午11:58:02 
 * 
 */ 
#ifndef _SCMD405_H_
#define _SCMD405_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD405 : public Packet
{
public:
	SCMD405()
	{
	}

	virtual ~SCMD405() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_EGG_OPEN;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_type;
	int32 b_eggId;
	int32 c_goodsId;
	int32 d_goodsNum;
};


class SCMD405Factory: public MessageFactory
{
public :
	
	virtual ~SCMD405Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD405();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_EGG_OPEN;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD405Handler 
{
public:
	static uint32 Execute(SCMD405* pPacket) ;
};

#endif