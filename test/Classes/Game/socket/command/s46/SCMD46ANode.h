#pragma once

#include "BaseType.h"

struct SCMD46ANode
{
	SCMD46ANode()
	{
		a_roldId = 0;
		b_sitGrid = 0;
		c_id = 0;
		d_goodId = 0;
		e_lv = 1;
		f_curexp = 0;
	}

	uint32 a_roldId;//Ó¶±øID
	uint8 b_sitGrid; // XH  pos
	uint32 c_id; // the world's XH only Id 
	int32 d_goodId; // XH config Id 
	uint8 e_lv;//current level
	uint32 f_curexp;//current exp
};
