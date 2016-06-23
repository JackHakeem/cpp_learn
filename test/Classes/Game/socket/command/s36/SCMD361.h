#ifndef _SCMD361_H_
#define _SCMD361_H_

	/**
		返回玩家竞技场信息
		WMSG_WORLD_QUALIFYING_INFO = 0x361(865),
		服务端->客户端, 包结构
		Uint8		玩家状态（0：可挑战，1：待翻牌）
		Uint32		当前排名（0~999）
		Uint32		最高排名
		Uint32		连胜数
		Uint32		竞技挑战CD时间
		Uint32		竞技对手刷新CD时间
		Uint32		今日可挑战次数
		Uint32      竞技令购买价格
		Uint32      今天已购买次数		
		可挑战玩家数组：
			Uint32	排位
			Uint32  玩家账号ID
			string	姓名
			Uint32	等级
			Uint16	主角原型id
		最近翻牌挑战结果数组：
			Int8	战斗结果（<0:失败，>0胜利）
		最近5场战报数组：
			Uint32	战斗时间
			String	对手姓名
			Uint8	进攻方（0：本人进攻，1：本人防守）
			int8	本人胜负情况（小于0失败，大于0胜利）
			int8	本人排位情况（小于0下降，等于0不变，大于0上升）
			uint64	战报ID
	*/

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "SCMD361Node.h"
#include "SCMD361Node2.h"

class SCMD361 : public Packet
{
public:
	SCMD361()
	{
		a_state = 0;
		b_rank = 0;
		c_maxRank = 0;
		d_winstreak = 0;
		e_cd = 0;
		l_refreshcd = 0; //hwj
		f_quota = 0;
		g_price = 0;
		h_buyed = 0;		
	}

	virtual ~SCMD361() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_QUALIFYING_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_state;
	uint32 b_rank;
	uint32 c_maxRank;
	uint32 d_winstreak;
	uint32 e_cd;
	uint32 l_refreshcd;
	uint32 f_quota;
	uint32 g_price;
	uint32 h_buyed;
	

	std::vector<SCMD361Node> i_challengeArr;
	std::vector<int> j_resultArr;
	std::vector<SCMD361Node2> k_reportArr;
};


class SCMD361Factory: public MessageFactory
{
public :

	virtual ~SCMD361Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD361();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_QUALIFYING_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD361Handler 
{
public:
	static uint32 Execute(SCMD361* pPacket) ;
};

#endif