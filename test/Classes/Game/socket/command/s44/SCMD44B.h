/**
 
 */
#ifndef _SCMD44B_H_
#define _SCMD44B_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD44B : public Packet
{
public:
	SCMD44B() {
	}
	virtual ~SCMD44B() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_GONG_UPDATE_EXPBUFF;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:


	int32 a_gongExpBuffCount;
};


class SCMD44BFactory: public MessageFactory
{
public :

	virtual ~SCMD44BFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD44B();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_GONG_UPDATE_EXPBUFF;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD44BHandler 
{
public:
	static uint32 Execute(SCMD44B* pPacket) ;
};

#endif