#ifndef HLQS_SkillVo_H_
#define HLQS_SkillVo_H_
#include "cocos2d.h"

class SkillVo
{
public:
	int id;
	std::string name;
	int resId;
	int pListId;// Jae add on 2012.6.6
	int longAttack;
	int rank;
	int icon;
	int level;
	std::string des;
	int musid;
	int nameid;
	int shift;
	int combo;
    int actzhen;
    float acttime;
	float offsetX;
	float offsetY;
	float offsetX2;
	float offsetY2;
	char flipX;
	char flipY;
	float scale;
public:
	SkillVo()
	{
		id = 0;
		resId = 0;
		pListId = 0;
		longAttack = 0;
		rank = 0;
		icon = 0;
		level = 0;
		musid = 0;
		nameid = 0;
		shift = 0;
		combo = 99;
        actzhen = 0;
        acttime = 0.0f;
		offsetX = 0.0f;
		offsetY = 0.0f;
		offsetX2 = 0.0f;
		offsetY2 = 0.0f;
		flipX = 0;
		flipY = 0;  
		scale = 0.0f;
	}
};

#endif