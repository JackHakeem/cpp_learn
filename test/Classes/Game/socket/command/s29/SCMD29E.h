#ifndef _SCMD29E_H_
#define _SCMD29E_H_
#include "../../network/Packet.h"
#include "../../message/MessageFactory.h"
#include "../../message/SocketCMDConst.h"

class SCMD29E : public Packet
{
public:
	SCMD29E() {}
	virtual ~SCMD29E() {}


	virtual bool Read();
public :
	virtual int32 Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_VIP_AWARD_INFO_RESP;}

	virtual	int32 GetMessageSize( ) const { return 0;}

public:
	int32 a_num;
};


class SCMD29EFactory: public MessageFactory
{
public :
	virtual ~SCMD29EFactory ()  {}

	virtual Packet* CreateMessage () {return new SCMD29E();}

	virtual PacketID_t GetPacketID ()const  {return WMSG_WORLD_VIP_AWARD_INFO_RESP;}

	virtual uint32 GetMessageMaxSize ()const  {return 0;}

};

class SCMD29EHandler 
{
public:
	static uint32 Execute(SCMD29E* pPacket) ;
};
#endif