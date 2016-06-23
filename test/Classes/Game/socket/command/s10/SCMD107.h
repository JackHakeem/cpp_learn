/**
Line landed respond
WMSG_WORLD_LOGIN_RESPONSE = 0x107 (263) / / line node landing respond
The service side -> client package structure:
short: the current map Id
short: X-coordinate
short: Y-coordinate
uint32,: The protagonist of Id
string protagonist name
int32 silver
int32 gold
int32 experience
int32 reputation
short energy
uint32 current
uint8 the VIP level
uint32 recharge gold total
uint32 fatigue system accumulated time (in seconds)
byte: Account type / / 1 - tourists; 2 - an ordinary player;-GM
a uint8 existing number of training location
a uint8 existing Crystal queues
the string Association name
int32 magic spar number
 */

#ifndef _SCMD107_H_
#define _SCMD107_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD107 : public Packet
{
public:
	SCMD107()
	{
		a_AccountId = 0;
		b_mapId = 0;
		c_x = 0;
		d_y = 0;
		f_name = "";
		e_id = 0;
		g_silvere = 0;
		h_gold = 0;
		i_practice = 0;
		j_popularity = 0;
		k_energy = 0;
		_remainVigourBuffCount = 0;
		_gongExpBuffCount = 0;
		l_serverTime = 0;
		m_vipLev = 0;
		n_vipGold = 0;
		o_onlineTime = 0;
		p_accountType = 0;
		q_trainSitNum = 0;
		r_crystalListNum = 0;
		s_guildName = "";
		t_stone = 0;
		u_blue = 0;
		v_puple = 0;
		w_red = 0;
		x_isOnbussiness = 0;
		y_restTraderCnt = 0;
	}

	virtual ~SCMD107() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_LOGIN_RESPONSE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int32		a_AccountId;
	int16		b_mapId;
	int16		c_x;
	int16		d_y;
	int32		e_id;
	std::string f_name;
	int32		g_silvere;
	int32		h_gold;
	int32		i_practice;
	int32		j_popularity;
	int16		k_energy;
	int8		_remainVigourBuffCount;
	int32		_gongExpBuffCount;
	uint32		l_serverTime;
	int8		m_vipLev;
	uint32		n_vipGold;
	uint32		o_onlineTime;
	int8		p_accountType;
	int8		q_trainSitNum;
	int8		r_crystalListNum;
	std::string s_guildName;
	int32		t_stone;
	int32		u_blue;
	int32		v_puple;
	int32		w_red;
	int8		x_isOnbussiness;
	int16		y_restTraderCnt;
};


class SCMD107Factory: public MessageFactory
{
public :
	
	virtual ~SCMD107Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD107();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_LOGIN_RESPONSE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD107Handler 
{
public:
	static uint32 Execute(SCMD107* pPacket) ;
};

#endif 