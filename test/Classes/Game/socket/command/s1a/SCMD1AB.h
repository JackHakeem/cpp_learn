/**
		 *返回用户邮件数量信 
		 * 
		 */	

#ifndef _SCMD1AB_H_
#define _SCMD1AB_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD1AB : public Packet
{
public:
	SCMD1AB() {}
	virtual ~SCMD1AB() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_MAIL_COUNTINFO;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint16 a_unreadNum;		//未读邮件数
	uint16 b_totalNum;			//全部邮件总数
	uint16 c_playerMailNum;		//玩家邮件总数
	uint16 d_systemMailNum;		//系统邮件总数
};


class SCMD1ABFactory: public MessageFactory
{
public :
	
	virtual ~SCMD1ABFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1AB();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_MAIL_COUNTINFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1ABHandler
{
public:
	static uint32 Execute(SCMD1AB* pPacket) ;
};

#endif 