/**
* Protocol number: 0x162
* C -> s
* Int8: the original location of items
* Int8: articles new location
	*/		
#ifndef _CCMD162_H_
#define _CCMD162_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD162 : public Packet
{
public:
	CCMD162() {}
	virtual ~CCMD162() {}


	virtual bool	Write();
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_BANK_ITEM_UPDATE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	int8 c_oldSit;//Items of the original position
	int8 d_newSit;//Items new position
};


class CCMD162Factory: public MessageFactory
{
public :
	
	virtual ~CCMD162Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_BANK_ITEM_UPDATE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 