/**
	*protocal num£º0x176£»
	* c -> s£»
	* Int8: open type, 1 backpack, 2 bank;  
	* Int8: add open num
	*/		
#ifndef _CCMD176_H_
#define _CCMD176_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD176 : public Packet
{
public:
	CCMD176() {}
	virtual ~CCMD176() {}


	virtual bool	Write();
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_CONTAINER_EXPAND;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	int8 a_gridType;//open type, 1 backpack, 2 bank;  
	int8 b_number;//add open num
};


class CCMD176Factory: public MessageFactory
{
public :
	
	virtual ~CCMD176Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_CONTAINER_EXPAND;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 