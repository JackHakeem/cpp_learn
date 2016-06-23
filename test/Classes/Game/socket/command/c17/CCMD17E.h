/**
* CMSG_WORLD_LOGIN_CD =  0x17e
* C -> s
	*/		
#ifndef _CCMD17E_H_
#define _CCMD17E_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD17E : public Packet
{
public:
	CCMD17E() {}
	virtual ~CCMD17E() {}


	virtual bool	Write();
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_LOGIN_CD;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:

};


class CCMD17EFactory: public MessageFactory
{
public :
	
	virtual ~CCMD17EFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_LOGIN_CD;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 