/**
 */

#ifndef _SCMD431_H_
#define _SCMD431_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD431 : public Packet
{
public:

	SCMD431()
	{
		a_stoneNum = 0;
		b_oreNum = 0;
	}

	virtual ~SCMD431() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_ORE_INFO;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint8 a_stoneNum;
	uint32 b_oreNum;
	uint32 c_buyCount;
};


class SCMD431Factory: public MessageFactory
{
public :
	
	virtual ~SCMD431Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD431();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_ORE_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD431Handler 
{
public:
	static uint32 Execute(SCMD431* pPacket) ;
};

#endif