/**
 *服务端返回购买结果
WMSG_WORLD_ BUY_IDENTIFY_POS = 0x2A1 	(673)
服务端->客户端, 包结构
Uint8 		是否成功，1：成功，0，失败;
Uint8        购买后的格子数,失败为0 
 */
#ifndef _SCMD2A1_H_
#define _SCMD2A1_H_

#include "../../network/Packet.h"
#include "../../message/MessageFactory.h"
#include "../../message/SocketCMDConst.h"

class SCMD2A1 : public Packet
{
public:
	SCMD2A1() {}
	virtual ~SCMD2A1() {}


	virtual bool Read();
public :
	virtual int32 Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_BUY_IDENTIFY_POS;}

	virtual	int32 GetMessageSize( ) const { return 0;}

public:
	uint8 a_isSuc;
	uint8 b_gridNum;
};


class SCMD2A1Factory: public MessageFactory
{
public :
	virtual ~SCMD2A1Factory ()  {}

	virtual Packet* CreateMessage () {return new SCMD2A1();}

	virtual PacketID_t GetPacketID ()const  {return WMSG_WORLD_BUY_IDENTIFY_POS;}

	virtual uint32 GetMessageMaxSize ()const  {return 0;}

};

class SCMD2A1Handler 
{
public:
	static uint32 Execute(SCMD2A1* pPacket) ;
};
#endif