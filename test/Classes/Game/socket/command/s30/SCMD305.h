/**
* Xie mercenaries return package
* WMSG_WORLD_MERCENARY_DISMISS = 0x305
* Server -> client package structure
* Uint32, mercenary unique ID
* Byte processing results
 */ 

#ifndef _SCMD305_H_
#define _SCMD305_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD305 : public Packet
{
public:
	SCMD305()
	{
		a_mercenaryId = 0;
		b_result = 0;
	}

	virtual ~SCMD305() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_MERCENARY_DISMISS;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int32	a_mercenaryId;
	int8	b_result;
};


class SCMD305Factory: public MessageFactory
{
public :
	
	virtual ~SCMD305Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD305();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_MERCENARY_DISMISS;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD305Handler 
{
public:
	static uint32 Execute(SCMD305* pPacket) ;
};

#endif