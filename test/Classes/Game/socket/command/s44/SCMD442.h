/**
 
 */
#ifndef _SCMD442_H_
#define _SCMD442_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD442 : public Packet
{
public:
	SCMD442() {
		a_NextWorldBossTime = 0;
		b_NextGongTime = 0;
		c_NextSilverMineTime = 0;
	}
	virtual ~SCMD442() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_GONG_OPENTIME;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint32 a_NextWorldBossTime;
	uint32 b_NextGongTime;
	uint32 c_NextSilverMineTime;
};


class SCMD442Factory: public MessageFactory
{
public :

	virtual ~SCMD442Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD442();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_GONG_OPENTIME;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD442Handler 
{
public:
	static uint32 Execute(SCMD442* pPacket) ;
};

#endif