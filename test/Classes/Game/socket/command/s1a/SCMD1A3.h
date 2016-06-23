/**
		 *返回用户邮件详细内容
			GMSG_COMMU_MAIL_DETAIL_RESPONSE = 0x1A3 (419)
			服务端<->客户端, 包结构
			Int:		邮件唯一ID
			Char:	发送人角色名
			Char:	邮件标题
			Byte:	邮件类型
			Byte:	收件箱状态(未读0，已读1)
			Int:		发送时间
			Byte:	附件领取状态
			Char:	邮件内容
			short: 	附件物品原型ID
			Int:		物品数量
		 * 
		 */	

#ifndef _SCMD1A3_H_
#define _SCMD1A3_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD1A3 : public Packet
{
public:
	SCMD1A3() {}
	virtual ~SCMD1A3() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_MAIL_CONTENT;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint32 a_mailId;			//邮件唯一ID
	std::string b_senderName;	//发送人角色名
	std::string c_mailTitle;	//邮件标题
	uint8 d_mailType;			//邮件类型
	uint8 e_mailStatus;		//收件箱状态(未读0，已读1)
	uint32 f_sendTime;			//发送时间
	uint8 g_attachStatus;		//附件领取状态(未领取0，已领取1，无附件状态2)
	std::string h_mailContent;	//邮件内容
	uint16 i_attachId;
	uint32 j_goodsNum;
};


class SCMD1A3Factory: public MessageFactory
{
public :
	
	virtual ~SCMD1A3Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1A3();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_MAIL_CONTENT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1A3Handler 
{
public:
	static uint32 Execute(SCMD1A3* pPacket) ;
};

#endif 