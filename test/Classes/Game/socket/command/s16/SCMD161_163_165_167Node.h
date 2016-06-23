#ifndef _SCMD161_163_165_167NODE_H_
#define _SCMD161_163_165_167NODE_H_

#include "BaseType.h"

struct SCMD161_163_165_167Node
{
	int8 a_sitGrid; // items where
	uint32 b_id; // the world's goods only Id (Items 0)
	int16 c_goodId; // items prototype Id (Items 0)
	int8 d_number; // number of items (If there are no items to 0)
	int8 e_superLv; // enhanced level of
	int16 f_stamina; // the magic of the physical number of
	int16 g_wrist; // the magic of the wrist a few
	int16 h_intellect; // Fel Intellect number

	int16 i_sp_stamina;
	int16 j_sp_wrist;
	int16 k_sp_intellect;
	int8 l_blue;
	int8 m_purple;
	int8 n_red;
};

#endif