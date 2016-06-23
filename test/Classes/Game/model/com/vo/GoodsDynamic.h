#ifndef _GOODSDYNAMIC_H_
#define _GOODSDYNAMIC_H_

#include "BaseType.h"

class GoodsDynamic
{
public:
	uint32 a_id; // items Id
	int32 b_goodID; // item type Id
	int32 c_sit; // items grid position
	int32 d_number; // item number
	int32 e_strengthen; // strengthen number
	int32 f_holds; // punched number
	int32 g_hold1; // hole one item type ID
	int32 h_hold2; // hole 2 item type ID
	int32 i_hold3; // hole three item type ID
	int32 j_att; // attack
	int32 k_def; // defense
	int32 l_magicAtt; // the attack
	int32 m_magicDef; // magic the
	int32 n_hit; // hit
	int32 o_dodge; // avoid
	int32 p_crit; // crit
	int32 q_back; // counterattack
	int32 r_hp; // blood
	int32 s_sell_price; // selling price
	char * t_propety;
	int32 u_stamina; // enchantment physical number
	int32 v_wrist; // enchantment number of achievement
	int32 w_intellect; // enchantment intelligence number
};

#endif