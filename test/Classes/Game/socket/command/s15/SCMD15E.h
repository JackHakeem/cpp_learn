#ifndef _SCMD15E_H_
#define _SCMD15E_H_
#include "socket/network/Packet.h"
#include "socket/message/MessageFactory.h"
#include "socket/message/SocketCMDConst.h"
/**
* WMSG_WORLD_REFRESH_TASK = 0x15E (350),
* Server -> client package structure
* Byte: success (a success)
 */
class SCMD15E : public Packet
{
public:
	SCMD15E(){}
	~SCMD15E(){}

	int8 _succ;

	virtual int32 Execute();

	virtual bool Read();

	virtual PacketID_t getPacketID()const { return WMSG_WORLD_REFRESH_TASK;}

};


class SCMD15EFactory : public MessageFactory
{
	virtual Packet* CreateMessage() {return new SCMD15E();}

	virtual PacketID_t GetPacketID()const {return WMSG_WORLD_REFRESH_TASK;}

	virtual uint32 GetMessageMaxSize()const {return 0;}

};


class SCMD15EHandler 
{
public:
	static uint32 Execute(SCMD15E *pPacket) ;
};


#endif