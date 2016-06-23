#ifndef _HERORANKVO_H_
#define _HERORANKVO_H_

#include "BaseType.h"

class HeroRankVo
{
public:
	HeroRankVo()
	{
		rank = 0;
		id = 0;
		std::string name = "";
		lev = 0;
		threat = 0;
	}

	int32 rank; 
	int32 id;
	std::string name;
	int32 lev;
	int32 threat;
};

#endif
