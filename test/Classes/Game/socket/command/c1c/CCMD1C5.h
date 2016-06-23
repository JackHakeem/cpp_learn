

#ifndef _CCMD1C5_H_
#define _CCMD1C5_H_
	/**
	 * 查看科技列表
	CMSG_COMMU_GUILD_TECH_LIST = 0x1C5 (453),			
	服务端<-客户端, 包结构
	Short:		页码
	 */	
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD1C5 : public Packet
{
public:
	CCMD1C5() {}
	virtual ~CCMD1C5() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_COMMU_GUILD_TECH_LIST;}

	virtual	int32		GetMessageSize( ) const { return 0;}
	
	int16 a_page;
};

bool CCMD1C5::Write()
{
	writeShort(a_page);
	return true;
}

class CCMD1C5Factory: public MessageFactory
{
public :

	virtual ~CCMD1C5Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_GUILD_TECH_LIST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif