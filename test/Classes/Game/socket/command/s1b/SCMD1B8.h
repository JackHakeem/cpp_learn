#ifndef _SCMD1B8_H_
#define _SCMD1B8_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
	公会提示信息
	GMSG_COMMU_GUILD_NEW_RESP = 0x1B8 (439),		
	服务端->客户端, 包结构
	Byte：		提示类型  // 1 – 职务变更 / 2 – 捐献  /  3 – 新人入会 / 4 – 修改公告 / 5 - 科技升级
	String:		操作者名字
	String:		被操作对象名字 // 1时为对方名字 2时空 3时为对方名字 4时为公告内容 5空
	Int:		参数1	// 类型1时为原职务ID 2时为科技ID 3，4空，5科技ID
	Int:		参数2	// 类型1时为新职务ID 2时为捐献额 3，4空，5科技等级
 */
class SCMD1B8 : public Packet
{
public:
	SCMD1B8() {}
	virtual ~SCMD1B8() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_GUILD_TIP_RESP;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
	
	int8 a_type;
	string b_operator;
	string c_target;
	int d_param1;
	int e_param2;
};


class SCMD1B8Factory: public MessageFactory
{
public :
	
	virtual ~SCMD1B8Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1B8();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_GUILD_TIP_RESP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1B8Handler 
{
public:
	static uint32 Execute(SCMD1B8* pPacket) ;
};

#endif 