/**
 * GMSG_COMMU_MAIL_LIST_RESPONSE = 0x1A1(417)
服务端<->客户端, 包结构
byte:		邮件类型（全部0，玩家1，系统2）
Short:		该类型邮件列表总数量
Short:		邮件列表起始序号
Short:		邮件头数量
	Int:	邮件唯一ID
	Char:	发送人角色名
	Char:	邮件标题
	Byte:	邮件类型
	Byte:	收件箱状态(未读0，已读1)
	Int:    发送时间
	Byte:	附件领取状态(未领取0，已领取1，无附件状态2)
 */
#ifndef _SCMD1A1_H_
#define _SCMD1A1_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

/**
		 *邮件头信息
		 * Int:	邮件唯一ID
		Char:	发送人角色名
		Char:	邮件标题
		Byte:	邮件类型
		Byte:	收件箱状态(未读0，已读1)
		Int:	发送时间
		Byte:	附件领取状态(未领取0，已领取1，无附件状态2)

		 */

struct SCMD1A1Node
{
	uint32 a_mailId;		//邮件唯一ID
	std::string b_senderName;	//发送人角色名
	std::string c_mailTitle;		
	uint8 d_mailType;
	uint8 e_mailStatus;			//状态(未读0，已读1)
	uint32 f_sendTime;				//发送时间
	uint8 g_attachStatus;			//附件领取状态(未领取0，已领取1，无附件状态2)
	SCMD1A1Node()
	{
		a_mailId = 0;
		b_senderName = "";
		c_mailTitle = "";
		d_mailType = 0;
		e_mailStatus = 0;
		f_sendTime = 0;
		g_attachStatus = 0;
	}
};

class SCMD1A1 : public Packet
{
public:
	SCMD1A1() {}
	virtual ~SCMD1A1() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_MAIL_LIST;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint8 a_mailType;		//邮件类型（全部0，玩家1，系统2）
	uint16 b_mailCount;	//该类型邮件列表总数量
	uint16 c_startNum;	//邮件列表起始序号
	std::list<SCMD1A1Node> d_mailList;
};


class SCMD1A1Factory: public MessageFactory
{
public :
	
	virtual ~SCMD1A1Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1A1();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_MAIL_LIST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1A1Handler 
{
public:
	static uint32 Execute(SCMD1A1* pPacket) ;
};

#endif 