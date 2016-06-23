/**
退出战队结果
WMSG_WORLD_GROUPCREATE_RESULT = 0x279 
服务端->客户端, 包结构
Uint16		副本ID
Uint16		战队ID
Uint8		结果码（0：成功；非0：失败，错误码待定）
*/

#ifndef _SCMD279_H_
#define _SCMD279_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD279 : public Packet
{
public:
	SCMD279() {}
	virtual ~SCMD279() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_LEAVEGROUP_RESULT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint16 a_fbId;
	uint16 b_teamId;
	uint8 c_ret;
};


class SCMD279Factory: public MessageFactory
{
public :

	virtual ~SCMD279Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD279();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_LEAVEGROUP_RESULT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD279Handler 
{
public:
	static uint32 Execute(SCMD279* pPacket) ;
};

#endif