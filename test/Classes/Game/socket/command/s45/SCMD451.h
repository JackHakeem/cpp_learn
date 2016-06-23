/**
*   服务端返回阵营战双方成员信息
*   WMSG_CAMPFIGHT_ENTER_RES = 0X451,
*   服务端->客户端, 包结构
*   int32: 登陆阵营返回值 
*         0：成功，
*         -1：阵营战活动不设置开放
*         -2：阵营战活动时间未到
*         -3：玩家等级不符合阵营战要求
*         -4：阵营战人数已满
*         -5：玩家状态异常
*         -6：初始化阵营战角色异常
*         -7：阵营ID错误
*         -8：玩家连接异常
**/

#ifndef _SCMD451_H_
#define _SCMD451_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD451 : public Packet
{
public:
	SCMD451() {}

	virtual ~SCMD451() {}

	virtual bool Read();

public:

	virtual int32 Execute();

	virtual PacketID_t getPacketID() { return WMSG_CAMPFIGHT_ENTER_RES; }

	virtual int32 GetMessageSize() const { return 0; }

public:
	int32  a_res;
};

class SCMD451Factory : public MessageFactory
{
public:

	virtual ~SCMD451Factory() {}

	virtual Packet* CreateMessage() { return new SCMD451(); }

	virtual PacketID_t GetPacketID() const { return WMSG_CAMPFIGHT_ENTER_RES; }

	virtual uint32 GetMessageMaxSize() const { return 0; }

};

class SCMD451Handler
{
public:
	static uint32 Execute(SCMD451* pPacket);
};

#endif 