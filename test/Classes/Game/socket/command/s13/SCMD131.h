/**
	* PVE Raiders began fighting
	* WMSG_WORLD_BATTLE_REPORT_START = 0x135 (309),
	* Server -> client package structure
	* Int: battle scenes ID
	* Int: monster combination of ID
	* Uint16: formation ID
	* Short: Participation station mercenaries number
	*	Short: mercenary ID
	*	Byte: Location
	*	Byte: Level
	*	Int: HP
	*	Short: ordinary skill ID
	*	Short: the esoteric skills of ID
	*	Short: Passive skill ID
	*	Char: mercenary name
	*	char: mercenary Avatar
	* Int the player ID (used to group warfare systems)
	* /

	/ **
	* PVE Raiders began fighting
	* WMSG_WORLD_BATTLE_REPORT_START = 0x135 (309),
	* Server -> client package structure
	* Int: battle scenes ID
	* Int: monster combination of ID
	* Short: Participation station mercenaries number
	*	Short: mercenary ID
	*	Byte: Location
	*	Byte: Level
	*	Uint32,: the current HP
	*	Short: ordinary skill ID
	*	Short: the esoteric skills of ID
	*	Short: Passive skill ID
	*	Char: mercenary name
	*	char: mercenary Avatar
	*/

#ifndef _SCMD131_H_
#define _SCMD131_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

struct SCMD131Node
{
	int16		a_id;		//Ô­ÐÍ±àºÅ
	int8		b_station;
	int8		c_lev;
	int32		d_hp;
	int16		e_skill1; 
	int16		f_skill2;
	int16		g_skill3;
	std::string h_name;
	std::string i_cloth;
	int32       j_maxHp;
	int16		k_startEP;



	SCMD131Node()
	{
		a_id = 0;
		b_station = 0;
		c_lev = 0;
		d_hp = 0;
		e_skill1 = 0;
		f_skill2 = 0;
		g_skill3 = 0;
		j_maxHp = 0;
		k_startEP = 0;
	}
};

class SCMD131 : public Packet
{
public:
	SCMD131() {}
	virtual ~SCMD131() {}


	virtual bool	Read();
public :
	virtual int32 	Execute(); 

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_BATTLE_PVE_START;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
		
	int32			a_BattleId;
	int32			b_GroupId;
	int16			c_formationId;
	int16			d_SCMD131NodeNum;
	std::list<SCMD131Node> d_SCMD131Node;
	int16			e_playerId;
};


class SCMD131Factory: public MessageFactory
{
public :
	
	virtual ~SCMD131Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD131();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_BATTLE_PVE_START;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD131Handler 
{
public:
	static uint32 Execute(SCMD131* pPacket) ;
};

#endif 