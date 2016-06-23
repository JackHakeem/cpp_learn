/**
	PVE combat content (the location of the attacking side 1-9, the defending side position 11-19)
	WMSG_WORLD_BATTLE_CONTENT = 0x132 (306),
	The service side -> client package structure
	int: the battle scenes ID
byte: The first few rounds
	  short: the action times
	  short: to produce BUFF effect of the number of
	  * /

	  / ** SCMD132Node1
byte: an attacker position
byte: resonance by location
	  short: Attack Skill ID
	  int: an attacker HP
	  short: an attacker EP
	  int: hurt (plus blood, to pay for the reduction of blood)
	  short: the number of targets (maximum of not more than 9)
	  * /

	  / ** SCMD132Node2
	  * Byte: number of an attacker
	  * Byte: crit
	  * Int: being attacked by HP
	  * Short: an attacker EP
	  * Int: Attacker Takes Damage of (positive plus blood, to pay for the reduction of blood)
	  * As byte: new buff type
	  * Byte: status of an attacker
	  * Short: the number of targets (not more than 9)
	  * /

	  / ** SCMD132Node3
	  * Byte: number of an attacker
	  * Int: being attacked by HP
	  * Short: an attacker EP
	  * Int: Attacker Takes Damage of (positive plus blood, to pay for the reduction of blood)
	  * Int: an attacker to add and subtract EP (plus the EP negative minus the EP) - temporarily remove
	  * As byte: new buff type
	  * Byte: status of an attacker
	  * /

	  / ** SCMD132Node4
byte: buff type
byte: buff has location
	  int: the owner of HP
	  short: the owner of EP
	  int: Damage
byte: EP changes in value
byte: the owner of state
byte: whether to remove the buff
	  short: the number of targets (maximum of not more than 9)
	  * /

	  / ** SCMD132Node5
	  * Byte: number of an attacker
	  * Int: being attacked by HP
	  * Short: an attacker EP
	  * Int: Attacker Takes Damage of (positive plus blood, to pay for the reduction of blood)
	  * Int: an attacker to add and subtract EP (plus the EP negative minus the EP) - temporarily do not have this ep
	  * As byte: new buff type
	  * Byte: status of an attacker
	  */

#ifndef _SCMD132_H_
#define _SCMD132_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD132 : public Packet
{
public:
	SCMD132() {}
	virtual ~SCMD132() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_BATTLE_CONTENT;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16 SCMD132Node3Num;
	struct SCMD132Node3
	{
		int8  a_hitedId;
		int32 b_hitedhp;
		int16 c_hitedmp;
		int32 d_damage;
		int32 e_diffEp;
		int8  f_buffType; //buffTypeVo
		int8  g_state ;  // Dodge status
	};

	 int16 SCMD132Node2Num;
	struct SCMD132Node2
	{
		int8	a_hitedId;
		int8	b_crit;
		int32	c_hitedhp;
		int16	d_hitedmp;
		int32	e_damage;
		int8	f_buffType; //buffTypeVo
		int8	g_state;  
		std::list<SCMD132Node3>	h_hiteds;
	};
	int16 SCMD132Node1Num;
	struct SCMD132Node1
	{
		int8	a_attackId;
		int8	b_resonanceId;
		int16	c_skill; 
		int32	d_attackhp;
		int16	e_attackmp;
		int32	f_buffType;
		std::list<SCMD132Node2>	g_hiteds;
	};
	int16 SCMD132Node5Num;
	struct SCMD132Node5
	{
		int8	a_hitedId;
		int32	b_hitedhp;
		int16	c_hitedmp;
		int32	d_damage;	
		int32	e_diffEp;
		int8	f_buffType; //buffTypeVo
		int8	g_state;
	};
	int16 SCMD132Node4Num;
	struct SCMD132Node4
	{
		int8	a_buffTtype;
		int8	b_id;
		int32	c_hp;
		int16	d_mp;
		int32	e_damage;
		int8	f_ep_damage;
		int8	g_state;
		int8	h_isremove;
		std::list<SCMD132Node5>	i_hiteds;
	};

	int32						a_BattleId;
	int8						b_round; 		//´Ó0¿ªÊ¼	
	std::vector<SCMD132Node1>		c_Actions;
	std::list<SCMD132Node4>		d_buffs;
};


class SCMD132Factory: public MessageFactory
{
public :
	
	virtual ~SCMD132Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD132();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_BATTLE_CONTENT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD132Handler 
{
public:
	static uint32 Execute(SCMD132* pPacket) ;
};

#endif 