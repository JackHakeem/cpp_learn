/**服务器回应征收结果包
WMSG_WORLD_IMPOSE_RESULT = 0x321,(801)
byte		征收成功标识：0，成功；1，CD中(在征收前最好客户端判断)；2，剩余征收次数为零（客户端也可以在征收前判断）；3，不够金币征收（强征）；4，征收后超过最大银币上限；5，征收后超过金币上限。
Byte		征收类型：1，普通征收；2，强制征收
Uint16      下一次强征所需金币
Uint16 		普通征收剩余次数；（看征收类型，如果是强制征收就是强征次数）
byte		普通征收次数限制；（看征收类型，如果是强制征收就是0）
uint16		金币征收次数
byte		征收以外获得金币数目
uint32		征收后银币总量，征收失败为 0；
uint32		征收后金币总量，征收失败为 0；
uint16 		公会科技等级
uint16 		每周目标星星数
**/

#ifndef _SCMD321_H_
#define _SCMD321_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD321 : public Packet
{
public:
	SCMD321() {}
	virtual ~SCMD321() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_IMPOSE_RESULT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_isSuccess;
	int8 b_type;
	uint16 c_levyCost;
	uint16 d_rest;
	int8 e_limit;
	int8 h_luckyGold;
	uint32 i_silver;
	uint32 j_gold;
	uint16 k_uniteLev;
	uint16 l_starNum;
};


class SCMD321Factory: public MessageFactory
{
public :

	virtual ~SCMD321Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD321();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_IMPOSE_RESULT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD321Handler 
{
public:
	static uint32 Execute(SCMD321* pPacket) ;
};

#endif