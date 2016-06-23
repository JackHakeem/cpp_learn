#ifndef _SCMD3B1_H_
#define _SCMD3B1_H_
#include "socket/network/Packet.h"
#include "socket/message/MessageFactory.h"
#include "socket/message/SocketCMDConst.h"

class SCMD3B1 : public Packet
{
public:
	SCMD3B1(){}
	~SCMD3B1(){}

	virtual int32 Execute();

	virtual bool Read();

	virtual PacketID_t getPacketID()const { return WMSG_REQUEST_BATTLE_REPORT;}

public:
	uint _battleId1; // int64 part 1
	uint _battleId2; // int64 part 2
};


class SCMD3B1Factory : public MessageFactory
{
	virtual Packet* CreateMessage() {return new SCMD3B1();}

	virtual PacketID_t GetPacketID()const {return WMSG_REQUEST_BATTLE_REPORT;}

	virtual uint32 GetMessageMaxSize()const {return 0;}

};


class SCMD3B1Handler 
{
public:
	static uint32 Execute(SCMD3B1 *pPacket) ;
};

#endif
