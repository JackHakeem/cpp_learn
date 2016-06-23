#ifndef _SCMD36E_H_
#define _SCMD36E_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "SCMD36ENode.h"

class SCMD36E : public Packet
{
public:
	SCMD36E()
	{
	}

	virtual ~SCMD36E() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_QUALIFYING_AWARD_RES;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_result;
	int8 b_id;
	std::vector<SCMD36ENode> c_rewards;
};


class SCMD36EFactory: public MessageFactory
{
public :

	virtual ~SCMD36EFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD36E();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_QUALIFYING_AWARD_RES;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD36EHandler 
{
public:
	static uint32 Execute(SCMD36E* pPacket) ;
};

#endif