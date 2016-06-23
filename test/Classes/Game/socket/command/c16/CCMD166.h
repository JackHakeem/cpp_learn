/**

 */

#ifndef _CCMD166_H_
#define _CCMD166_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD166 : public Packet
{
public:
	CCMD166() {}
	virtual ~CCMD166() {}


	virtual bool	Write();
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_BANK_INIT;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
// No data
};


class CCMD166Factory: public MessageFactory
{
public :
	
	virtual ~CCMD166Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_BANK_INIT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 