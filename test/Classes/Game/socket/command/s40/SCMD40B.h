/** 
 * @author shenzhiqiang
 * @version 1.1.7.0
 * @description 服务端返回-仓库
WMSG_EGG_DEPOT = 0x40B
服务端 ->客户端, 包结构:
Uint16		蛋数
	Uint8	蛋类(1装备蛋/2佣兵蛋/3资源蛋)
	Uint8	品质(1小/2大/3蓝色/4紫色/5橙色/6红色)
	Uint8	状态(1已开/2未开)
	Uint32	内容ID(比如装备ID,佣兵ID,物品ID)
	Uint32	内容数量(装备数量,佣兵数量,物品数量)
	Uint32	堆叠数

 * @data 2012-3-26 上午11:58:42 
 * 
 */ 
#ifndef _SCMD40B_H_
#define _SCMD40B_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "SCMD40BNode.h"

class SCMD40B : public Packet
{
public:
	SCMD40B()
	{
	}

	virtual ~SCMD40B() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_EGG_DEPOT;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	std::vector<SCMD40BNode> a_eggs;
};


class SCMD40BFactory: public MessageFactory
{
public :
	
	virtual ~SCMD40BFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD40B();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_EGG_DEPOT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD40BHandler 
{
public:
	static uint32 Execute(SCMD40B* pPacket) ;
};

#endif