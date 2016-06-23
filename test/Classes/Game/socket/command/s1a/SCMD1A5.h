/**
		 * 回应用户删除邮件结果
		 * 
		 */	

#ifndef _SCMD1A5_H_
#define _SCMD1A5_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD1A5 : public Packet
{
public:
	SCMD1A5():a_result(0) {}
	virtual ~SCMD1A5() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_MAIL_DELETE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint16 a_result;	//处理结果(返回结果见：服务端返回错误码)
};


class SCMD1A5Factory: public MessageFactory
{
public :
	
	virtual ~SCMD1A5Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1A5();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_MAIL_DELETE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1A5Handler 
{
public:
	static uint32 Execute(SCMD1A5* pPacket) ;
};

#endif 