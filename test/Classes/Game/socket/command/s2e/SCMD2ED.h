/**
 * 服务端返回下一次银矿战开启时间	
WMSG_SILVERMINE_OPENTIME = 0x2ED 
服务端->客户端, 包结构
uint32		下次银矿战开启时间
 */
#ifndef _SCMD2ED_H_
#define _SCMD2ED_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD2ED : public Packet
{
public:
	SCMD2ED() {}
	virtual ~SCMD2ED() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_SILVERMINE_OPENTIME;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint32 a_time;
	uint32 b_timeGong;
};


class SCMD2EDFactory: public MessageFactory
{
public :

	virtual ~SCMD2EDFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2ED();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_SILVERMINE_OPENTIME;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2EDHandler 
{
public:
	static uint32 Execute(SCMD2ED* pPacket) ;
};

#endif