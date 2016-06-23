#ifndef _ARENAREPORTVO_H_
#define _ARENAREPORTVO_H_

#include "BaseType.h"

class ArenaReportVo
{
public:
	ArenaReportVo()
	{
		fightTime = 0;
		isChallenge = 0;
		std::string enemyName = "";
		rank = 0;
		fightingId1 = 0;
		fightingId2 = 0;
	}

	int32 fightTime;		//battle time
	int32 isChallenge;		//whether challenger (1 is true)
	int32 isSuccess;		//win or not (1 is win)
	std::string enemyName;	//enemy name
	int32 rank;				// ranking (0:no change, positive:up to, negative:down to)
	int32 fightingId1;
	int32 fightingId2;
};

#endif
