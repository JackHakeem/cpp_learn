#ifndef _SCMD15A_H_
#define _SCMD15A_H_
#include "socket/network/Packet.h"
#include "socket/message/MessageFactory.h"
#include "socket/message/SocketCMDConst.h"

class SCMD15A : public Packet
{
public:
	SCMD15A(){}
	~SCMD15A(){}

	int16 _id;
	int8 _succ;

	virtual int32 Execute();

	virtual bool Read();

	virtual PacketID_t getPacketID()const { return WMSG_WORLD_SUBMIT_TASK;}
	
};


class SCMD15AFactory : public MessageFactory
{
	virtual Packet* CreateMessage() {return new SCMD15A();}

	virtual PacketID_t GetPacketID()const {return WMSG_WORLD_SUBMIT_TASK;}

	virtual uint32 GetMessageMaxSize()const {return 0;}

};


class SCMD15AHandler 
{
public:
	static uint32 Execute(SCMD15A *pPacket) ;
};

#endif