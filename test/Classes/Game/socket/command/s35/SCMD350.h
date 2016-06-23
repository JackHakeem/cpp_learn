/**
* xp update package
* WMSG_WORLD_UPDATE_EXP = Ox350, (848)
* the server-> the client, package structure
* int32: role ID
* Int32: experience value
* Int8: character level
* Int8: whether to upgrade (0 no, 1 is)
 */ 

#ifndef _SCMD350_H_
#define _SCMD350_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD350 : public Packet
{
public:
	SCMD350()
	{
		a_figureId = 0;
		b_isReborn = 0;
		c_exp = 0;
		d_lev = 0;
		e_isUpgrade = 0;
	}

	virtual ~SCMD350() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_UPDATE_EXP;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	int32 a_figureId;
	int8 b_isReborn;
	int32 c_exp;
	int8 d_lev;
	int8 e_isUpgrade;
};


class SCMD350Factory: public MessageFactory
{
public :

	virtual ~SCMD350Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD350();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_UPDATE_EXP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD350Handler 
{
public:
	static uint32 Execute(SCMD350* pPacket) ;
};

#endif