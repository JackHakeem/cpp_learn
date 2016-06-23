#ifndef _CCMD190_H_
#define _CCMD190_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
 * CMSG_COMMU_WORLD_CHAT = 0x190(400),			//世界聊天，将消息进行世界广播
 * 服务端->客户端, 包结构
 * string:     聊天内容 
 * string:		附加数据（战报，展示物品等）
 */

class CCMD190 : public Packet
{
public:
	CCMD190() {}
	virtual ~CCMD190() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_COMMU_WORLD_CHAT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

	std::string a_content;
	std::string b_data;


};


class CCMD190Factory: public MessageFactory
{
public :

	virtual ~CCMD190Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_WORLD_CHAT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif