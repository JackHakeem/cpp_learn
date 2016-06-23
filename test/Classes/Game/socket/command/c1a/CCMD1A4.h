#ifndef _CCMD1A4_H_
#define _CCMD1A4_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
		 *用户删除邮件
			CMSG_COMMU_MAIL_DEL = 0x1A4 (420),
			客户端<->服务端, 包结构
			Short：		删除邮件的数量
				Int:		邮件唯一Id

		 * 
		 */	

class CCMD1A4 : public Packet
{
public:
	CCMD1A4() {}
	virtual ~CCMD1A4() {a_mailIdList.clear();}


	virtual bool	Write();


	virtual PacketID_t getPacketID() const { return CMSG_COMMU_MAIL_DELETE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	/**邮件唯一Id列表，删除多封或一封邮件*/
	std::list<uint> a_mailIdList;
};


class CCMD1A4Factory: public MessageFactory
{
public :

	virtual ~CCMD1A4Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_MAIL_DELETE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif