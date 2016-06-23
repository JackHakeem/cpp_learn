/**
* Mercenary reincarnation return package
* WMSG_WORLD_MERCENARY_RERSIE = 0x30C (780)
* Server -> client package structure
uint8 whether
the uint32 mercenary unique ID
uint8 reincarnation Views
	 * 
	 */

#ifndef _SCMD30C_H_
#define _SCMD30C_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD30C : public Packet
{
public:
	SCMD30C()
	{
		a_result = 0;
		b_figureId = 0;
		c_rebornNum = 0;
	}

	virtual ~SCMD30C() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_MERCENARY_RERSIE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8	a_result;
	int32	b_figureId;
	int8	c_rebornNum;
};


class SCMD30CFactory: public MessageFactory
{
public :
	
	virtual ~SCMD30CFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD30C();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_MERCENARY_RERSIE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD30CHandler 
{
public:
	static uint32 Execute(SCMD30C* pPacket) ;
};

#endif