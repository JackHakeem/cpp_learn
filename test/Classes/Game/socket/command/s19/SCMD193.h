#ifndef _SCMD193_H__
#define _SCMD193_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
 * GMSG_COMMU_GUILD_CHAT = 0x193(403),			//工会聊天，服务端根据发起者id确定接收者
 * 服务端<->客户端, 包结构
 * Int：		发起者ID
 * string:		发起者角色名
 * string:     聊天内容
	 string:		附加数据（战报，展示物品等）
 * byte:	线路
 * byte:	发起者帐号类型 // 1-游客 ; 2-普通玩家; 3-GM
 */
class SCMD193 : public Packet
{
public:
	SCMD193() {}
	virtual ~SCMD193() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_GUILD_CHAT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:		 
	int32 a_id;
	std::string b_name;
	std::string c_content;
	std::string d_data;
	int8 d_line;
	int8 e_accountType;

};


class SCMD193Factory: public MessageFactory
{
public :

	virtual ~SCMD193Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD193();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_GUILD_CHAT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD193Handler 
{
public:
	static uint32 Execute(SCMD193* pPacket) ;
};
#endif