
#ifndef _CCMD1CE_H_
#define _CCMD1CE_H_

	/**
	 * 修改公会信息
	CMSG_COMMU_GUILD_ALTER_INFO = 0x1CE ()，			 
	服务端<-客户端, 包结构
	// 公告、介绍不变
	String:			QQ群			// 若无变动则为空，下同
	String：		公告			
	String：		介绍 
	 * 
	 */	

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD1CE : public Packet
{
public:
	CCMD1CE() {}
	virtual ~CCMD1CE() {}


	virtual bool	Write() 
	{ 
		writeString(b_qqGP.c_str());
		writeString(c_notice.c_str());
		writeString(d_intr.c_str());
		return true; 
	};
public :
	virtual PacketID_t getPacketID() const  { return CMSG_COMMU_GUILD_ALTER_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}
	
	string b_qqGP;
	string c_notice;
	string d_intr;
};

class CCMD1CEFactory: public MessageFactory
{
public :

	virtual ~CCMD1CEFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_GUILD_ALTER_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};
#endif 