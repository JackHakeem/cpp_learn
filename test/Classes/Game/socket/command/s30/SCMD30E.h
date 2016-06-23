/**
* Replace the mercenary skills return package
* WMSG_WORLD_MERCENARY_SKILL_ENABLED = 0x30E
* Server -> client package structure
* Uint8 is successful
* Uint32, mercenary unique ID
* The uint8 skill type
* The uint16 skill ID
* The uint16 replaced the skill ID
 */

#ifndef _SCMD30E_H_
#define _SCMD30E_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD30E : public Packet
{
public:
	SCMD30E()
	{
		a_isSucceed = 0;
		b_merId = 0;
		c_skillRank = 0;
		d_skillId = 0;
		e_exSkillId = 0;
	}

	virtual ~SCMD30E() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_MERCENARY_SKILL_ENABLED;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8	a_isSucceed;
	int32	b_merId;
	int8	c_skillRank;
	int16	d_skillId;
	int16	e_exSkillId;
};


class SCMD30EFactory: public MessageFactory
{
public :
	
	virtual ~SCMD30EFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD30E();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_MERCENARY_SKILL_ENABLED;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD30EHandler 
{
public:
	static uint32 Execute(SCMD30E* pPacket) ;
};

#endif