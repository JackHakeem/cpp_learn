#ifndef _SCMD24B_H_
#define _SCMD24B_H_
#include "../../network/Packet.h"
#include "../../message/MessageFactory.h"
#include "../../message/SocketCMDConst.h"

class SCMD24B : public Packet
{
public:
	SCMD24B() 
	{
		a_roleErrorNum = 0;
		b_roleName = "";
	}
	virtual ~SCMD24B() {}


	virtual bool Read();
public :
	virtual int32 Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_REGISTER_RESP;}

	virtual	int32 GetMessageSize( ) const { return 0;}

public:
	uint16 a_roleErrorNum;
	std::string b_roleName;
};


class SCMD24BFactory: public MessageFactory
{
public :
	virtual ~SCMD24BFactory ()  {}

	virtual Packet* CreateMessage () {return new SCMD24B();}

	virtual PacketID_t GetPacketID ()const  {return GMSG_COMMU_REGISTER_RESP;}

	virtual uint32 GetMessageMaxSize ()const  {return 0;}

};

class SCMD24BHandler 
{
public:
	static uint32 Execute(SCMD24B* pPacket) ;
};
#endif