// Player move CMSG_WORLD_MOVE

#ifndef _CCMD110_H_
#define _CCMD110_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

struct CCMD110Node
{
	int16 a_x;
	int16 b_y;
	CCMD110Node()
	{
		a_x = 0;
		b_y = 0;
	}
};

class CCMD110 : public Packet
{
public:
	CCMD110() 
	{
	}

	virtual ~CCMD110() {}


	virtual bool	Write();
public :

	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_MOVE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	std::vector<CCMD110Node> a_path;
};


class CCMD110Factory: public MessageFactory
{
public :
	
	virtual ~CCMD110Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_MOVE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 