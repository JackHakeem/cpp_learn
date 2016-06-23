

#ifndef _CCMD1C4_H_
#define _CCMD1C4_H_
	/**
	 *默认科技修改
	 *CMSG_COMMU_GUILD_DEFAULT_TECH = 0x1C4 (452),			
	 *服务端<-客户端, 包结构
	 *Int16:		默认科技ID
	 **/
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD1C4 : public Packet
{
public:
	CCMD1C4() {}
	virtual ~CCMD1C4() {}


	virtual bool	Write()
	{
		writeShort(a_scienceId);
		return true;
	}
public :
	virtual PacketID_t getPacketID() const { return CMSG_COMMU_GUILD_DEFAULT_TECH;}

	virtual	int32		GetMessageSize( ) const { return 0;}
	
	int16 a_scienceId;
};


class CCMD1C4Factory: public MessageFactory
{
public :

	virtual ~CCMD1C4Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_GUILD_DEFAULT_TECH;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif