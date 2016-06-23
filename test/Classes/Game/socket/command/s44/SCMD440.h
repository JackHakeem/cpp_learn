/**
 */

#ifndef _SCMD440_H_
#define _SCMD440_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD440 : public Packet
{
public:

	SCMD440()
	{
		a_flag = 0;
	}

	virtual ~SCMD440() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_GONG_MSG;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint32 a_flag;
};


class SCMD440Factory: public MessageFactory
{
public :
	
	virtual ~SCMD440Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD440();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_GONG_MSG;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD440Handler 
{
public:
	static uint32 Execute(SCMD440* pPacket) ;
};

#endif