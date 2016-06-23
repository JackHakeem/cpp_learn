/**
* Protocol number: 0x178
* C -> s
Int8: change type (0 for parcels -> Bank 1 Bank -> wrapped)
* Int8: items location
	*/		
#ifndef _CCMD178_H_
#define _CCMD178_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD178 : public Packet
{
public:
	CCMD178() {}
	virtual ~CCMD178() {}


	virtual bool	Write();
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_ITEM_BUY;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	int16 a_shopid;//Interchangeable type (0 parcels -> Bank 1 Bank -> package)
	int16 b_goodid;//Where stuff is
};


class CCMD178Factory: public MessageFactory
{
public :
	
	virtual ~CCMD178Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_ITEM_BUY;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 