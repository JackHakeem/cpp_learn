/**
玩家使用复活结果
WMSG_WORLDBOSS_RELIVE = 0X2CE			
服务端->客户端, 包结构
Uint8			复活模式
Uint8			复活结果码
复活结果码：
0——成功
1——活动已结束
2——金币不足
3——系统内部错误
*/

#ifndef _SCMD2CE_H_
#define _SCMD2CE_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD2CE : public Packet
{
public:
	SCMD2CE() {}
	virtual ~SCMD2CE() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLDBOSS_RELIVE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint8 a_mode;	// 复活模式
	uint8 b_result;	// 复活结果码 0成功 1活动已结束 2金币不足 3系统内部错误
};


class SCMD2CEFactory: public MessageFactory
{
public :

	virtual ~SCMD2CEFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2CE();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLDBOSS_RELIVE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2CEHandler 
{
public:
	static uint32 Execute(SCMD2CE* pPacket) ;
};

#endif