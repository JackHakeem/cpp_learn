/**
		 *用户接收到的邮件
		 GMSG_COMMU_MAIL_RECV = 0x1A9(425)		//用户接收到的邮件
		 服务端<->客户端, 包结构
		 |Int:	邮件唯一ID
		 |Char:	发送人角色名 
		 |Char:	邮件标题
		 |Byte:	邮件类型（全部0，玩家1，系统2）
		 |Byte:	收件箱状态(未读0，已读1)
		 |Int:	发送时间
		 |Byte:	附件领取状态(未领取0，已领取1，无附件状态2)
		 */	

#ifndef _SCMD1A9_H_
#define _SCMD1A9_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD1A9 : public Packet
{
public:
	SCMD1A9() {}
	virtual ~SCMD1A9() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_MAIL_RECV;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint32 a_mailId;			//邮件唯一ID
	std::string b_senderName;	//发送人角色名 
	std::string c_mailTitle;	//邮件标题
	uint8 d_mailType;			//邮件类型（全部0，玩家1，系统2）
	uint8 e_mailStatus;		//收件箱状态(未读0，已读1)
	uint32 f_sendTime;			//发送时间
	uint8 g_attachStatus;		//附件领取状态(未领取0，已领取1，无附件状态2)
};


class SCMD1A9Factory: public MessageFactory
{
public :
	
	virtual ~SCMD1A9Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1A9();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_MAIL_RECV;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1A9Handler 
{
public:
	static uint32 Execute(SCMD1A9* pPacket) ;
};

#endif 