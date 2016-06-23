#pragma once
#include "BaseType.h"
/**
 * 银矿阵营信息数组：
	Uint32	银矿ID
	Uint32  当前玩家数 
	int8	当前占领阵营ID（-1：空矿；0~2：阵营ID）
	uint8	是否双倍矿（0：否；1：是）
 */

class SCMD2E6Node
{
public:
	SCMD2E6Node()
	{
		memset(this, 0, sizeof(SCMD2E6Node));
	}
	uint32 a_mineId;
	uint32 b_online;
	int8 c_mineType;
	int8 d_isDouble;
};