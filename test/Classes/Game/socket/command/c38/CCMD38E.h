/**
* client requests battle winning streak info
CMSG_WORLD_PVP_QUALIFYING_STAR = 0x360
Client -> server, the package structure
byte 0
 
 */

#ifndef _CCMD38E_H_
#define _CCMD38E_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD38E : public Packet
{
public:
	CCMD38E() 
	{
		
	}

	virtual ~CCMD38E() {}

	virtual bool	Write(){ return true; };	 

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_ACTIVITY_INFO_REQ;}
													
	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	//uint32 param;
};


class CCMD38EFactory: public MessageFactory
{
public :

	virtual ~CCMD38EFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_ACTIVITY_INFO_REQ;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif