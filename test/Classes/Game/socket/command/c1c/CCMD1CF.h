

#ifndef _CCMD1CF_H_
#define _CCMD1CF_H_
	/**
		//用户发起升级军徽请求 CMSG_COMMU_GUILD_FLAG_UPDATE
	 **/
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD1CF : public Packet
{
public:
	CCMD1CF() {}
	virtual ~CCMD1CF() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_COMMU_GUILD_FLAG_UPDATE;}

	virtual	int32		GetMessageSize( ) const { return 0;}
};

bool CCMD1CF::Write()
{
	return true;
}

class CCMD1CFFactory: public MessageFactory
{
public :

	virtual ~CCMD1CFFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_GUILD_FLAG_UPDATE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif