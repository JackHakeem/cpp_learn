

#ifndef _CCMD1BA_H_
#define _CCMD1BA_H_

	/**
	 入会申请
	 CMSG_COMMU_GUILD_APPLY = 0x1BA (442),			    
	 服务端<-客户端, 包结构
	 String：	公会名
	 */

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD1BA : public Packet
{
public:
	CCMD1BA() {}
	virtual ~CCMD1BA() {}


	virtual bool	Write()
	{
		writeString( a_guildName.c_str() );
		return true; 
	};
public :
	virtual PacketID_t getPacketID() const { return CMSG_COMMU_GUILD_APPLY;}

	virtual	int32		GetMessageSize( ) const { return 0;}

	string a_guildName;
};


class CCMD1BAFactory: public MessageFactory
{
public :

	virtual ~CCMD1BAFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_GUILD_APPLY;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif