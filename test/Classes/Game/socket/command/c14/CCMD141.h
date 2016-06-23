#ifndef _CCMD141_H_
#define _CCMD141_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD141 : public Packet
{
public:
	CCMD141() 
	{
	}

	virtual ~CCMD141() {}

	virtual bool	Write()
	{
		return true;
	}

	virtual PacketID_t getPacketID() const { return CMSG_GET_ACHIVEMENT_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
};


class CCMD141Factory: public MessageFactory
{
public :

	virtual ~CCMD141Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_GET_ACHIVEMENT_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif