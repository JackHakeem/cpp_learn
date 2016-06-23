/**
* Mercenary swap skills to return the package
WMSG_WORLD_MERCENARY_SKILL_EXCHANGED = 0x2FF (767)
The service side -> client package structure
uint32 replacement by a unique ID
the uint16 replacement Skill ID
are uint32 be replace by a unique ID
are uint16 be to replace those skills ID
		 * 
		 */	

#ifndef _SCMD2FF_H_
#define _SCMD2FF_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD2FF : public Packet
{
public:
	SCMD2FF() {}
	virtual ~SCMD2FF() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_MERCENARY_SKILL_EXCHANGED;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	int32 a_mercId1;
	int16 b_skill1;
	int32 c_mercId2;
	int16 d_skill2;
};


class SCMD2FFFactory: public MessageFactory
{
public :

	virtual ~SCMD2FFFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2FF();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_MERCENARY_SKILL_EXCHANGED;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2FFHandler 
{
public:
	static uint32 Execute(SCMD2FF* pPacket) ;
};

#endif