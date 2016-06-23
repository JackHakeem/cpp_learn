/**
Delivery to the client list passive skills
* WMSG_WORLD_PASSIVESKILL_INFO = 0 x319
* the server-> the client, package structure
* uint16 passive skill number
* uint16 passive skill ID
* uint8 passive skill level
* uint8 is enabled
 */ 

#ifndef _SCMD319_H_
#define _SCMD319_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

struct SCMD319Node
{
	int16 a_skillId ;         //Formation of a position
	int8 b_skillLel ;        //Mercenaries only ID
	int8 c_active;

	SCMD319Node()
	{
		a_skillId = 0;
		b_skillLel = 0;
		c_active = 0;
	}
}; 


class SCMD319 : public Packet
{
public:
	SCMD319() {}
	virtual ~SCMD319() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_PASSIVESKILL_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	std::vector<SCMD319Node> a_skills;
	 
	 
};


class SCMD319Factory: public MessageFactory
{
public :

	virtual ~SCMD319Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD319();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_PASSIVESKILL_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD319Handler 
{
public:
	static uint32 Execute(SCMD319* pPacket) ;
};

#endif 