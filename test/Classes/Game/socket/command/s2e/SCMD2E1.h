/**
*  buy cd list response
WMSG_WORLD_BUY_CRYSTAL_CD = 0x2E1
The service side -> client package structure
Uint8 		0,buy already£»1£¬gold is not enough£»2£¬buy success
Uint8 		current list num 
 * 
*/	

#ifndef _SCMD2E1_H_
#define _SCMD2E1_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD2E1 : public Packet
{
public:
	SCMD2E1() {}
	virtual ~SCMD2E1() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_BUY_CRYSTAL_CD;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint8 a_value;
	uint8 b_listNum;
};


class SCMD2E1Factory: public MessageFactory
{
public :

	virtual ~SCMD2E1Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2E1();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_BUY_CRYSTAL_CD;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2E1Handler 
{
public:
	static uint32 Execute(SCMD2E1* pPacket) ;
};

#endif