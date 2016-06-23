

#ifndef _CCMD1CA_H_
#define _CCMD1CA_H_
	/**
	 * 踢出成员
	 * CMSG_COMMU_GUILD_KICK_MEMBER = 0x1CA (459)，
	 * 服务端<-客户端, 包结构
	 * String:		被踢角色名
	 **/
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD1CA : public Packet
{
public:
	CCMD1CA() {}
	virtual ~CCMD1CA() {}


	virtual bool	Write()
	{
		writeString(a_pName.c_str());
		return true;
	}
public :
	virtual PacketID_t getPacketID() const { return CMSG_COMMU_GUILD_KICK_MEMBER;}

	virtual	int32		GetMessageSize( ) const { return 0;}
	
	string a_pName;
};



class CCMD1CAFactory: public MessageFactory
{
public :

	virtual ~CCMD1CAFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_GUILD_KICK_MEMBER;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif