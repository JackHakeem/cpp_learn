/**
*   阵营战参战返回
*   WMSG_CAMPFIGHT_FIGHT_RES                        = 0X455, //	
*   服务端->客户端, 包结构
*   int8:	离开阵营返回值
*         0：成功，
*         -1：阵营战未开始或者已经结束
*         -2：系统正在匹配对手中
*         -3：玩家网络异常
*         -4：玩家不在阵营战中
**/

#ifndef _SCMD455_H_
#define _SCMD455_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD455 : public Packet
{
public:
	SCMD455() {}

	virtual ~SCMD455() {}

	virtual bool Read();

public:

	virtual int32 Execute();

	virtual PacketID_t getPacketID() { return WMSG_CAMPFIGHT_FIGHT_RES; }

	virtual int32 GetMessageSize() const { return 0; }

public:
	int8       a_res;
};

class SCMD455Factory : public MessageFactory
{
public:

	virtual ~SCMD455Factory() {}

	virtual Packet* CreateMessage() { return new SCMD455(); }

	virtual PacketID_t GetPacketID() const { return WMSG_CAMPFIGHT_FIGHT_RES; }

	virtual uint32 GetMessageMaxSize() const { return 0; }

};

class SCMD455Handler
{
public:
	static uint32 Execute(SCMD455* pPacket);
};

#endif 