/**
 *
 Push to the client mercenary basic information
 WMSG_WORLD_MERCENARY_BASE_INFO = 0x309 (777)
 The service side -> client package structure
 a_mercLim can recruit mercenaries
 The number of Short mercenary
	 the uint32 mercenary unique ID
	 the uint16 mercenary prototype ID
	 uint8 mercenary level
	 uint8 mercenary reincarnation of the number of
	 a uint32 mercenary experience
	 the uint32 mercenaries lives on the line
	 the uint32 mercenaries current value of life
	 uint16 mercenary wrist
	 uint16 mercenary intelligence
	 uint16 mercenary physique
	 the uint16 equipment special ID
	 the uint16 equipment esoteric skill ID
	 the uint16 equipment passive skill ID
 */

#ifndef _SCMD309_H_
#define _SCMD309_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

struct SCMD309Node
{
	int32 a_id;
	int16 b_typeId;
	int8 c_level;
	int8 d_ad_lv;
	int8 e_rebornNum;
	int8 f_exp_type;
	int32 g0_ad_exp;
	int32 g1_exp;
	int32 h_maxHp;
	int32 i_hp;
	int16 j_strength;
	int16 k_intellect;
	int16 l_stamina;
	int16 m_plus_str;
	int16 n_plus_intel;
	int16 o_plus_sta;
	int16 p_sp_str;
	int16 q_sp_intel;
	int16 r_sp_sta;
	int32  s_p_att;
	int32  t_p_def;
	int32  u_m_att;
	int32  v_m_def;
	int16 w_equipSkillId;
	int16 x_aoyiId;
	int16 y_passiveId;
	int32 z_att;

	SCMD309Node()
	{
		a_id = 0;
		b_typeId = 0;
		c_level = 0;
		d_ad_lv = 0;
		e_rebornNum = 0;
		f_exp_type = 0;
		g0_ad_exp = 0;
		g1_exp = 0;
		h_maxHp = 0;
		i_hp = 0;
		j_strength = 0;
		k_intellect = 0;
		l_stamina = 0;
		m_plus_str = 0;
		n_plus_intel = 0;
		o_plus_sta = 0;
		p_sp_str = 0;
		q_sp_intel = 0;
		r_sp_sta = 0;
		s_p_att = 0;
		t_p_def = 0;
		u_m_att = 0;
		v_m_def = 0;
		w_equipSkillId = 0;
		x_aoyiId = 0;
		y_passiveId = 0;
		z_att = 0;
	}
};

class SCMD309 : public Packet
{
public:
	SCMD309()
	{
		a_threat = 0;
		b_mercLim = 0;
	}

	virtual ~SCMD309() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_MERCENARY_BASE_INFO;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16	a_threat;
	int8		b_mercLim;
	std::list<SCMD309Node> c_mercInfo;
};


class SCMD309Factory: public MessageFactory
{
public :
	
	virtual ~SCMD309Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD309();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_MERCENARY_BASE_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD309Handler 
{
public:
	static uint32 Execute(SCMD309* pPacket) ;
};

#endif