/**
CMSG_WORLD_MAP_PROCESS_GET = 0x121 (289)
 */

#ifndef _CCMD121_H_
#define _CCMD121_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD121 : public Packet
{
public:
	CCMD121()
	{
		a_byte = 0;
	}

	virtual ~CCMD121() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_WORLD_MAP_PROCESS_GET;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	 int8 a_byte;

};


class CCMD121Factory: public MessageFactory
{
public :

	virtual ~CCMD121Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_MAP_PROCESS_GET;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif