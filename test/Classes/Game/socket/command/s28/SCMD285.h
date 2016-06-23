/**
 * WMSG_WORLD_HERO_INFO = 0x285 
服务端->客户端, 包结构
Uint16		本人排名
Uint32		下次奖励发放时间
英雄榜奖励数组：（如果奖励已领取，则数组长度为0）
	Uint16	奖励物品ID
	Uint32	奖励物品数量
英雄榜前25名玩家数组
	uint16	排名（0~24）
	uint32	玩家ID（若是无玩家的话则为0，客户端显示“无玩家占领”）
	string	玩家名字
	uint32	人物等级
 */

#ifndef _SCMD285_H_
#define _SCMD285_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "SCMD285Node.h"
#include "SCMD285Node1.h"

class SCMD285 : public Packet
{
public:
	SCMD285() {}
	virtual ~SCMD285() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_HERO_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	int16	a_meRank;	uint32	b_time;
	std::vector<SCMD285Node1> c_rewards;
	std::vector<SCMD285Node> d_rankArr;
};


class SCMD285Factory: public MessageFactory
{
public :
	
	virtual ~SCMD285Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD285();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_HERO_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD285Handler 
{
public:
	static uint32 Execute(SCMD285* pPacket) ;
};

#endif 