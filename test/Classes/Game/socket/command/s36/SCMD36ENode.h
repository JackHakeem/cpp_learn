#pragma once

#include "BaseType.h"

struct SCMD36ENode
{
	SCMD36ENode()
	{
		a_goodsId = 0;
		b_count = 0;
	}
	int16 a_goodsId;
	uint32 b_count;
};