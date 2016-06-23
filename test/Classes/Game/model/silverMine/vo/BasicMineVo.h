#pragma once

#include "BaseType.h"

class BasicMineVo
{
public:
	BasicMineVo()
	{
		memset(this, 0, sizeof(BasicMineVo));
	}
	int mineId;
	int mineLev;
	int xPos;
	int yPos;
	int x;
	int y;
		
};