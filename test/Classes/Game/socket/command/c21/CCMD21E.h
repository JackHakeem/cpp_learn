#ifndef _CCMD21E_H_
#define _CCMD21E_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
Player requests to buy energy info
CMSG_WORLD_BUY_VIGOUR_INFO = 0x21E
 */

class CCMD21E : public Packet
{
public:
	CCMD21E() {}
	virtual ~CCMD21E() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_WORLD_BUY_VIGOUR_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :


};


class CCMD21EFactory: public MessageFactory
{
public :

	virtual ~CCMD21EFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_BUY_VIGOUR_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif