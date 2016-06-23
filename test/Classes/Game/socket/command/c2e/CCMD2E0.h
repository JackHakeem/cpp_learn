/**
* The client requests buy cd list
* CMSG_WORLD_BUY_CRYSTAL_CD = 0x2E0
* Client -> server-side package structure
* int32, type
 */

#ifndef _CCMD2E0_H_
#define _CCMD2E0_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2E0 : public Packet
{
public:
	CCMD2E0() 
	{
		a_type = 0;
	}

	virtual ~CCMD2E0() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_WORLD_BUY_CRYSTAL_CD;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	 int32 a_type;
};


class CCMD2E0Factory: public MessageFactory
{
public :

	virtual ~CCMD2E0Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_BUY_CRYSTAL_CD;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif