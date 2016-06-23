#ifndef _SCMD3CF_H_
#define _SCMD3CF_H_

/**
	服务端返回隐藏boss历练奖励
	WMSG_WORLD_REQ_HIDDEN_MONSTER_AWARD	= 0X3CF
	服务端->客户端, 包结构
	Uint16  	数量
		Uint8 		楼层
	　Uint8		对应奖励ID(3:历练)
	　Uint32		奖励数量 
	 	Uint16		当前层的奖励个数
			Uint32　 奖励ID
			Uint32	奖励数量
 */

#include "socket/network/Packet.h"
#include "socket/message/MessageFactory.h"
#include "socket/message/SocketCMDConst.h"
#include "BaseType.h"
#include "../s3b/SCMD3B5.h"

class SCMD3CF : public Packet
{
public:
	SCMD3CF(){}
	~SCMD3CF()
	{
	}

	virtual int32 Execute();

	virtual bool Read();

	virtual PacketID_t getPacketID()const { return WMSG_WORLD_REQ_HIDDEN_MONSTER_AWARD;}

public:
	struct SCMD3CFNode
	{
		int8 a_floor;
		int8 b_id;
		int c_num;
		std::list<SCMD3B5Node> d_floorReward;
		SCMD3CFNode()
		{
			a_floor = 0;
			b_id = 0;
			c_num = 0;
		}
	};
	std::list<SCMD3CFNode> a_rewards;
};


class SCMD3CFFactory : public MessageFactory
{
	virtual Packet* CreateMessage() {return new SCMD3CF();}

	virtual PacketID_t GetPacketID()const {return WMSG_WORLD_REQ_HIDDEN_MONSTER_AWARD;}

	virtual uint32 GetMessageMaxSize()const {return 0;}

};


class SCMD3CFHandler 
{
public:
	static uint32 Execute(SCMD3CF *pPacket) ;
};

#endif
