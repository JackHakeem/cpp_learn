#pragma once

#include "BaseType.h"

class SilverMineVo
{
public:
	SilverMineVo():id(0), campId(0),online(0),isDouble(false)
	{
	}
	int id;				// 矿ID
	int campId;	 		// 阵营ID
	int online;			// 该矿当前玩家数 
	bool isDouble;	// 是否双倍矿 
};