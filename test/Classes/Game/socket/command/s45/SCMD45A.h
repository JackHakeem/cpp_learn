/**
*   阵营战直播信息返回
*   WMSG_CAMPFIGHT_LIVE_RES = 0X45A,	
*   服务端->客户端, 包结构
*   string: 广播消息
**/

#ifndef _SCMD45A_H_
#define _SCMD45A_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD45A : public Packet
{
public:
	SCMD45A() {}

	virtual ~SCMD45A() {}

	virtual bool Read();

public:

	virtual int32 Execute();

	virtual PacketID_t getPacketID() { return WMSG_CAMPFIGHT_LIVE_RES; }

	virtual int32 GetMessageSize() const { return 0; }

public:
	std::string  a_msg;
};

class SCMD45AFactory : public MessageFactory
{
public:

	virtual ~SCMD45AFactory() {}

	virtual Packet* CreateMessage() { return new SCMD45A(); }

	virtual PacketID_t GetPacketID() const { return WMSG_CAMPFIGHT_LIVE_RES; }

	virtual uint32 GetMessageMaxSize() const { return 0; }

};

class SCMD45AHandler
{
public:
	static uint32 Execute(SCMD45A* pPacket);
};

#endif 