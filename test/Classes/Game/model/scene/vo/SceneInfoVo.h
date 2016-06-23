#ifndef HLQS_SceneInfoVo_H_
#define HLQS_SceneInfoVo_H_
#include "BaseType.h"
//#define MAX_CELLS_X 200
//#define MAX_CELLS_Y 200

class SceneInfoVo
{
public:
	int offsetX;		//Map backgroundX offset
	int offsetY;		//Map backgroundY offset
	int width;
	int height;
	int blockW;
	int blockH;
	int id;
	int type;//Map types, 1, the city, 2, field
	int pid;
	std::string name;
	int level;
	char mapData[MAX_CELLS_X][MAX_CELLS_Y];
	//char mapData[MAX_CELLS_X * MAX_CELLS_Y];
	int cellRows;
	int cellCols;
	std::string sceneRoot;

	int mapRoWs;
	int mapCols;

public:
	SceneInfoVo();
	void reset();
};

#endif