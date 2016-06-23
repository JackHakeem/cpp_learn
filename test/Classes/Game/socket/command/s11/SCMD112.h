/**
* The players enter the field of vision
* WMSG_WORLD_PLAYER_VIEW_IN = 0x112, / / ​​the players enter the field of vision
*
Send players location map all visible
WMSG_WORLD_PLAYER_VIEW_GET = 0x11A (282), / / ​​Get a map of where the information

* Server -> client package structure
short: the number of players
int: account id
string: the role name
short: X-coordinate
short: Y-coordinate
string: the name of the Association in to an empty string
uint32,: Max HP
uint32 current hp
uint16 current energy
uint16 protagonist mercenary prototype Id
the uint8 current players protagonist grade
int32 facelift type
MoveInfo current player's mobile
Short current player's threat degree


 */
#ifndef _SCMD112_H_
#define _SCMD112_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "SCMD111.h"

struct SCMD112Node
{
	int32 a_AccountId;
	std::string b_RoleName;
	int16 c_x;
	int16 d_y;
	std::string e_guildName;
	int32 f_maxHp;
	int32 g_hp;
	int16 h_energy;
	int16 i_mercId;
	int8 j_roleLev;
	int32 k_avatar;
	std::vector<SCMD111Node> l_path;
	int16 m_weiXie;
	int16 n_title;

	SCMD112Node()
	{
		a_AccountId = 0;
		c_x = 0;
		d_y = 0;
		f_maxHp = 0;
		g_hp = 0;
		h_energy = 0;
		i_mercId = 0;
		j_roleLev = 0;
		k_avatar = 0;
		m_weiXie = 0;
		n_title = 0;
	}
};


class SCMD112 : public Packet
{
public:
	SCMD112()
	{
		/*a_mapId = 0;
		b_mapStatus = 0;
		c_isAward = 0;*/
	}

	virtual ~SCMD112() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_PLAYER_VIEW_IN;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	/*int16	a_mapId;
	int8	b_mapStatus;
	int8	c_isAward;*/
	std::vector<SCMD112Node>a_Accounts;
};


class SCMD112Factory: public MessageFactory
{
public :
	
	virtual ~SCMD112Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD112();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_PLAYER_VIEW_IN;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD112Handler 
{
public:
	static uint32 Execute(SCMD112* pPacket) ;
};

#endif