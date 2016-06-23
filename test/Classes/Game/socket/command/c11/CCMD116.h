// root map jum

#ifndef _CCMD116_H_
#define _CCMD116_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD116 : public Packet
{
public:
	CCMD116() 
	{
		triggerId = 0;
	}

	virtual ~CCMD116() {}


	virtual bool	Write();
public :

	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_MAP_ENTER;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	int16 triggerId;
};


class CCMD116Factory: public MessageFactory
{
public :
	
	virtual ~CCMD116Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_MAP_ENTER;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 