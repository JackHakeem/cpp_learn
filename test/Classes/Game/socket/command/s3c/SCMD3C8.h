#ifndef _SCMD3C8_H_
#define _SCMD3C8_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD3C8 : public Packet
{
public:
	SCMD3C8() {}
	virtual ~SCMD3C8() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_REQ_TRIAL_VIP;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	int8 a_isTrialVip;
	int32 b_endTime;

};


class SCMD3C8Factory: public MessageFactory
{
public :

	virtual ~SCMD3C8Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD3C8();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_REQ_TRIAL_VIP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD3C8Handler 
{
public:
	static uint32 Execute(SCMD3C8* pPacket) ;
};

#endif 