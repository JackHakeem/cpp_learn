/** 
 * @author shenzhiqiang
 * @version 1.1.7.0
 * @description 服务端返回-获蛋历史记录
WMSG_EGG_HISTORY = 0x401
服务端 -> 客户端, 包结构:
Uint8		许愿币个数
Uint16		个人记录数
	Uint8	蛋类(1装备蛋/2佣兵蛋/3资源蛋)
	Uint8	品质(1小/2大/3蓝色/4紫色/5橙色/6红色)
	Uint8	状态(1已开/2未开)
	Uint32	内容ID(比如装备ID,佣兵ID,物品ID)
	Uint32	内容数量(装备数量,佣兵数量,物品数量)
	Uint32	蛋数
Uint16		其他玩家记录数
	String	玩家名字
	Uint8	蛋类(1装备蛋/2佣兵蛋/3资源蛋)
	Uint8	品质(1小/2大/3蓝色/4紫色/5橙色/6红色)
	Uint8	状态(1已开/2未开)
	Uint32	内容ID(比如装备ID,佣兵ID,物品ID)
	Uint32	内容数量(装备数量,佣兵数量,物品数量)
	Uint32	蛋数

 * @data 2012-3-26 上午11:57:53 
 * 
 */ 
#ifndef _SCMD401_H_
#define _SCMD401_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "./SCMD401Node1.h"
#include "./SCMD401Node2.h"

class SCMD401 : public Packet
{
public:
	SCMD401()
	{
	}

	virtual ~SCMD401() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_EGG_HISTORY;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_num;
	std::vector<SCMD401Node1> b_myReward;
	std::vector<SCMD401Node2> c_otherReward;
};


class SCMD401Factory: public MessageFactory
{
public :
	
	virtual ~SCMD401Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD401();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_EGG_HISTORY;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD401Handler 
{
public:
	static uint32 Execute(SCMD401* pPacket) ;
};

#endif