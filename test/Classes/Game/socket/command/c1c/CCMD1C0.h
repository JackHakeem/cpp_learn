#ifndef _CCMD1C0_H_
#define _CCMD1C0_H_

/**
* 查看成员列表（分页）
* CMSG_COMMU_GUILD_MEMBER_LIST = 0x1C0 (448),			//世界聊天，将消息进行世界广播
* 服务端<-客户端, 包结构
* Byte：		排序类型，						//0-默认（不显示离线） 1-显示所有
* Short:		页码
* @author Administrator
* 
*/	

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD1C0 : public Packet
{
public:
	CCMD1C0() 
	{
	}

	virtual ~CCMD1C0() {}

	virtual bool	Write();	 

	virtual PacketID_t getPacketID() const { return CMSG_COMMU_GUILD_MEMBER_LIST;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	int8 a_displayType;
	int16 b_memberPage;
};

bool CCMD1C0::Write()
{
	writeByte(a_displayType);
	writeShort(b_memberPage);

	return true;
}

class CCMD1C0Factory: public MessageFactory
{
public :

	virtual ~CCMD1C0Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_GUILD_MEMBER_LIST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif