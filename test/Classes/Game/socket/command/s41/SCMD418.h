/**
 */

#ifndef _SCMD418_H_
#define _SCMD418_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD418 : public Packet
{
public:

	SCMD418()
	{
		a_flag = 0;
	}

	virtual ~SCMD418() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_DUNGEON_GUA_MSG;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint32 a_flag;
};


class SCMD418Factory: public MessageFactory
{
public :
	
	virtual ~SCMD418Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD418();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_DUNGEON_GUA_MSG;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD418Handler 
{
public:
	static uint32 Execute(SCMD418* pPacket) ;
};

#endif