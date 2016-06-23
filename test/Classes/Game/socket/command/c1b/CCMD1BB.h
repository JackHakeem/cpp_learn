

#ifndef _CCMD1BB_H_
#define _CCMD1BB_H_
	/**
	 * 查看入会申请列表
	CMSG_COMMU_GUILD_APPLY_LIST = 0x1BB (443),			    
	服务端<-客户端, 包结构
	Short:		页码
	 */	
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD1BB : public Packet
{
public:
	CCMD1BB() {}
	virtual ~CCMD1BB() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_COMMU_GUILD_APPLY_LIST;}

	virtual	int32		GetMessageSize( ) const { return 0;}

	int16 a_page; 
};

bool CCMD1BB::Write()
{
	writeShort(a_page);
	return true;
}


class CCMD1BBFactory: public MessageFactory
{
public :

	virtual ~CCMD1BBFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_GUILD_APPLY_LIST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif