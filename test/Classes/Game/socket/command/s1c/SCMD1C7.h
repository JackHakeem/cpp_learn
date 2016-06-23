#ifndef _SCMD1C7_H_
#define _SCMD1C7_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

/**
公会操作响应
GMSG_COMMU_GUILD_ERR = 0x1C7 (455)，			 
服务端->客户端, 包结构
byte:		响应码(待约定)

响应码含义：
111，军徽达到最高等级
113，成功
114，钱不够
115，超过捐献上限
122，被所在公会踢出
*/
class SCMD1C7 : public Packet
{
public:
	SCMD1C7() {}
	virtual ~SCMD1C7() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_GUILD_ERR;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint8 a;
};


class SCMD1C7Factory: public MessageFactory
{
public :

	virtual ~SCMD1C7Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1C7();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_GUILD_ERR;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1C7Handler 
{
public:
	static uint32 Execute(SCMD1C7* pPacket) ;
};

/**
 * 所有响应码
 * 
从105开始：

// 用于新建工会
新建公会成功
名字重复
银币不足
没有勋章

// 用于公会查找
公会不存在

// 用于军徽升级
成功
已达最大等级
金币不足

//用于捐献
捐献成功
银币不足
超过当日捐献上限

//用于成员任命
成功
官员人数满
副会长人数满
任命对象不存在

//用于入会审批
审批对象已加入别的公会
公会人数达到上限

 
*/

#endif 