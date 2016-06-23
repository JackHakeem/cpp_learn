/**
* CMSG_WORLD_LOGIN = 0x106, / / ​​line node landing
* Client -> server, the package structure:
* Int: Account Id
* Int: random verification code
* String: encryption SN
 */

#ifndef _CCMD11E_H_
#define _CCMD11E_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD11E : public Packet
{
public:
	CCMD11E()
	{
		a_monsterId = 0;
	}
	virtual ~CCMD11E() {}


	virtual bool	Write();
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_REDO_MAP_PROCESS;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	int32 a_monsterId;
};


class CCMD11EFactory: public MessageFactory
{
public :
	
	virtual ~CCMD11EFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_REDO_MAP_PROCESS;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 