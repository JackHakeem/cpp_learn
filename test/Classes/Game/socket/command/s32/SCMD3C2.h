#ifndef _SCMD3C2_H_
#define _SCMD3C2_H_

/*
packet << pTwrNLCrtDrp->m_nCrateDropID;
packet << addnum;
res返回值的含义
	0:成功
	1：上一期没有留名
	2：已经领取过奖励
	3：该层不发放留名奖励
	4：玩家背包空格数不够放宝箱
	5：其他
	*/

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD3C2 : public Packet
{
public:
	SCMD3C2() {}
	virtual ~SCMD3C2() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_SEND_TOWER_GIFT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int32 a_isSuccess;	//m_nCrateDropID
	int8 b_type;	//addnum
	int8 c_resultNo;
};


class SCMD3C2Factory: public MessageFactory
{
public :

	virtual ~SCMD3C2Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD3C2();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_SEND_TOWER_GIFT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD3C2Handler 
{
public:
	static uint32 Execute(SCMD3C2* pPacket) ;
};

#endif