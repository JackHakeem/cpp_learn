#ifndef _CCMD400_H_
#define _CCMD400_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD400 : public Packet
{
public:
	CCMD400()
	{
	}
	virtual ~CCMD400() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_EGG_HISTORY;}

	virtual	int32		GetMessageSize( ) const { return 0;}
	
};

bool CCMD400::Write()
{
	
	return true;
}


class CCMD3DAFactory: public MessageFactory
{
public :

	virtual ~CCMD3DAFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_EGG_HISTORY;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif