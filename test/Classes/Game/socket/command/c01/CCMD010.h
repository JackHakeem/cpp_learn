#ifndef _CCMD010_H_
#define _CCMD010_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD010 : public Packet
{
public:
	CCMD010() {}
	virtual ~CCMD010() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_COMMU_HARTBEAT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

	//int16 a_sitNum ;
};


class CCMD010Factory: public MessageFactory
{
public :

	virtual ~CCMD010Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_HARTBEAT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif