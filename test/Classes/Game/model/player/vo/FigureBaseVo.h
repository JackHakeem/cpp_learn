#ifndef HLQS_FigureBaseInfoVo_h
#define HLQS_FigureBaseInfoVo_h
#include "model/spirit/vo/LvSpiritVo.h"

class FigureBaseVo
{
public:
	int pAttack;
	int pDefense;
	int mAttack;
	int mDefense;
	int strength;
	int agility;
	int intellect;
	int hitRate;
	int dodge;
	int crit;
	int tough;
	int stamina;
	int plus_str;
	int plus_int;
	int plus_sta;
	int sp_str;
	int sp_int;
	int sp_sta;	
	int jadeId;
	int mercId;
	int silver;
	int rebornNum;
	std::string requirement;
	int attPoint;
	std::string recommend;
	std::string selected;
	bool spiritAwoke;
	std::vector<LvSpiritVo> spVec;

public:
	FigureBaseVo()
	{
		pAttack= 0;
		pDefense= 0;
		mAttack = 0;
		mDefense = 0;
		strength = 0;
		agility = 0;
		intellect = 0;
		hitRate = 0;
		dodge = 0;
		crit = 0;
		tough = 0;
		stamina = 0;
		plus_str = 0;
		plus_int = 0;
		plus_sta = 0;
		sp_str = 0;
		sp_int = 0;
		sp_sta = 0;	
		jadeId = 0;
		mercId = 0;
		silver = 0;
		rebornNum = 0;
		attPoint = 0;
		spiritAwoke = false;
	}
};
#endif