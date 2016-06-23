
#ifndef _SCMD139_H_
#define _SCMD139_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD139 : public Packet
{
public:
	SCMD139() {}
	virtual ~SCMD139() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_BATTLE_UPDATE_ROLE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	struct SCMD139Node
	{
		int32		a_roleId;		// Prototype No.
		int32		b_maxHP;
		int32		c_hp;
		int32		d_exp;
		int8		e_lev;
	};

	std::vector<SCMD139Node> roles;

};


class SCMD139Factory: public MessageFactory
{
public :
	
	virtual ~SCMD139Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD139();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_BATTLE_UPDATE_ROLE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD139Handler 
{
public:
	static uint32 Execute(SCMD139* pPacket) ;
};

#endif 