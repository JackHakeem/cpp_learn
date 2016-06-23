/**
 * 银矿战令牌使用结果	
WMSG_SILVERMINE_TOKEN_RES = 0x2EF 
服务端->客户端, 包结构
	Uint8		令牌ID
	Uint32		目标银矿ID
	Uint8		令牌执行结果（0：成功；非零：失败）
	Uint32		返回参数（只对查令牌有用，返回目标银矿的玩家数）
 */
#ifndef _SCMD2EF_H_
#define _SCMD2EF_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD2EF : public Packet
{
public:
	SCMD2EF() {}
	virtual ~SCMD2EF() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_SILVERMINE_TOKEN_RES;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_type;
	uint32 b_mineID;
	int8 c_ret;
	uint32 d_param;
};


class SCMD2EFFactory: public MessageFactory
{
public :

	virtual ~SCMD2EFFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2EF();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_SILVERMINE_TOKEN_RES;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2EFHandler 
{
public:
	static uint32 Execute(SCMD2EF* pPacket) ;
};

#endif