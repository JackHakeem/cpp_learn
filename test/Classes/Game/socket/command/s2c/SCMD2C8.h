/**
	世界BOSS活动玩家信息
	WMSG_WORLDBOSS_PLAYERINFO = 0X2C8			
	服务端->客户端, 包结构
	Uint32			移动CD
	Uint32			战斗CD
	Uint8			累计鼓舞次数(0~10)
	Uint32			累计伤害BOSS点数
	活动累积奖励收益数组（银币、名声、魔石等）
	Uint32		累积奖励物品ID
	Uint32		累积奖励物品数量

*/

#ifndef _SCMD2C8_H_
#define _SCMD2C8_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD2C8 : public Packet
{
public:
	SCMD2C8() {}
	virtual ~SCMD2C8() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLDBOSS_PLAYERINFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	struct SCMD2C8Node 
	{
		uint32 a_id;		// 累积奖励物品ID
		uint32 b_num;		// 累积奖励物品数量
		SCMD2C8Node()
		{
			a_id = 0;
			b_num = 0;
		}
	};

	uint32 a_movingCD;		// 移动CD
	uint32 b_battleCD;		// 战斗CD
	uint8 c_boostNum;		// 累计鼓舞次数
	uint32 d_damage;			// 累计伤害
	std::list<SCMD2C8Node> e_awardList; // 活动累积奖励收益数组（银币、名声、魔石等）
};


class SCMD2C8Factory: public MessageFactory
{
public :

	virtual ~SCMD2C8Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2C8();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLDBOSS_PLAYERINFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2C8Handler 
{
public:
	static uint32 Execute(SCMD2C8* pPacket) ;
};

#endif