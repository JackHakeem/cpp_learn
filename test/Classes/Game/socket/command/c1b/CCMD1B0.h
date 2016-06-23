
#ifndef _CCMD1B0_H_
#define _CCMD1B0_H_

	/**新建公会
	 CMSG_COMMU_GUILD_NEW = 0x1B0 (432),			 
	 服务端<-客户端, 包结构
	 string:     公会名
	 */

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD1B0 : public Packet
{
public:
	CCMD1B0() {}
	virtual ~CCMD1B0() {}


	virtual bool	Write()
	{
		writeString(a_name.c_str());
		return true;
	};
public :
	virtual PacketID_t getPacketID() const  { return CMSG_COMMU_GUILD_NEW;}

	virtual	int32		GetMessageSize( ) const { return 0;}
	
	string a_name;
};

class CCMD1B0Factory: public MessageFactory
{
public :

	virtual ~CCMD1B0Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_GUILD_NEW;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};
#endif 