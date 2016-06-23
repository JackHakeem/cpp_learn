/**

* PVP or PK fighting began
WMSG_WORLD_BATTLE_PVP_START = 0x13C (316),
The service side -> client package structure
int: the battle scenes ID
uint16: attacking side Formation ID
uint16: the defending Formation ID
short: the number of Senate station mercenary
	short: mercenary ID
	byte: location
	Priority byte:
	int: the HP
	short: of ordinary skill ID
	short: the esoteric skills of ID
	short: Passive skill ID
	char: mercenary name
	char: mercenary Avatar
 */

#ifndef _SCMD13C_H_
#define _SCMD13C_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "SCMD131.h"

class SCMD13C : public Packet
{
public:
	SCMD13C() 
	{
		a_BattleId = 0;
		b_attackFid = 0;
		c_defendFid = 0;
	}

	virtual ~SCMD13C() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_BATTLE_PVP_START;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	//struct SCMD13CNode
	//{
	//	int16		a_id;		//Prototype No.
	//	int8		b_station;
	//	int8		c_lev;
	//	int32		d_hp;
	//	int16		e_skill1;
	//	int16		f_skill2;
	//	int16		g_skill3;
	//	std::string h_name;
	//	std::string i_cloth;
	//};
		
	int32			a_BattleId;
	int16			b_attackFid;
	int16			c_defendFid;
	std::list<SCMD131Node>	d_players;
};


class SCMD13CFactory: public MessageFactory
{
public :
	
	virtual ~SCMD13CFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD13C();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_BATTLE_PVP_START;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD13CHandler 
{
public:
	static uint32 Execute(SCMD13C* pPacket) ;
};

#endif 