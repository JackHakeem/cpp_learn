/**
* client requests battle winning streak info
CMSG_WORLD_PVP_QUALIFYING_STAR = 0x360
Client -> server, the package structure
byte 0
 
 */

#ifndef _CCMD38D_H_
#define _CCMD38D_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD38D : public Packet
{
public:
	CCMD38D() 
	{
		
	}

	virtual ~CCMD38D() {}

	virtual bool	Write(){ return true; };	 

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_QUALIFYING_OPP_RESET_REQ;}
													
	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	//uint32 param;
};


class CCMD38DFactory: public MessageFactory
{
public :

	virtual ~CCMD38DFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_QUALIFYING_OPP_RESET_REQ;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif