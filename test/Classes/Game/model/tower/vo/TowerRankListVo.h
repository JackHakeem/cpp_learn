#ifndef _TowerRankListVo_H_
#define _TowerRankListVo_H_

#include "BaseType.h"
#include "TowerRankItemVo.h"

class TowerRankListVo
{
public:
	TowerRankListVo()
	{
		page = 0;
		maxFloor = 0;
		curFloor = 0;
		myRank = 0;
		restCount = 0;
		lastRank = 0;
	}
	~TowerRankListVo()
	{
		std::list<TowerRankItemVo*>::iterator it = rankList.begin();
		for ( ; it != rankList.end(); it++ )
		{
			TowerRankItemVo* item = *it;
			CC_SAFE_DELETE(item);
		}
	}

public:

	int page;
	int maxFloor;
	int curFloor;
	int myRank;
	int restCount;
	int lastRank;
	std::list<TowerRankItemVo*> rankList;
};
#endif