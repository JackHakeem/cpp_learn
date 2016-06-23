/**
* CMSG_WORLD_LOGIN = 0x106, / / ​​line node landing
* Client -> server, the package structure:
* As byte: 0

 */

#ifndef _CCMD164_H_
#define _CCMD164_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD164 : public Packet
{
public:
	CCMD164() {}
	virtual ~CCMD164() {}


	virtual bool	Write();
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_BAG_INIT;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
//无数据项
};


class CCMD164Factory: public MessageFactory
{
public :
	
	virtual ~CCMD164Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_BAG_INIT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 