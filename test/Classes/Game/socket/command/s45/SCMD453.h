/**
*   服务端返回阵营战离开返回
*   WMSG_CAMPFIGHT_QUIT_RES                         = 0X453, //	阵营战离开返回
*   服务端->客户端, 包结构
*   int8:	离开阵营返回值
*         0：成功，
*         -1：系统正在匹配对手中
*         -2：网络异常
*         -3：玩家不在阵营战中
**/

#ifndef _SCMD453_H_
#define _SCMD453_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD453 : public Packet
{
public:
	SCMD453() {}

	virtual ~SCMD453() {}

	virtual bool Read();

public:

	virtual int32 Execute();

	virtual PacketID_t getPacketID() { return WMSG_CAMPFIGHT_QUIT_RES; }

	virtual int32 GetMessageSize() const { return 0; }

public:
	int8       a_res;
};

class SCMD453Factory : public MessageFactory
{
public:

	virtual ~SCMD453Factory() {}

	virtual Packet* CreateMessage() { return new SCMD453(); }

	virtual PacketID_t GetPacketID() const { return WMSG_CAMPFIGHT_QUIT_RES; }

	virtual uint32 GetMessageMaxSize() const { return 0; }

};

class SCMD453Handler
{
public:
	static uint32 Execute(SCMD453* pPacket);
};

#endif 