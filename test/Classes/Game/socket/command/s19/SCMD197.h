#ifndef _SCMD197_H__
#define _SCMD197_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
 * GMSG_COMMU_PRIVATE_CHAT = 0x197(407),			//密语聊天
 * 服务端<->客户端, 包结构
 * Int: 		发起者ID
 * string:		发起者角色名
 * string:     聊天内容
	 string:		附加数据（战报，展示物品等）
 * byte:	线路
 * int:		接收对象ID
 * string:		接收者名称
 * byte:	发起者帐号类型 // 1-游客 ; 2-普通玩家; 3-GM
 */
class SCMD197 : public Packet
{
public:
	SCMD197() {}
	virtual ~SCMD197() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_PRIVATE_CHAT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:		 
	int32 a_fromId;
	std::string b_fromName;
	std::string c_content;
	std::string d_data;
	int8 d_line;
	int32 e_toId;
	std::string f_toName;
	int8 g_accountType;

};


class SCMD197Factory: public MessageFactory
{
public :

	virtual ~SCMD197Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD197();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_PRIVATE_CHAT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD197Handler 
{
public:
	static uint32 Execute(SCMD197* pPacket) ;
};
#endif