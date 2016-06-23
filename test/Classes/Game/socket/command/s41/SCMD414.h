#ifndef _SCMD414_H__
#define _SCMD414_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD414 : public Packet
{
public:
	SCMD414() {}
	virtual ~SCMD414() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_CHALLENAGE_VIGOUR_GET;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:	
	uint8 a_canChaTimes;
	uint8 b_buyTimes;
	//uint16 a_GUANeedVigour;
	//uint16 b_GUANeedVigour;
	//uint16 c_GUANeedVigour;
	uint16 d_GUANeedVigour;
};


class SCMD414Factory: public MessageFactory
{
public :

	virtual ~SCMD414Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD414();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_CHALLENAGE_VIGOUR_GET;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD414Handler 
{
public:
	static uint32 Execute(SCMD414* pPacket) ;
};
#endif