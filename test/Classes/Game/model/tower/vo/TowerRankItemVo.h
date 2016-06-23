#ifndef _TowerRankItemVo_H_
#define _TowerRankItemVo_H_

#include "BaseType.h"

class TowerRankItemVo
{
public:
	TowerRankItemVo()
	{
		rank = 0;
		floor = 0;
		name = "";
		guild = "";
		lev = 0;
		date = "";
	}
	~TowerRankItemVo() {}

public:
	int rank;
	int floor;
	string name;
	string guild;
	int lev;
	string date;
};
#endif