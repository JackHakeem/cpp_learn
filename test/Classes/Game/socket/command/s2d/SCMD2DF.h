/**
 *服务端返回传承结果
WMSG_WORLD_HERITAGE = 0x2Df
服务端->客户端, 包结构
Uint8	是否传承成功：0，失败；1，成功
Uint8		源物品强化等级
Uint8        源物品所在位置类型（背包/身上）
Uint8 		源物品所在位置
Uint32 		源物品所属的俑兵ID（在背包则为0）

Uint8		目标物品强化等级
Uint8        目标物品物品所在位置类型（背包/身上）
Uint8 		目标物品物品所在位置
Uint32 		目标物品物品所属的俑兵ID（在背包则为0） 
Uint16	目标物品的新魔化体格属性		（如果失败则为0）
Uint16	目标物品的新魔化腕力属性		（如果失败则为0）
Uint16	目标物品的新魔化智力属性		（如果失败则为0）
 */
#ifndef _SCMD2DF_H_
#define _SCMD2DF_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD2DF : public Packet
{
public:
	SCMD2DF() {}
	virtual ~SCMD2DF() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_HERITAGE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_type;
	int8 b_streng;
	int8 c_location;
	int8 d_sit;
	int e_roleId;
	int8 f_streng;
	int8 g_location;
	int8 h_sit;
	int i_roleId;
	int16 j_stamina;
	int16 k_wrist;
	int16 l_intellect;
};


class SCMD2DFFactory: public MessageFactory
{
public :
	
	virtual ~SCMD2DFFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2DF();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_HERITAGE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2DFHandler 
{
public:
	static uint32 Execute(SCMD2DF* pPacket) ;
};

#endif