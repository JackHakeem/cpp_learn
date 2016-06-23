/**
pass gift
WMSG_WORLD_DUNGEON_AWARD = 0x376(886),	
Short		map ID
 */

#ifndef _SCMD144_H_
#define _SCMD144_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD144 : public Packet
{
public:
	SCMD144()
	{
		a_honorid = 0;
	}

	virtual ~SCMD144() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_GET_ACHIVEMENT_AWARD_REPLY;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16 a_honorid;
	int8 b_sucess;
};


class SCMD144Factory: public MessageFactory
{
public :
	
	virtual ~SCMD144Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD144();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_GET_ACHIVEMENT_AWARD_REPLY;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD144Handler 
{
public:
	static uint32 Execute(SCMD144* pPacket) ;
};

#endif