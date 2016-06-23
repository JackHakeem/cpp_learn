#ifndef  _SCMD18E_H__
#define  _SCMD18E_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/** 
WMSG_UPDATE_PRACTICE = 0x18e
*/ 

class SCMD18E : public Packet
{
public:
	SCMD18E() {}
	virtual ~SCMD18E() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_UPDATE_PRACTICE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:		 
	int32 a_newvalue;
	int32 b_diffvalue;
	uint8 c_isShow;
};


class SCMD18EFactory: public MessageFactory
{
public :

	virtual ~SCMD18EFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD18E();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_UPDATE_PRACTICE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD18EHandler 
{
public:
	static uint32 Execute(SCMD18E* pPacket) ;
};
#endif