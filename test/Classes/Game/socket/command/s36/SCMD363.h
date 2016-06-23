#ifndef _SCMD363_H_
#define _SCMD363_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD363 : public Packet
{
public:
	SCMD363()
	{

	}

	virtual ~SCMD363() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_QUALIFYING_CHALLENGE_RES;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint32 a_rank;
	int8 b_result;
};


class SCMD363Factory: public MessageFactory
{
public :

	virtual ~SCMD363Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD363();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_QUALIFYING_CHALLENGE_RES;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD363Handler 
{
public:
	static uint32 Execute(SCMD363* pPacket) ;
};

#endif