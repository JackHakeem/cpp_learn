/**
 * 银矿战鼓舞使用结果	
WMSG_SILVERMINE_INSPIRE_RES = 0x369 
服务端->客户端, 包结构
Uint8		鼓舞类型
Uint8		执行结果
Uint32		当前攻击鼓舞加成百分比
Uint32		当前防守鼓舞加成百分比
 */
#ifndef _SCMD369_H_
#define _SCMD369_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD369 : public Packet
{
public:
	SCMD369()
	{

	}

	virtual ~SCMD369() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_SILVERMINE_INSPIRE_RES;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_type;
	int8 b_ret;
	uint32 c_attPlus;
	uint32 d_defPlus;
};


class SCMD369Factory: public MessageFactory
{
public :

	virtual ~SCMD369Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD369();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_SILVERMINE_INSPIRE_RES;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD369Handler 
{
public:
	static uint32 Execute(SCMD369* pPacket) ;
};

#endif