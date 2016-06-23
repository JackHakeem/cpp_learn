/**
 * 
Ò»¼üÂô³ö
 */

#ifndef _CCMD466_H_
#define _CCMD466_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD466 : public Packet
{
public:
	CCMD466() 
	{
	}

	virtual ~CCMD466() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_ZX_SELL_XH;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
};


class CCMD466Factory: public MessageFactory
{
public :

	virtual ~CCMD466Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_ZX_SELL_XH;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif