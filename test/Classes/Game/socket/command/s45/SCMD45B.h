/**
*   服务端返回阵营战双方成员信息
*   WMSG_CAMPFIGHT_BROADCAST_RES = 0X45B,
*   服务端->客户端, 包结构
*   Uint8:	阵营类型 0：冰之城 1：火之城
*   Uint32: 阵营得分
*   Uint16：成员数量
*       Int32:  玩家ID
*       String:	玩家名称
*       uint16:	玩家连胜次数
*   Uint8:	阵营类型 0：冰之城 1：火之城
*   Uint32: 阵营得分
*   Uint16：成员数量
*       Int32:  玩家ID
*       String:	玩家名称
*       uint16:	玩家连胜次数
**/

#ifndef _SCMD45B_H_
#define _SCMD45B_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

struct SCMD45BNode
{
	SCMD45BNode()
	{
		a_playerId = 0;
		b_name = "";
		c_contiWin = 0;
	}

	int32       a_playerId;
	std::string b_name;
	int16       c_contiWin;

};

class SCMD45B : public Packet
{
public:
	SCMD45B() {}

	virtual ~SCMD45B() {}

	virtual bool Read();

public:

	virtual int32 Execute();

	virtual PacketID_t getPacketID() { return WMSG_CAMPFIGHT_BROADCAST_RES; }

	virtual int32 GetMessageSize() const { return 0; }

public:
	uint8  a_type;
	uint32 b_score;
	int16  c_num;
	std::vector<SCMD45BNode> d_members;
	uint8  e_type;
	uint32 f_score;
	int16  g_num;
	std::vector<SCMD45BNode> h_members;
};

class SCMD45BFactory : public MessageFactory
{
public:

	virtual ~SCMD45BFactory() {}

	virtual Packet* CreateMessage() { return new SCMD45B(); }

	virtual PacketID_t GetPacketID() const { return WMSG_CAMPFIGHT_BROADCAST_RES; }

	virtual uint32 GetMessageMaxSize() const { return 0; }

};

class SCMD45BHandler
{
public:
	static uint32 Execute(SCMD45B* pPacket);
};

#endif 