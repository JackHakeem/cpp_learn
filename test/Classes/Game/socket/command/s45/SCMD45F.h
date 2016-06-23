/**
*   阵营战鼓舞返回
*   WMSG_CAMPFIGHT_INSPIRE_RES  = 0X45F,  
*   服务端->客户端, 包结构
	int8   a_mod;  鼓舞方式
	int8   b_res;  鼓舞返回值 
		0成功 
		1鼓舞已满 
		2金币不足 
		3历练不足 
		4概率鼓舞失败，历练已经消耗
	uint8  c_harmInc;
	uint8  d_lifeInc;
**/

#ifndef _SCMD45F_H_
#define _SCMD45F_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD45F : public Packet
{
public:
	SCMD45F() {}

	virtual ~SCMD45F() {}

	virtual bool Read();

public:

	virtual int32 Execute();

	virtual PacketID_t getPacketID() { return WMSG_CAMPFIGHT_INSPIRE_RES; }

	virtual int32 GetMessageSize() const { return 0; }

public:
	//int8   a_mod;
	int8   b_res;
	uint8  c_harmInc;
	uint8  d_lifeInc;
};

class SCMD45FFactory : public MessageFactory
{
public:

	virtual ~SCMD45FFactory() {}

	virtual Packet* CreateMessage() { return new SCMD45F(); }

	virtual PacketID_t GetPacketID() const { return WMSG_CAMPFIGHT_INSPIRE_RES; }

	virtual uint32 GetMessageMaxSize() const { return 0; }

};

class SCMD45FHandler
{
public:
	static uint32 Execute(SCMD45F* pPacket);
};

#endif 