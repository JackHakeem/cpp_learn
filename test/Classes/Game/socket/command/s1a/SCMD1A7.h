/**
		 *回应用户发送邮件结果 
		 * 
		 */

#ifndef _SCMD1A7_H_
#define _SCMD1A7_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD1A7 : public Packet
{
public:
	SCMD1A7():a_result(0) {}
	virtual ~SCMD1A7() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_MAIL_SEND;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint16 a_result;
};


class SCMD1A7Factory: public MessageFactory
{
public :
	
	virtual ~SCMD1A7Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1A7();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_MAIL_SEND;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1A7Handler 
{
public:
	static uint32 Execute(SCMD1A7* pPacket) ;
};

#endif 