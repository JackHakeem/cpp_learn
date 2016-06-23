#ifndef _SCMD16F_H_
#define _SCMD16F_H_

/**
*code： 0x16F；
* S -> C；
* Int8: pos type
* Int8: jutiweizhi
* uint: figure id
* int8: streng lev
* 
*/	

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD16F : public Packet
{
public:
	SCMD16F() {}
	virtual ~SCMD16F() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_ITEM_INFO;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_locationType;	//位置类型
	int8 b_sitNum;			//具体位置
	uint c_roleId;			//角色id
	int8 d_strength;		//强化等级		
	int16 e_stamina;		//魔化体格数
	int16 f_wrist;			//魔化腕力数
	int16 g_intellect;		//魔化智力数
};


class SCMD16FFactory: public MessageFactory
{
public :
	
	virtual ~SCMD16FFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD16F();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_ITEM_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD16FHandler 
{
public:
	static uint32 Execute(SCMD16F* pPacket) ;
};

#endif 