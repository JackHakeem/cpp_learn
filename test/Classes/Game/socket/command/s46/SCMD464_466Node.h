#pragma once

#include "BaseType.h"

struct SCMD464_465Node
{
	SCMD464_465Node()
	{
		a_sitGrid = 0;
		b_id = 0;
		c_goodId = 0;
		d_lv = 1;
		e_curexp = 0;
		f_isnew = 0;
	}

	uint8 a_sitGrid; // XHpos
	uint32 b_id; // the world's XH only Id 
	int32 c_goodId; // XH config Id
	uint8 d_lv; //current level
	uint32 e_curexp;//current exp
	int8	f_isnew;
};
