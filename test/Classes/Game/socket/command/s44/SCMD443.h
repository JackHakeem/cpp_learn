/**
 
 */
#ifndef _SCMD443_H_
#define _SCMD443_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD443 : public Packet
{
public:
	SCMD443() {
		a_wave = 0;
		b_servertime = 0;

	}
	virtual ~SCMD443() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_GONG_PROGRESS;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint32 a_wave;
	uint32 b_servertime;
	std::vector<uint8> c_monsterInfo;
};


class SCMD443Factory: public MessageFactory
{
public :

	virtual ~SCMD443Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD443();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_GONG_PROGRESS;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD443Handler 
{
public:
	static uint32 Execute(SCMD443* pPacket) ;
};

#endif