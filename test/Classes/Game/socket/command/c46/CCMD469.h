/**
 * 
星魂面板里移动星魂操作
 */

#ifndef _CCMD469_H_
#define _CCMD469_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD469 : public Packet
{
public:
	CCMD469() 
	{
		a_fromPosType = 0;
		b_fromPos= 0;
		c_toPosType= 0;
		d_toPos= 0;
		e_roldId = 0;
	}

	virtual ~CCMD469() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_ZX_XH_MOVE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	/*
	enum 包裹类型
	{
		XH_POS_16 = 1,背包
		XH_POS_8 = 3, 装备
	};
	*/
	int8 a_fromPosType; //从包裹类型（enum 包裹类型：注意枚举值）
	int8 b_fromPos;		//从哪个位置
	int8 c_toPosType;	//移动到包裹类型（enum 包裹类型：注意枚举值）
	int8 d_toPos;		//移动到位置
	uint32 e_roldId;	//佣兵ID（如果有涉及到装备栏的移动需要写，否则填0）
};


class CCMD469Factory: public MessageFactory
{
public :

	virtual ~CCMD469Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_ZX_XH_MOVE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif