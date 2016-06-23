/**
战斗开启结果
WMSG_WORLD_GROUPFIGHT_RESULT = 0x27D 
服务端->客户端, 包结构
Uint16		副本ID
Uint16		战队ID
Uint8		结果码（0：成功；非0：失败，错误码待定）
*/

#ifndef _SCMD27D_H_
#define _SCMD27D_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD27D : public Packet
{
public:
	SCMD27D() {}
	virtual ~SCMD27D() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_GROUPFIGHT_RESULT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint16 a_fbId;
	uint16 b_teamId;
	uint8 c_ret;
};


class SCMD27DFactory: public MessageFactory
{
public :

	virtual ~SCMD27DFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD27D();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_GROUPFIGHT_RESULT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD27DHandler 
{
public:
	static uint32 Execute(SCMD27D* pPacket) ;
};

#endif