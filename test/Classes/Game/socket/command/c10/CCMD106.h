/**
* CMSG_WORLD_LOGIN = 0x106, / / ​​line node landing
* Client -> server, the package structure:
* Int: Account Id
* Int: random verification code
* String: encryption SN
 */

#ifndef _CCMD106_H_
#define _CCMD106_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD106 : public Packet
{
public:
	CCMD106() {}
	virtual ~CCMD106() {}


	virtual bool	Write();
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_LOGIN_RESPONSE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	int32 a_accountId;
	int32 b_key;
	std::string c_sn;
};


class CCMD106Factory: public MessageFactory
{
public :
	
	virtual ~CCMD106Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_LOGIN_RESPONSE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 