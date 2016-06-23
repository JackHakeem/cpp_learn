/**
* End PVE combat
* WMSG_WORLD_BATTLE_FINISH = 0x133 (307),
* Server -> client package structure
* Int: battle scenes ID
* Byte: fighting type 0 = 1 PvE = qualifying = Challenge Cup 3 = resource Tian = pk 5 = team pve
* Byte:> 0 win; <0 the lost;
* Int: The total injured
* Byte: the number of turns
* Short: the number of members
* Byte: Location
* Int: HP
* /

/ ** SCMD133Node
* End PVE combat
* WMSG_WORLD_BATTLE_FINISH = 0x133 (307),
* Server -> client package structure
* Int: battle scenes ID
* Byte: 1win; 2lost;
* Int: The total injured
* Byte: the number of turns
* Short: the number of members
* Byte: Location
* Int: HP
 */

#ifndef _SCMD133_H_
#define _SCMD133_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD133 : public Packet
{
public:
	SCMD133()
	{
		a_BattleId = 0;
		b_type = 0;	
		c_win = 0;  
		d_damage = 0;
		e_round = 0;
	}
	virtual ~SCMD133()
	{

	}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_BATTLE_FINISH;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	struct SCMD133Node
	{
		int8	a_station;
		int32	b_hp;
	};

	int32	a_BattleId; 
	int8	b_type;	//	Fighting type
	int8	c_win;  // Changed to have signed a Byte> = wins
	int32	d_damage;
	int8	e_round;
	std::list<SCMD133Node>	f_members;
};


class SCMD133Factory: public MessageFactory
{
public :
	
	virtual ~SCMD133Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD133();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_BATTLE_FINISH;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD133Handler 
{
public:
	static uint32 Execute(SCMD133* pPacket) ;
};

#endif 