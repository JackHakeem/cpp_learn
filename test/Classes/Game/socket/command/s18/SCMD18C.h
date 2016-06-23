#ifndef  _SCMD18C_H__
#define  _SCMD18C_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/** 
WMSG_UPDATE_SILVER = 0x18c
*/ 

class SCMD18C : public Packet
{
public:
	SCMD18C() {}
	virtual ~SCMD18C() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_UPDATE_SILVER;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:		 
	int32 a_newvalue;
	int32 b_diffvalue;
	uint8 c_isShow;
};


class SCMD18CFactory: public MessageFactory
{
public :

	virtual ~SCMD18CFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD18C();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_UPDATE_SILVER;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD18CHandler 
{
public:
	static uint32 Execute(SCMD18C* pPacket) ;
};
#endif