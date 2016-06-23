#ifndef _SCMD1EF_H_
#define _SCMD1EF_H_
#include "../../network/Packet.h"
#include "../../message/MessageFactory.h"
#include "../../message/SocketCMDConst.h"

class SCMD1EF : public Packet
{
public:
	SCMD1EF() {}
	virtual ~SCMD1EF() {}


	virtual bool Read();
public :
	virtual int32 Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_VIP_LEVEL;}

	virtual	int32 GetMessageSize( ) const { return 0;}

public:
	int8 a_vipLV;
};


class SCMD1EFFactory: public MessageFactory
{
public :
	virtual ~SCMD1EFFactory ()  {}

	virtual Packet* CreateMessage () {return new SCMD1EF();}

	virtual PacketID_t GetPacketID ()const  {return WMSG_WORLD_VIP_LEVEL;}

	virtual uint32 GetMessageMaxSize ()const  {return 0;}

};

class SCMD1EFHandler 
{
public:
	static uint32 Execute(SCMD1EF* pPacket) ;
};
#endif