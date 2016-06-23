#ifndef _SCMD285NODE1_H_
#define _SCMD285NODE1_H_

#include "BaseType.h"

struct SCMD285Node1
{
	SCMD285Node1()
	{
		a_goodsId = 0;
		b_num = 0;
	}
	int16 a_goodsId;
	uint32 b_num;
};


#endif