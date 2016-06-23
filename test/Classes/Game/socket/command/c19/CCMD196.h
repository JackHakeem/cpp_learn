#ifndef _CCMD196_H_
#define _CCMD196_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
 * CMSG_COMMU_SECRET_CHAT = 0x196(406),			//密语聊天
 * 服务端<->客户端, 包结构
 * string:		接收者角色名
 * string:     聊天内容
 * string:		附加数据（战报，展示物品等）
 */

class CCMD196 : public Packet
{
public:
	CCMD196() {}
	virtual ~CCMD196() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_COMMU_PRIVATE_CHAT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

	std::string a_name;
	std::string b_content;
	std::string c_data;
};


class CCMD196Factory: public MessageFactory
{
public :

	virtual ~CCMD196Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_PRIVATE_CHAT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif