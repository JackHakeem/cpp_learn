#ifndef _CCMD1A6_H_
#define _CCMD1A6_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
		 *用户发送邮件
		CMSG_COMMU_MAIL_SEND = 0x1A6 (422),
		客户端<->服务端, 包结构
		Char:	接收人角色名
		Char:	邮件标题
		Char:	邮件内容
		 * 
		 */

class CCMD1A6 : public Packet
{
public:
	CCMD1A6() {}
	virtual ~CCMD1A6() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_COMMU_MAIL_SEND;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

	std::string a_recvName;		//接收人角色名
	std::string b_mailTitle;	//邮件标题
	std::string c_mailContent;	//邮件内容
};


class CCMD1A6Factory: public MessageFactory
{
public :

	virtual ~CCMD1A6Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_MAIL_SEND;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif