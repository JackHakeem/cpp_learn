/**
 *response magic result
WMSG_WORLD_ENCHANT = 0x2D7 （727）
Uint8		魔化是否成功：0，成功；1，失败，低于成功率；2，晶体不够；3，装备不符合要求；4，魔化属性达到上限
Uint8		如果成功则是魔化类型（客户端对应的魔化属性增加1：0，体格；1，腕力；2智力）
Uint32		剩余晶体数
Uint8		强化等级
Uint8       物品所在位置类型（背包/身上）
Uint8 		物品所在位置
Uint32 		物品所属的俑兵ID（在背包则为0） 
 */
#ifndef _SCMD2D7_H_
#define _SCMD2D7_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD2D7 : public Packet
{
public:
	SCMD2D7() {}
	virtual ~SCMD2D7() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_ENCHANT;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_type;
	int8 b_attribute;
	int c_sparNum;
	int8 d_streng;
	int8 e_location;
	int8 f_sit;
	int g_roleId;
};


class SCMD2D7Factory: public MessageFactory
{
public :
	
	virtual ~SCMD2D7Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2D7();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_ENCHANT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2D7Handler 
{
public:
	static uint32 Execute(SCMD2D7* pPacket) ;
};

#endif