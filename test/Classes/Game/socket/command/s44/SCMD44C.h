/**
 
 */
#ifndef _SCMD44C_H_
#define _SCMD44C_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD44C : public Packet
{
public:
	SCMD44C() {
	}
	virtual ~SCMD44C() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_GONG_HEROINFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:


	int8 a_hasHero;
	std::string b_heroName;
};


class SCMD44CFactory: public MessageFactory
{
public :

	virtual ~SCMD44CFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD44C();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_GONG_HEROINFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD44CHandler 
{
public:
	static uint32 Execute(SCMD44C* pPacket) ;
};

#endif