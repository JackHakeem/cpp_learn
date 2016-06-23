/**
 
 */
#ifndef _SCMD446_H_
#define _SCMD446_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "model/gong/vo/GongRanking.h"


class SCMD446 : public Packet
{
public:
	SCMD446() {
	}
	virtual ~SCMD446() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_GONG_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:


	uint32 a_wave;
	std::vector<GongRanking> b_ranking;
};


class SCMD446Factory: public MessageFactory
{
public :

	virtual ~SCMD446Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD446();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_GONG_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD446Handler 
{
public:
	static uint32 Execute(SCMD446* pPacket) ;
};

#endif