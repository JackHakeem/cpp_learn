/**
* Protocol number: 0x16B
* C -> s
* Int8: the original location of items
* Int8: articles new location
	*/		
#ifndef _CCMD16B_H_
#define _CCMD16B_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD16B : public Packet
{
public:
	CCMD16B() {}
	virtual ~CCMD16B() {}


	virtual bool	Write();
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_BAG_ITEM_DELETE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	int8 a_bagType;//Items of the original position
	int8 b_sitGrid;//Items new position
};


class CCMD16BFactory: public MessageFactory
{
public :
	
	virtual ~CCMD16BFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_BAG_ITEM_DELETE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 