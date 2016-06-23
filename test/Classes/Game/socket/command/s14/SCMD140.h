/**
pass gift
WMSG_WORLD_DUNGEON_AWARD = 0x376(886),	
Short		map ID
 */

#ifndef _SCMD140_H_
#define _SCMD140_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD140 : public Packet
{
public:
	SCMD140()
	{
		a_honorid = 0;
	}

	virtual ~SCMD140() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_ACHIVEMENT_REACHED;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16 a_honorid;
};


class SCMD140Factory: public MessageFactory
{
public :
	
	virtual ~SCMD140Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD140();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_ACHIVEMENT_REACHED;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD140Handler 
{
public:
	static uint32 Execute(SCMD140* pPacket) ;
};

#endif