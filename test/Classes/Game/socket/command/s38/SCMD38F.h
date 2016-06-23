#ifndef _SCMD38F_H_
#define _SCMD38F_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "SCMD38FNode.h"

class SCMD38F : public Packet
{
public:
	SCMD38F()
	{

	}

	virtual ~SCMD38F() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_ACTIVITY_INFO_RES;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	std::list<SCMD38FNode> _arr;
};


class SCMD38FFactory: public MessageFactory
{
public :

	virtual ~SCMD38FFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD38F();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_ACTIVITY_INFO_RES;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD38FHandler 
{
public:
	static uint32 Execute(SCMD38F* pPacket) ;
};

#endif