#ifndef _SCMD28F_H_
#define _SCMD28F_H_

#include "../../network/Packet.h"
#include "../../message/MessageFactory.h"
#include "../../message/SocketCMDConst.h"

class SCMD28F : public Packet
{
public:
	SCMD28F() {}
	virtual ~SCMD28F() {}


	virtual bool Read();
public :
	virtual int32 Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_TRADE_ROB_INFO;}

	virtual	int32 GetMessageSize( ) const { return 0;}

public:
	int32 a_sil;
	int32 b_pop;
	int16 c_beated;
	uint8 d_BuyTokenCnt;
};


class SCMD28FFactory: public MessageFactory
{
public :
	virtual ~SCMD28FFactory ()  {}

	virtual Packet* CreateMessage () {return new SCMD28F();}

	virtual PacketID_t GetPacketID ()const  {return WMSG_WORLD_TRADE_ROB_INFO;}

	virtual uint32 GetMessageMaxSize ()const  {return 0;}

};

class SCMD28FHandler 
{
public:
	static uint32 Execute(SCMD28F* pPacket) ;
};
#endif