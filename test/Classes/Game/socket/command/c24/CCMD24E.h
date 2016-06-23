/**
* client requests battle winning streak info
 = 0x24E
Client -> server, the package structure
byte 0
 
 */

#ifndef _CCMD24E_H_
#define _CCMD24E_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD24E : public Packet
{
public:
	CCMD24E() 
	{
	}

	virtual ~CCMD24E() {}

	virtual bool	Write()
	{
		return true;
	}

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_FREE_TOKEN_INFO_REQUEST;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

};


class CCMD24EFactory: public MessageFactory
{
public :

	virtual ~CCMD24EFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_FREE_TOKEN_INFO_REQUEST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif