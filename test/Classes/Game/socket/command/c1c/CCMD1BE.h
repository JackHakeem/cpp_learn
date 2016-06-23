#ifndef _CCMD1BE_H_
#define _CCMD1BE_H_

/**
* 用户发起查看公会信息请求
* CMSG_COMMU_GUILD_INFO = 0x1BE
* */


#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD1BE : public Packet
{
public:
	CCMD1BE() 
	{
	}

	virtual ~CCMD1BE() {}

	virtual bool	Write(){return true;}

	virtual PacketID_t getPacketID() const { return CMSG_COMMU_GUILD_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}
};

class CCMD1BEFactory: public MessageFactory
{
public :

	virtual ~CCMD1BEFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_GUILD_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif