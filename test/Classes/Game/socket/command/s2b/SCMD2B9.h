#ifndef  _SCMD2B9_H__
#define  _SCMD2B9_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
	开始跑商回应
	WMSG_WORLD_TRADE_BEGIN_RESP= 0x2B9 (697)
	服务端->客户端, 包结构
	short: 		0可以跑商, >0为相关ErrorCode 
 */

class SCMD2B9 : public Packet
{
public:
	SCMD2B9() {}
	virtual ~SCMD2B9() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_TRADE_BEGIN_RESP;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16 a_err;
};


class SCMD2B9Factory: public MessageFactory
{
public :

	virtual ~SCMD2B9Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2B9();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_TRADE_BEGIN_RESP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2B9Handler 
{
public:
	static uint32 Execute(SCMD2B9* pPacket) ;
};
#endif