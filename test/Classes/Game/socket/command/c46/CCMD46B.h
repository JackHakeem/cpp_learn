/**
 * 
Ò»¼üºÏ³É
 */

#ifndef _CCMD46B_H_
#define _CCMD46B_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD46B : public Packet
{
public:
	CCMD46B() 
	{
	}

	virtual ~CCMD46B() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_ZX_ONEKEY_COMPOSE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
};


class CCMD46BFactory: public MessageFactory
{
public :

	virtual ~CCMD46BFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_ZX_ONEKEY_COMPOSE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif