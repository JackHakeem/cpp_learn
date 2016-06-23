/**
* The client requests buy cd list
* CMSG_WORLD_BUY_CRYSTAL_CD = 0x2E0
* Client -> server-side package structure
* int32, type
 */

#ifndef _CCMD2E2_H_
#define _CCMD2E2_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2E2 : public Packet
{
public:
	CCMD2E2() 
	{
	}

	virtual ~CCMD2E2() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_SILVERMINE_ENTER;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
};


class CCMD2E2Factory: public MessageFactory
{
public :

	virtual ~CCMD2E2Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_SILVERMINE_ENTER;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif