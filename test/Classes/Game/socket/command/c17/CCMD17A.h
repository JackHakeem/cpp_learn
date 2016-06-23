/**
* Protocol: 0x17A
* C -> s
Int8: change type (0 for parcels -> Bank 1 Bank -> wrapped)
* Int8: items location
	*/		
#ifndef _CCMD17A_H_
#define _CCMD17A_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD17A : public Packet
{
public:
	CCMD17A() {}
	virtual ~CCMD17A() {}


	virtual bool	Write();
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_ITEM_SELL;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	int16 a_shopid;//Interchangeable type (0 parcels -> Bank 1 Bank -> package)
	int32 b_sit;//Where stuff is
};


class CCMD17AFactory: public MessageFactory
{
public :
	
	virtual ~CCMD17AFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_ITEM_SELL;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 