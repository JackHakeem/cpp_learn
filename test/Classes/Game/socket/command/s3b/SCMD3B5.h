#ifndef _SCMD3B5_H_
#define _SCMD3B5_H_

/**
	服务端返回打开幻龙塔面板信息
	WMSG_WORLD_APPLY_CLIMB_TOWER	= 0X3B5,		
	服务端->客户端, 包结构
	Uint8		免费进入剩余次数
	Uint8		本日进入次数（除免费次数外）
	Uint8		当前所在楼层
	Uint8		历史最高闯塔楼层
	Uint32		当前所在层的怪物ID
	Uint16		当前层的固定奖励数量
		Uint32　 奖励ID (大于100为物品／礼包ID)
		Uint32	奖励数量
	Uint8		是否显示当前层隐藏boss(0,否)
	Uint32 		下层怪物ID（无则为０，且奖励数量为０）
	Uint16		下层固定奖励数量
		Uint32　 奖励ID (大于100为物品／礼包ID)
		Uint32	奖励数量
	Uint8		是否显示下层隐藏boss(0,否)
	Uint8		鼓舞百分比（整数0-100）
	Uint32		下次历练鼓舞所需历练值
 */

#include "socket/network/Packet.h"
#include "socket/message/MessageFactory.h"
#include "socket/message/SocketCMDConst.h"
#include "BaseType.h"


struct SCMD3B5Node
{
	int a_rewardId;
	int b_rewardNum;
	SCMD3B5Node()
	{
		a_rewardId = 0;
		b_rewardNum = 0;
	}
};

class SCMD3B5 : public Packet
{
public:
	SCMD3B5()
	{
		a_numFree = 0;
		b_numPay = 0;
		c_curFloor = 0;
		d_maxFloor = 0;
		e_curMonsterId = 0;

		g_showCurBoss = 0;
		h_nextMonsterId = 0;

		j_showNextBoss = 0;
		k_inspire = 0;
		l_inspirePrac = 0;
	}
	~SCMD3B5()
	{
	}

	virtual int32 Execute();

	virtual bool Read();

	virtual PacketID_t getPacketID()const { return WMSG_WORLD_APPLY_CLIMB_TOWER;}

public:

	int8 a_numFree;
	int8 b_numPay;
	int8 c_curFloor;
	int8 d_maxFloor;
	int e_curMonsterId;
	std::list<SCMD3B5Node> f_curRewards;
	int8 g_showCurBoss;
	int h_nextMonsterId;
	std::list<SCMD3B5Node> i_nextRewards;
	int8 j_showNextBoss;
	int8 k_inspire;
	int l_inspirePrac;
};


class SCMD3B5Factory : public MessageFactory
{
	virtual Packet* CreateMessage() {return new SCMD3B5();}

	virtual PacketID_t GetPacketID()const {return WMSG_WORLD_APPLY_CLIMB_TOWER;}

	virtual uint32 GetMessageMaxSize()const {return 0;}

};


class SCMD3B5Handler 
{
public:
	static uint32 Execute(SCMD3B5 *pPacket) ;
};

#endif
