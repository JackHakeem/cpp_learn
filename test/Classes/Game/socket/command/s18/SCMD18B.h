#ifndef _SCMD18B_H_
#define _SCMD18B_H_
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
WMSG_WORLD_UPDATE_HP = 0x18b (395)
Client -> server-side package structure (none)
 */

class SCMD18B : public Packet
{
public:
	SCMD18B() 
	{
		a_figure = 0;
		b_maxHp = 0;
		c_difference = 0;
	}
	virtual ~SCMD18B() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_UPDATE_HP	;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	int32 a_figure;
	int32 b_maxHp;
	int32 c_difference;
};


class SCMD18BFactory: public MessageFactory
{
public :

	virtual ~SCMD18BFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD18B();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_UPDATE_HP	;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD18BHandler 
{
public:
	static uint32 Execute(SCMD18B* pPacket) ;
};

#endif 