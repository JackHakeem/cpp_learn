/**
 
 */
#ifndef _SCMD444_H_
#define _SCMD444_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD444 : public Packet
{
public:
	SCMD444() {
		a_show = 0;
	}
	virtual ~SCMD444() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_GONG_SHOW_MONSTER;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint8 a_show;
};


class SCMD444Factory: public MessageFactory
{
public :

	virtual ~SCMD444Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD444();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_GONG_SHOW_MONSTER;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD444Handler 
{
public:
	static uint32 Execute(SCMD444* pPacket) ;
};

#endif