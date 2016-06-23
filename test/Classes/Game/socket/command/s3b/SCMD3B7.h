#ifndef _SCMD3B7_H_
#define _SCMD3B7_H_

/**
	服务端返回战斗结果信息(若挑战成功，发对应的楼层奖励)
	WMSG_WORLD_RESULT_CLIMB_TOWER	= 0X3B7,	
	服务端->客户端, 包结构
	Uint8		是否可以前往下一层(1,是；０，否)
	Uint8		是否触发抽奖（客户端弹出抽奖面板）
	Uint8		免费进入剩余次数
	Uint8		本日进入次数（除免费次数外）
	Uint8		挑战前的楼层
	Uint8		挑战后的楼层(若当前层挑战成功并已经到达最高层，客户端发送离塔包; 若失败则等于挑战前的楼层)
	Uint8		历史最高闯塔楼层
	Uint32		当前所在层的怪物ID
	Uint16		当前层的固定奖励数量
	Uint32　    奖励ID (大于100为物品／礼包ID)
	Uint32	    奖励数量
	Uint8		是否显示当前层隐藏boss(0,否)
	Uint32 		下层怪物ID（无则为０，且奖励数量为０）
	Uint16		下层固定奖励数量
	Uint32　    奖励ID (大于100为物品／礼包ID)
	Uint32	    奖励数量
	Uint8		是否显示下层隐藏boss(0,否)
	Uint8		鼓舞百分比（整数）
	Uint32		下次历练鼓舞所需历练值
 */

#include "socket/network/Packet.h"
#include "socket/message/MessageFactory.h"
#include "socket/message/SocketCMDConst.h"
#include "BaseType.h"
#include "SCMD3B5.h"

class SCMD3B7 : public Packet
{
public:
	SCMD3B7()
	{
		a_isWin = 0;
		b_isLottery = 0;
		c_numFree = 0;
		d_numPay = 0;
		e_beforeFloor = 0;
		f_afterFloor = 0;
		g_maxFloor = 0;
		h_curMonsterId = 0;
		j_showCurBoss = 0;
		k_nextMonsterId = 0;
		m_showNextBoss = 0;
		n_inspire = 0;
		o_inspirePrac = 0;
	}
	~SCMD3B7()
	{
	}

	virtual int32 Execute();

	virtual bool Read();

	virtual PacketID_t getPacketID()const { return WMSG_WORLD_RESULT_CLIMB_TOWER;}

public:

	int8 a_isWin;
	int8 b_isLottery;
	int8 c_numFree;
	int8 d_numPay;
	int8 e_beforeFloor;
	int8 f_afterFloor;
	int8 g_maxFloor;
	int h_curMonsterId;
	std::list<SCMD3B5Node> i_curRewards;
	int8 j_showCurBoss;
	int k_nextMonsterId;
	std::list<SCMD3B5Node> l_nextRewards;
	int8 m_showNextBoss;
	int8 n_inspire;
	int o_inspirePrac;
};


class SCMD3B7Factory : public MessageFactory
{
	virtual Packet* CreateMessage() {return new SCMD3B7();}

	virtual PacketID_t GetPacketID()const {return WMSG_WORLD_RESULT_CLIMB_TOWER;}

	virtual uint32 GetMessageMaxSize()const {return 0;}

};


class SCMD3B7Handler 
{
public:
	static uint32 Execute(SCMD3B7 *pPacket) ;
};

#endif
