#ifndef _SCMD108_H__
#define _SCMD108_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD108 : public Packet
{
public:
	SCMD108() {}
	virtual ~SCMD108() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return XMSG_ERROR_RESPONSE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:		
	int16 a_errCode;
};


class SCMD108Factory: public MessageFactory
{
public :

	virtual ~SCMD108Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD108();}

	virtual PacketID_t	GetPacketID ()const  {return XMSG_ERROR_RESPONSE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD108Handler 
{
public:
	static uint32 Execute(SCMD108* pPacket) ;
};
#endif