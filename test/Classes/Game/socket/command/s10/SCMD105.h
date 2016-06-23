/**
GMSG_CREATE_ACCOUNT = 0x105 
The service -> client package structure:
short: error type
 */

#ifndef _SCMD105_H_
#define _SCMD105_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD105 : public Packet
{
public:
	SCMD105()
	{
		a_result = 0;
	}

	virtual ~SCMD105() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_CREATE_ACCOUNT;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16		a_result;
};


class SCMD105Factory: public MessageFactory
{
public :
	
	virtual ~SCMD105Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD105();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_CREATE_ACCOUNT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD105Handler 
{
public:
	static uint32 Execute(SCMD105* pPacket) ;
};

#endif 