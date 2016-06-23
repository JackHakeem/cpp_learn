#ifndef _CCMD1A0_H_
#define _CCMD1A0_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
	 *邮件头列表请求
	 * @author Administrator
	 * 
	 */
/**
		 *CMSG_COMMU_MAIL_LIST_REQUEST = 0x1A0(416),		
			客户端<->服务端, 包结构
			byte:		邮件类型			(全部0，玩家1，系统2）
			Short：		请求列表起始序号	(序号从0开始排号)
			Short：		请求列表数量
		 * 
		 */	

class CCMD1A0 : public Packet
{
public:
	CCMD1A0() : a_mailType(0),b_startNum(0),c_mailNum(0)
	{}
	virtual ~CCMD1A0() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_COMMU_MAIL_LIST;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

	uint8 a_mailType;		//邮件类型（全部0，玩家1，系统2）
	uint16 b_startNum;		//邮件列表起始序号	(序号从0开始排号)
	uint16 c_mailNum;		//邮件列表数量;
};


class CCMD1A0Factory: public MessageFactory
{
public :

	virtual ~CCMD1A0Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_MAIL_LIST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif