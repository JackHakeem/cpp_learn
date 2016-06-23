#ifndef _SCMD411_H__
#define _SCMD411_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD411 : public Packet
{
public:
	SCMD411() {}
	virtual ~SCMD411() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_DUNGEON_GUA;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:	
	uint16 a_dunId;
};


class SCMD411Factory: public MessageFactory
{
public :

	virtual ~SCMD411Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD411();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_DUNGEON_GUA;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD411Handler 
{
public:
	static uint32 Execute(SCMD411* pPacket) ;
};
#endif