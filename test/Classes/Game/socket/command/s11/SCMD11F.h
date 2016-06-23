/**
* WMSG_WORLD_FOLLOW_PROCESS 	= 0x11F(287),				// 战斗后续进度触发
服务端->客户端, 包结构
byte:		事件类型:1对话,    2动画 3 战斗
short:		相关编号:对话Id    动画Id
 */

#ifndef _SCMD11F_H_
#define _SCMD11F_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD11F : public Packet
{
public:
	SCMD11F()
	{
        a_type = 0;
        b_id = 0;
	}

	virtual ~SCMD11F() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_FOLLOW_PROCESS;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint8 a_type;
	uint16 b_id;
};


class SCMD11FFactory: public MessageFactory
{
public :
	
	virtual ~SCMD11FFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD11F();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_FOLLOW_PROCESS;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD11FHandler 
{
public:
	static uint32 Execute(SCMD11F* pPacket) ;
};

#endif