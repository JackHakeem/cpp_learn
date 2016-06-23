

#ifndef _CCMD1CC_H_
#define _CCMD1CC_H_
	/**
		//用户发起退出公会请求 CMSG_COMMU_GUILD_QUIT
	 **/
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD1CC : public Packet
{
public:
	CCMD1CC() {}
	virtual ~CCMD1CC() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_COMMU_GUILD_QUIT;}

	virtual	int32		GetMessageSize( ) const { return 0;}
};

bool CCMD1CC::Write()
{
	return true;
}

class CCMD1CCFactory: public MessageFactory
{
public :

	virtual ~CCMD1CCFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_GUILD_QUIT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif