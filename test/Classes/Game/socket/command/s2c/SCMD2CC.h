/**
	世界BOSS神赐鼓舞结果
	WMSG_WORLDBOSS_INSPIRE_RES = 0X2CC			
	服务端->客户端, 包结构
	Uint8			鼓舞结果
	鼓舞结果码：
	0——成功
	1——活动已结束
	2——鼓舞次数已满
	3——金币不足
	4——历练不足
	5——历练鼓舞失败
	6——系统内部错误

*/

#ifndef _SCMD2CC_H_
#define _SCMD2CC_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD2CC : public Packet
{
public:
	SCMD2CC() {}
	virtual ~SCMD2CC() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLDBOSS_INSPIRE_RES;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint8 a_result;		// 鼓舞结果 
};


class SCMD2CCFactory: public MessageFactory
{
public :

	virtual ~SCMD2CCFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2CC();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLDBOSS_INSPIRE_RES;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2CCHandler 
{
public:
	static uint32 Execute(SCMD2CC* pPacket) ;
};

#endif