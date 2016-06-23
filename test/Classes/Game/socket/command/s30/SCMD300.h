/**
* To the client push to recruit mercenaries ID list
* WMSG_WORLD_MERCENARY_RECRUIT_LIST = 0x300
* Server -> client package structure
* The short can recruit mercenaries number (never been to recruit)
*	Uint16 mercenaries ID.
 */ 

#ifndef _SCMD300_H_
#define _SCMD300_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD300 : public Packet
{
public:
	SCMD300() {}
	virtual ~SCMD300() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_MERCENARY_RECRUIT_LIST;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16	count;
	std::vector<int16> a_mercenarys;
};


class SCMD300Factory: public MessageFactory
{
public :
	
	virtual ~SCMD300Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD300();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_MERCENARY_RECRUIT_LIST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD300Handler 
{
public:
	static uint32 Execute(SCMD300* pPacket) ;
};

#endif