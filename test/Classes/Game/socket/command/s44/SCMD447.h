/**
 
 */
#ifndef _SCMD447_H_
#define _SCMD447_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD447 : public Packet
{
public:
	SCMD447() {
		a_gongActive = 0;
	}
	virtual ~SCMD447() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_GONG_ISIN;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:


	uint8 a_gongActive;
};


class SCMD447Factory: public MessageFactory
{
public :

	virtual ~SCMD447Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD447();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_GONG_ISIN;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD447Handler 
{
public:
	static uint32 Execute(SCMD447* pPacket) ;
};

#endif