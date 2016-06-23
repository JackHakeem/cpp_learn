/**
 * 请求进入银矿战地图结果	
WMSG_SILVERMINE_ENTER_RES = 0x2E3 
服务端->客户端, 包结构
int8	进入结果
    0：进入成功，分配阵营ID：0
    1：进入成功，分配阵营ID：1
    2：进入成功，分配阵营ID：2
    -1：进入失败，水晶等级未达到
    -2：进入失败，当前不在银矿战时间内
    -3：进入失败，银矿战人数满
    -4：进入失败，系统错误
 */

#ifndef _SCMD2E3_H_
#define _SCMD2E3_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD2E3 : public Packet
{
public:
	SCMD2E3() {}
	virtual ~SCMD2E3() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_SILVERMINE_ENTER_RES;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	int8 a_ret;
};


class SCMD2E3Factory: public MessageFactory
{
public :

	virtual ~SCMD2E3Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2E3();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_SILVERMINE_ENTER_RES;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2E3Handler 
{
public:
	static uint32 Execute(SCMD2E3* pPacket) ;
};

#endif