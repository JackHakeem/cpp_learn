#ifndef _SCMD41F_H_
#define _SCMD41F_H_
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD41F : public Packet
{
public:
	SCMD41F() {}
	virtual ~SCMD41F() {}


	virtual bool	Read();
public :
	virtual int32 	Execute(); 

	virtual PacketID_t getPacketID() const { return WMSG_NETWORK_DELAY_RES;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_res;
};


class SCMD41FFactory: public MessageFactory
{
public :

	virtual ~SCMD41FFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD41F();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_NETWORK_DELAY_RES;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD41FHandler 
{
public:
	static uint32 Execute(SCMD41F* pPacket) ;
};

#endif