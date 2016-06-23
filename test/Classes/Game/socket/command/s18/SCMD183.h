#ifndef  _SCMD183_H__
#define _SCMD183_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/* * 
Server response CD reset the results 

WMSG_WORLD_CLEAR_CD_RESULT = 0 x183 (387) 

The server-> the client, package structure 

Byte is strengthening success, 0: success, 6: not enough gold COINS 

Byte CD type 

*/ 

class SCMD183 : public Packet
{
public:
	SCMD183() {}
	virtual ~SCMD183() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_CLEAR_CD_RESULT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:		 
	int8 a_state;
	int8 b_type;
};


class SCMD183Factory: public MessageFactory
{
public :

	virtual ~SCMD183Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD183();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_CLEAR_CD_RESULT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD183Handler 
{
public:
	static uint32 Execute(SCMD183* pPacket) ;
};
#endif