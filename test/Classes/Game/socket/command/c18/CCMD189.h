// request for crystal info
#ifndef _CCMD189_H_
#define _CCMD189_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD189 : public Packet
{
public:
	CCMD189() {}
	virtual ~CCMD189() {}

	virtual bool	Write();	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_LOGIN_CRYSLTAL;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

};


class CCMD189Factory: public MessageFactory
{
public :

	virtual ~CCMD189Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_LOGIN_CRYSLTAL;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif