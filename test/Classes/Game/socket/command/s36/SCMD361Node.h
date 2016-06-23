#pragma once

#include "BaseType.h"

struct SCMD361Node
{
	SCMD361Node()
	{
		a_rank = 0;
		b_accountId = 0;
		c_name = "";
		d_level = 0;
		e_mercid = 0;
		f_win =0;
	}
	int32 a_rank;
	int32 b_accountId;
	std::string c_name;
	int32 d_level;
	int16 e_mercid;	
	int8 f_win; //hwj
};