/**
 * 银矿战信息更新	
WMSG_SILVERMINE_INFO = 0x2E6 
服务端->客户端, 包结构
uint8	当前是否在银矿战时间（0：不是；1：是）
uint32		行动CD时间结束
uint8		行动是否CD中（0：不是；1：是）
uint32		采矿CD时间
uint8		采矿是否CD中（0：不是；1：是）
uint32		当前所在银矿ID
uint32		当前所在银矿人数
Uint32		当前攻击鼓舞加成百分比
Uint32		当前防守鼓舞加成百分比
Uint8		令牌0类型
Uint8		令牌1类型
uint32      我所挖银币数 
银矿阵营信息数组：
	Uint32	银矿ID
	Uint32  当前玩家数 
	int8	当前占领阵营ID（-1：空矿；0~2：阵营ID）
	uint8	是否双倍矿（0：否；1：是）
	 * 
	 * 
 */
#ifndef _SCMD2E6_H_
#define _SCMD2E6_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "SCMD2E6Node.h"

class SCMD2E6 : public Packet
{
public:
	SCMD2E6() {}
	virtual ~SCMD2E6() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_SILVERMINE_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	int8 a_intime;
	uint32 b_actionCD;
	int8 c_inActionCD;
	uint32 d_digCD;
	int8 e_inDigCD;
	uint32 f_mineId;
	uint32 g_onMine;
	uint32 h_attPlus;
	uint32 i_defPlus;
	int8 j_token0;
	int8 k_token1;
	uint32 l_silver;
 	int8 m_mojinshi;
	std::list<SCMD2E6Node> m_mineArr;

};


class SCMD2E6Factory: public MessageFactory
{
public :

	virtual ~SCMD2E6Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2E6();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_SILVERMINE_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2E6Handler 
{
public:
	static uint32 Execute(SCMD2E6* pPacket) ;
};

#endif