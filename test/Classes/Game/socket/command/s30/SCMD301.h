/**
* Push to the client mercenary list dismissed
* WMSG_WORLD_MERCENARY_RECRUITED = 0x301
* Server -> client package structure
* The number of short of dismissal mercenary (once recruited)
*	Uint32, mercenary unique ID
*	Uint16 mercenary prototype ID
*	Uint8 mercenary grade.
*	Uint16 mercenary wrist
*	Uint16 mercenaries intelligence.
*	Uint16 mercenary physical
 */ 

#ifndef _SCMD301_H_
#define _SCMD301_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

struct SCMD301Node
{
	int32 a_mercenaryId;
	int16 b_prototypeId;
	int8 c_level;
	int32 d_exp;
	int16 e_strength;
	int16 f_intellect;
	int16 g_stamina;
	int16 i_skill;
	int8 j_reborn;
	uint32 k_maxHp;
};

class SCMD301 : public Packet
{
public:
	SCMD301() {}
	virtual ~SCMD301() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_MERCENARY_RECRUITED;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16	count;
	std::vector<SCMD301Node> a_mercenarys;
};


class SCMD301Factory: public MessageFactory
{
public :
	
	virtual ~SCMD301Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD301();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_MERCENARY_RECRUITED;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD301Handler 
{
public:
	static uint32 Execute(SCMD301* pPacket) ;
};

#endif