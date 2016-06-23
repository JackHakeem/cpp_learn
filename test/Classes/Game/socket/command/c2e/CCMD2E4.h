/**
* The client requests buy cd list
* CMSG_WORLD_BUY_CRYSTAL_CD = 0x2E0
* Client -> server-side package structure
* int32, type
 */

#ifndef _CCMD2E4_H_
#define _CCMD2E4_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2E4 : public Packet
{
public:
	CCMD2E4() 
	{
	}

	virtual ~CCMD2E4() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_SILVERMINE_QUIT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
};


class CCMD2E4Factory: public MessageFactory
{
public :

	virtual ~CCMD2E4Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_SILVERMINE_QUIT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif