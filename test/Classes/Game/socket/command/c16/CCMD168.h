/**

 */

#ifndef _CCMD168_H_
#define _CCMD168_H_ 

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD168 : public Packet
{
public:
	CCMD168() {}
	virtual ~CCMD168() {}


	virtual bool	Write();
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_BAG_SORT;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:

};


class CCMD168Factory: public MessageFactory
{
public :
	
	virtual ~CCMD168Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_BAG_SORT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 