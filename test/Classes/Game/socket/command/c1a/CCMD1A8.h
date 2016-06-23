#ifndef _CCMD1A8_H_
#define _CCMD1A8_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
	 *邮件领取附件请求
	 * @author Administrator
	 * 
	 */

class CCMD1A8 : public Packet
{
public:
	CCMD1A8() : a_mailId(0)
	{}
	virtual ~CCMD1A8() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_COMMU_MAIL_REQUEST_ATTAC;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

	uint32 a_mailId;		//邮件唯一ID
};


class CCMD1A8Factory: public MessageFactory
{
public :

	virtual ~CCMD1A8Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_MAIL_REQUEST_ATTAC;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif