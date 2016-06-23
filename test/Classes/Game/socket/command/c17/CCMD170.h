
#ifndef _CCMD170_H_
#define _CCMD170_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD170 : public Packet
{
public:
	CCMD170() {}
	virtual ~CCMD170() {}


	virtual bool	Write();
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_EQUIP_UP;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	uint32 a_figureId;
	uint8 b_sitGrid;
};


class CCMD170Factory: public MessageFactory
{
public :
	
	virtual ~CCMD170Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_EQUIP_UP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 