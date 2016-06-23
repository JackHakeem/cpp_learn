#ifndef _SCMD366_H_
#define _SCMD366_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD366 : public Packet
{
public:
	SCMD366()
	{
		a_isSucess = 0;
		b_arenaType = 0;
	}

	virtual ~SCMD366() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_PVP_CHALLENGE_RETURN;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_isSucess;
	int8 b_arenaType;
};


class SCMD366Factory: public MessageFactory
{
public :

	virtual ~SCMD366Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD366();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_PVP_CHALLENGE_RETURN;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD366Handler 
{
public:
	static uint32 Execute(SCMD366* pPacket) ;
};

#endif