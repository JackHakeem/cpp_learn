#include "SceneInfoVo.h"

SceneInfoVo::SceneInfoVo()
{
	reset();
}

void SceneInfoVo::reset()
{
	offsetX = 0;
	offsetY = 0;
	width = 2500;
	height = 700;
	id = 0;
	type = 0;
	blockW = 0;
	blockH = 0;
	for(int i = 0; i< MAX_CELLS_Y; ++i)
	{
		for(int j = 0; j< MAX_CELLS_X; ++j)
		{
			mapData[i][j] = 1;
		}
	}

	//for(int i = 0; i < MAX_CELLS_Y * MAX_CELLS_X; ++i)
	//{
	//	mapData[i] = 1;
	//}
	cellRows = 0;
	cellCols = 0;

	mapRoWs = 0;
	mapCols = 0;

}