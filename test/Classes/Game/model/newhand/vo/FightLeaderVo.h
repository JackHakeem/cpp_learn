#ifndef _FIGHT_LEADER_VO_H_
#define _FIGHT_LEADER_VO_H_

#include "BaseType.h"

class FightLeaderVo
{
public:
	FightLeaderVo() {}
	~FightLeaderVo() {}

	int map;
	int progress;
	string info;
	string btn;
	//		public var timer:int = 5;	//2012-01-11 �߻�Ҫ���Ƴ���������
};
#endif