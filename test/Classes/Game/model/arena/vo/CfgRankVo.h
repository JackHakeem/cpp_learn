#pragma once

#include "BaseType.h"

struct CfgRankVo
{
	CfgRankVo()
	{
		rank = 0;
		silver = 0;
		pop =0 ;
	}

	int rank;
	int silver;
	int pop;
	std::vector<int> interests;
};