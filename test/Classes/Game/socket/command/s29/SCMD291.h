/**
WMSG_REP_CAN_HIRE_MAX_MER_NUM = 0x291 (657)
byte
*/

#ifndef _SCMD291_H_
#define _SCMD291_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD291 : public Packet
{
public:
	SCMD291() {}
	virtual ~SCMD291() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return SMSG_LOGIN_RESPONSE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8	a_mercLim;
};


class SCMD291Factory: public MessageFactory
{
public :
	
	virtual ~SCMD291Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD291();}

	virtual PacketID_t	GetPacketID ()const  {return SMSG_LOGIN_RESPONSE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD291Handler 
{
public:
	static uint32 Execute(SCMD291* pPacket) ;
};

#endif 