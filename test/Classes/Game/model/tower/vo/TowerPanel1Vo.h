#ifndef _TowerPanel1Vo_H_
#define _TowerPanel1Vo_H_

#include "BaseType.h"

class TowerPanel1Vo
{
public:
	TowerPanel1Vo()
	{
		freeTimes = 0;
		lastFloor = 0;
		maxFloor = 0;
		myRank = 0;

		topRank = "";
	}
	~TowerPanel1Vo() {}

public:
	int freeTimes;
	int lastFloor;
	int maxFloor;
	int myRank;
	string topRank;
};
#endif