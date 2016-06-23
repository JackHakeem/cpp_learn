#ifndef HLQS_FuncExitVo_H_
#define HLQS_FuncExitVo_H_

class FuncExitVo
{
public:
	int id;
	int type;
	int lev;
	int mapId;
	int npcId;

public:

	FuncExitVo()
	{
		id = 0;
		type = 0;
		lev = 0;
		mapId = 0;
		npcId = 0;
	}
};

#endif