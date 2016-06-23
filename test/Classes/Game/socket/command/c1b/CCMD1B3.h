
#ifndef _CCMD1B3_H_
#define _CCMD1B3_H_

	/**
	 * 查找公会
	 * CMSG_COMMU_GUILD_FIND = 0x1B3 (435),
	 * 服务端<-客户端, 包结构
	 * string:     公会名字
	 * short:		页码						// 如果填0则是精确查找,否则是模糊查找
	 */

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD1B3 : public Packet
{
public:
	CCMD1B3() {}
	virtual ~CCMD1B3() {}


	virtual bool	Write()
	{
		writeString(a_guildName.c_str());
		writeShort(b_page);
		
		return true;
	};
public :
	virtual PacketID_t getPacketID() const  { return CMSG_COMMU_GUILD_FIND;}

	virtual	int32		GetMessageSize( ) const { return 0;}

	string a_guildName;
	int16 b_page;
};

class CCMD1B3Factory: public MessageFactory
{
public :

	virtual ~CCMD1B3Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_GUILD_FIND;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};
#endif 