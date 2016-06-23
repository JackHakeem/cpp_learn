/*
Update gold sum.
WMSG_WORLD_UPDATE_GOLDSUM = 0x1EE (494)
int32 nowCount
int32 addCount
*/

#ifndef _SCMD1EE_H_
#define _SCMD1EE_H_
#include "../../network/Packet.h"
#include "../../message/MessageFactory.h"
#include "../../message/SocketCMDConst.h"

class SCMD1EE : public Packet
{
public:
	SCMD1EE() {}
	virtual ~SCMD1EE() {}


	virtual bool Read();
public :
	virtual int32 Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_UPDATE_GOLDSUM;}

	virtual	int32 GetMessageSize( ) const { return 0;}

public:
	int32 a_presentValue;
	int32 b_addValue;
};


class SCMD1EEFactory: public MessageFactory
{
public :
	virtual ~SCMD1EEFactory ()  {}

	virtual Packet* CreateMessage () {return new SCMD1EE();}

	virtual PacketID_t GetPacketID ()const  {return WMSG_WORLD_UPDATE_GOLDSUM;}

	virtual uint32 GetMessageMaxSize ()const  {return 0;}

};

class SCMD1EEHandler 
{
public:
	static uint32 Execute(SCMD1EE* pPacket) ;
};
#endif