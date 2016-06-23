/**
* Protocol number: 0x160
* C -> s
* Int8: the original location of items
* Int8: articles new location
	*/		
#ifndef _CCMD160_H_
#define _CCMD160_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD160 : public Packet
{
public:
	CCMD160() {}
	virtual ~CCMD160() {}


	virtual bool	Write();
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_BAG_ITEM_UPDATE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	int8 a_oldSit;//Items of the original position
	int8 b_newSit;//Items new position
};


class CCMD160Factory: public MessageFactory
{
public :
	
	virtual ~CCMD160Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_BAG_ITEM_UPDATE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 