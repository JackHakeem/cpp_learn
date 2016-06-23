#ifndef  _SCMD18F_H__
#define  _SCMD18F_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/** 
WMSG_UPDATE_POPULARITY = 0x18f
*/ 

class SCMD18F : public Packet
{
public:
	SCMD18F() {}
	virtual ~SCMD18F() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_UPDATE_POPULARITY;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:		 
	int32 a_newvalue;
	int32 b_diffvalue;
	uint8 c_isShow;
};


class SCMD18FFactory: public MessageFactory
{
public :

	virtual ~SCMD18FFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD18F();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_UPDATE_POPULARITY;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD18FHandler 
{
public:
	static uint32 Execute(SCMD18F* pPacket) ;
};
#endif