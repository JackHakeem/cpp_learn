#ifndef _SCMD191_H__
#define _SCMD191_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
 * GMSG_COMMU_WORLD_CHAT = 0x191(401)，			//世界聊天，将消息进行世界广播
 * 服务端<->户端, 包结构
 * Int:		发起者ID
 * string:	发起者角色名
 * string:  聊天内容
	 string:		附加数据（战报，展示物品等）
 * byte:	线路
 * byte:	发起者帐号类型 // 1-游客 ; 2-普通玩家; 3-GM
 */

class SCMD191 : public Packet
{
public:
	SCMD191() {}
	virtual ~SCMD191() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_WORLD_CHAT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:		 
	int32 a_id;
	std::string b_name;
	std::string c_content;
	std::string d_data;
	int8 d_line;
	int8 e_accountType;
};


class SCMD191Factory: public MessageFactory
{
public :

	virtual ~SCMD191Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD191();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_WORLD_CHAT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD191Handler 
{
public:
	static uint32 Execute(SCMD191* pPacket) ;
};
#endif