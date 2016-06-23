/**
占星系统返回服务器信息
 */

#ifndef _SCMD460_H_
#define _SCMD460_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD460 : public Packet
{
public:

	SCMD460()
	{
		a_flag = 0;
	}

	virtual ~SCMD460() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_ZX_RESPONSE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint32 a_flag;
};


class SCMD460Factory: public MessageFactory
{
public :
	
	virtual ~SCMD460Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD460();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_ZX_RESPONSE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD460Handler 
{
public:
	static uint32 Execute(SCMD460* pPacket) ;
};

#endif