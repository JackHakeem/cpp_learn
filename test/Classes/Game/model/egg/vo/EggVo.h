#pragma once

#include "BaseType.h"

struct EggVo
{
	EggVo()
	{
		type = 0;
		smallType = 0;
		quality = 0;
		tips = "";
	}

	int32 type;			// 蛋大类(1装备蛋2佣兵蛋3资源蛋)
	int32 smallType;		// 资源蛋小类(1金币2银币3历练4精力5名声6魔石)
	int32 quality;		// 品质(1蓝2紫3橙4红101大102小)
	std::string tips;		// 客户端用来描述蛋的tips
};