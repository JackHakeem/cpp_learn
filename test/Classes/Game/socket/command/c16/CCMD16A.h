/**
* Protocol: 0x16A
* C -> s
Int8: change type (0 for parcels -> Bank 1 Bank -> wrapped)
* Int8: items location
	*/		
#ifndef _CCMD16A_H_
#define _CCMD16A_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD16A : public Packet
{
public:
	CCMD16A() {}
	virtual ~CCMD16A() {}


	virtual bool	Write();
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_BAG_BANK_SWAP;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	int8 a_type;//Interchangeable type (0 parcels -> Bank 1 Bank -> package)
	int8 b_sitGrid;//Where stuff is
};


class CCMD16AFactory: public MessageFactory
{
public :
	
	virtual ~CCMD16AFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_BAG_BANK_SWAP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 