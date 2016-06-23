/**
*   服务端返回阵营战个人信息
*   WMSG_CAMPFIGHT_INFO_RES                         = 0X459, //	阵营战信息返回
*   服务端->客户端, 包结构
*   Uint16：胜场
*   uint16:	玩家历史连胜次数
*   uint16:	总的获得名声
*   Uint32:	总的获得银币
*   uint16:	玩家的状态
**/

#ifndef _SCMD459_H_
#define _SCMD459_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD459 : public Packet
{
public:
	SCMD459() {}

	virtual ~SCMD459() {}

	virtual bool Read();

public:

	virtual int32 Execute();

	virtual PacketID_t getPacketID() { return WMSG_CAMPFIGHT_INFO_RES; }

	virtual int32 GetMessageSize() const { return 0; }

public:
	uint16 a_score;
	uint16 b_hisContiWinTms;
	uint16 c_sumPop;
	uint32 d_sumSilver;
	uint16 e_state;
};

class SCMD459Factory : public MessageFactory
{
public:

	virtual ~SCMD459Factory() {}

	virtual Packet* CreateMessage() { return new SCMD459(); }

	virtual PacketID_t GetPacketID() const { return WMSG_CAMPFIGHT_INFO_RES; }

	virtual uint32 GetMessageMaxSize() const { return 0; }

};

class SCMD459Handler
{
public:
	static uint32 Execute(SCMD459* pPacket);
};

#endif 