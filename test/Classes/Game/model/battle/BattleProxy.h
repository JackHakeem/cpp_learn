//
//  BattleProxy.h
//  HLQS_IPAD
//
//  Created by hui long on 12-2-29.
//  Copyright (c) 2012 4399. All rights reserved.
//


#ifndef HLQS_IPAD_BattleProxy_h
#define HLQS_IPAD_BattleProxy_h

#include "BaseType.h"


using namespace cocos2d;

class BattleProxy
{
private:
    BattleProxy();
    ~BattleProxy();


public:
	struct SCMD131Node
	{
		int16		a_id;

		int8		b_station;
		int8		c_lev;
		int32		d_hp;
		int16		e_skill1;
		int16		f_skill2;
		int16		g_skill3;
		std::string h_name;
		std::string i_cloth;
	};
    
	int32			a_BattleId_131;
	int32			b_GroupId;
	int16			c_formationId;
	int16			d_SCMD131NodeNum;
	std::list<SCMD131Node>	d_SCMD131Node;
	int16			e_playerId;


public:
    int16 SCMD132Node3Num;
	struct SCMD132Node3
	{
		int8  a_hitedId;
		int32 b_hitedhp;
		int16 c_hitedmp;
		int32 d_damage;
		int32 e_diffEp;
		int8  f_buffType;

		int8  g_state ;

	};
    
    int16 SCMD132Node2Num;
	struct SCMD132Node2
	{
		int8	a_hitedId;
		int8	b_crit;
		int32	c_hitedhp;
		int16	d_hitedmp;
		int32	e_damage;
		int8	f_buffType;

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
		int32	f_damage;
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
		int8	f_buffType;

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
    
	int32						a_BattleId_132;
	int8						b_round;

	std::list<SCMD132Node1>		c_Actions;
	std::list<SCMD132Node4>		d_buffs;


public:
	struct SCMD133Node
	{
		int8	a_station;
		int32	b_hp;
	};
    
	int32	a_BattleId; 
	int8	b_type;

	int8	c_win;

	int32	d_damage;
	int8	e_round;
    int16 SCMD133NodeNum;
	std::list<SCMD133Node>	f_members;
    
public:
    static BattleProxy * getInstance();
};

#endif
