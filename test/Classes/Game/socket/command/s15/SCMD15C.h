#ifndef _SCMD15C_H_
#define _SCMD15C_H_
#include "socket/network/Packet.h"
#include "socket/message/MessageFactory.h"
#include "socket/message/SocketCMDConst.h"

/**
Abandon the mission to return the package
* WMSG_WORLD_GIVE_UP _TASK = 0x15C (348),
* Server -> client package structure
* Short: Task ID
* Byte: success (a success)
 */
class SCMD15C : public Packet
{
public:
	SCMD15C(){}
	~SCMD15C(){}

	int16 _id;
	int8 _succ;

	virtual int32 Execute();

	virtual bool Read();

	virtual PacketID_t getPacketID()const { return WMSG_WORLD_GIVE_UP_TASK;}

};


class SCMD15CFactory : public MessageFactory
{
	virtual Packet* CreateMessage() {return new SCMD15C();}

	virtual PacketID_t GetPacketID()const {return WMSG_WORLD_GIVE_UP_TASK;}

	virtual uint32 GetMessageMaxSize()const {return 0;}

};


class SCMD15CHandler 
{
public:
	static uint32 Execute(SCMD15C *pPacket) ;
};


#endif