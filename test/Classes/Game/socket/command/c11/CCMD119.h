

#ifndef _CCMD119_H_
#define _CCMD119_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD119 : public Packet
{
public:
	CCMD119()
	{
		a_mapId = 0;
	}

	virtual ~CCMD119() {}


	virtual bool	Write();
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_PLAYER_VIEW_GET;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	int16 a_mapId;
};


class CCMD119Factory: public MessageFactory
{
public :
	
	virtual ~CCMD119Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_PLAYER_VIEW_GET;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 