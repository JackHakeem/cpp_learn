#ifndef _SCMD109_H__
#define _SCMD109_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD109 : public Packet
{
public:
	SCMD109() {}
	virtual ~SCMD109() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_TIME_BROADCAST;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:		 
	uint a_time;
};


class SCMD109Factory: public MessageFactory
{
public :

	virtual ~SCMD109Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD109();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_TIME_BROADCAST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD109Handler 
{
public:
	static uint32 Execute(SCMD109* pPacket) ;
};
#endif