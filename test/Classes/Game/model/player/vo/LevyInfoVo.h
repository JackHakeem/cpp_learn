#ifndef HLQS_LevyInfoVo_h
#define HLQS_LevyInfoVo_h

class LevyInfoVo
{
public:
	int rest;
	int max;
	int reward;
	int cost;

public:
	LevyInfoVo()
	{
		rest = 0;
		max = 0;
		reward = 0;
		cost = 0;
	}
};
#endif