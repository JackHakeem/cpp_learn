/**
* client requests battle winning streak info
CMSG_WORLD_PVP_QUALIFYING_STAR = 0x37D
Client -> server, the package structure
byte 0
 
 */

#ifndef _CCMD413_H_
#define _CCMD413_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD413 : public Packet
{
public:
	CCMD413() 
	{
		//a_lunType = 0;
		//b_lunType = 0;
		//c_lunType = 0;
	}

	virtual ~CCMD413() {}

	virtual bool	Write();	 

	virtual PacketID_t getPacketID() const { return CMSG_CHALLENAGE_VIGOUR_GET;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	 //uint8 a_lunType;
	 //uint8 b_lunType;
	 //uint8 c_lunType;
};


class CCMD413Factory: public MessageFactory
{
public :

	virtual ~CCMD413Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_CHALLENAGE_VIGOUR_GET;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif