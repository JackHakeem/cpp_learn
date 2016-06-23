/**
 *WMSG_WORLD_BUY_VIGOUR_INFO_RESP = 0x21F (543)
客户端->服务端, 包结构
Int16:		所需金币
Int16:		精力数量
 
 */

#ifndef _SCMD21F_H_
#define _SCMD21F_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD21F : public Packet
{
public:
	SCMD21F() {}
	virtual ~SCMD21F() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_BUY_VIGOUR_INFO_RESP;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint16 a_gold;
	uint16 b_energy;
};


class SCMD21FFactory: public MessageFactory
{
public :
	
	virtual ~SCMD21FFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD21F();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_BUY_VIGOUR_INFO_RESP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD21FHandler 
{
public:
	static uint32 Execute(SCMD21F* pPacket) ;
};

#endif 