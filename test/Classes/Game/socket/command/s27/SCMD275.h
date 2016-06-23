/**
新建战队结果
WMSG_WORLD_GROUPCREATE_RESULT = 0x275 
服务端->客户端, 包结构
Uint16		副本ID
Uint8		结果码（0：成功；非0：失败，错误码待定）
Uint16		战队ID
*/

#ifndef _SCMD275_H_
#define _SCMD275_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD275 : public Packet
{
public:
	SCMD275() {}
	virtual ~SCMD275() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_GROUPCREATE_RESULT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint16 a_fbId;
	uint8 b_ret;
	uint16 c_teamId;
};


class SCMD275Factory: public MessageFactory
{
public :

	virtual ~SCMD275Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD275();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_GROUPCREATE_RESULT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD275Handler 
{
public:
	static uint32 Execute(SCMD275* pPacket) ;
};

#endif