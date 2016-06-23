#ifndef _SCMD19A_H__
#define _SCMD19A_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
	系统广播
	WMSG_COMMU_SYS_BROADCAST = 0x19A(410),			//系统广播
	服务端->客户端, 包结构
	Byte:		广播类型		//  1 – 成就
									2 – 使命
									3 – 物品
									4 – 竞技场连胜
									6  - 紫色或以上物品掉落(包括碎片)
									7  - 紫色或以上物品合成
									8  - 跑商达成３星事件
									9  - 劫商大暴击
									10 - 通商大暴击
									11 - 首充
									12 - 世界Boss
									13 - 竞技场前10名争夺战
	Int:		玩家ID
	String：	玩家名字
	String：	广播消息  // 格式 ：
			对于成就 ： 成就名字
			对于使命 ： 使命名字
			对于物品 ：(碎片或物品掉落用世界物品编号是否为0来区别)
					1：掉落紫色或以上碎片[帐号ID，物品编号,世界物品编号(为0)，强化等级(为0)];
					2: 掉落紫色或以上物品[帐号ID，物品编号,世界物品编号(不为0)，强化等级(为0)];
					3, 紫色或以上装备合成[帐号ID，物品编号,世界物品编号(不为0)，强化等级(为0)];
			对于竞技场： 连胜场次
			对于跑商: 玩家名字(可以忽略，包里面有)
			对于劫商: 被劫人的名字
			对于通商: 玩家名字(可以忽略，包里面有)
			对于世界BOSS：奖励银币的数量
			对于竞技场前10名争夺战：被打败的玩家名字
 */
class SCMD19A : public Packet
{
public:
	SCMD19A():a_type(0),b_id(0),c_name(""),d_content("") {}
	virtual ~SCMD19A() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_COMMU_SYS_BROADCAST;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:		 
	uint8 a_type;
	int32 b_id;
	std::string c_name;
	std::string d_content;

};


class SCMD19AFactory: public MessageFactory
{
public :

	virtual ~SCMD19AFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD19A();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_COMMU_SYS_BROADCAST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD19AHandler 
{
public:
	static uint32 Execute(SCMD19A* pPacket) ;
};
#endif