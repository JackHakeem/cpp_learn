/**

 */

#ifndef _CCMD169_H_
#define _CCMD169_H_ 

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD169 : public Packet
{
public:
	CCMD169() {}
	virtual ~CCMD169() {}


	virtual bool	Write();
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_BANK_SORT;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:

};


class CCMD169Factory: public MessageFactory
{
public :
	
	virtual ~CCMD169Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_BANK_SORT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 