#ifndef  _SCMD18D_H__
#define  _SCMD18D_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/** 
WMSG_UPDATE_GOLD = 0x18d
*/ 

class SCMD18D : public Packet
{
public:
	SCMD18D() {}
	virtual ~SCMD18D() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_UPDATE_GOLD;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:		 
	int32 a_newvalue;
	int32 b_diffvalue;
	uint8 c_isShow;
};


class SCMD18DFactory: public MessageFactory
{
public :

	virtual ~SCMD18DFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD18D();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_UPDATE_GOLD;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD18DHandler 
{
public:
	static uint32 Execute(SCMD18D* pPacket) ;
};
#endif