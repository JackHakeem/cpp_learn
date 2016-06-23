#ifndef _CCMD1AA_H_
#define _CCMD1AA_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
	 *邮件数目请求
	 * @author Administrator
	 * 
	 */

class CCMD1AA : public Packet
{
public:
	CCMD1AA()
	{}
	virtual ~CCMD1AA() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_COMMU_MAIL_COUNTINFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

};


class CCMD1AAFactory: public MessageFactory
{
public :

	virtual ~CCMD1AAFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_MAIL_COUNTINFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif