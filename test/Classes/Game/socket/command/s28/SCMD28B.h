#ifndef _SCMD28B_H__
#define _SCMD28B_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
	英雄榜广播	
	WMSG_WORLD_HERO_BROADCAST = 0x28B 
	服务端->客户端, 包结构
	英雄榜数组（0~2）（第0个是第一名，以此类推）
	    Uint32	玩家ID
	    String	第一名玩家主角名
	   
	注：数组长度有可能小于3”
 */

class SCMD28B : public Packet
{
public:
	SCMD28B() {}
	virtual ~SCMD28B() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_HERO_BROADCAST;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	struct SCMD28BNode
	{
		int32 a_id;
		std::string b_name;
	};
	std::list<SCMD28BNode> heros;
};

class SCMD28BFactory: public MessageFactory
{
public :

	virtual ~SCMD28BFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD28B();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_HERO_BROADCAST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD28BHandler 
{
public:
	static uint32 Execute(SCMD28B* pPacket) ;
};
#endif