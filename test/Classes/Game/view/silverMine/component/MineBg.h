#pragma once

#include "BaseType.h"

#define MineBgCellCnt_x (8)
#define MineBgCellCnt_y (6)
#define MineBgCellMax (48)
#define MineBgCellLen_x (256)
#define MineBgCellLen_y (256)



class MineBg:public LayerNode
{
public:
	struct CELLPOINT
	{
		CELLPOINT(int xv, int yv)
		{
			x = xv, y=yv;
		}
		CCPoint localCellPos()
		{
			return ccp(MineBgCellLen_x*x, MineBgCellLen_y*y);
		}
		int x;
		int y;
	};

	MineBg();
	~MineBg();

	bool init();

	MineBg::CELLPOINT p2r_x(int x, int y);
public:
	SpriteNode* m_picArr[10][8];
};
