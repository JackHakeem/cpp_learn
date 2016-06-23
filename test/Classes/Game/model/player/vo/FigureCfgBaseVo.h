#ifndef HLQS_FigureCfgBaseInfoVo_h
#define HLQS_FigureCfgBaseInfoVo_h
#include "cocos2d.h"

class FigureCfgBaseVo
{
public:

	std::string explanation;
	int score;

	int mercId; // Numbers
	std::string name; // name
	bool isRole; // whether leading role
	int sex; // gender
	int careerId; // professional
	int color; // mercenaries color
	int strength; /* achievement */
	int intellect; // intelligence
	int hitRate; // hit
	int agility; // agility
	int crit; // crit
	int stamina; // physical
	int needPop; // reputation for
	int cloth; // model
	int maxHp; // basic health
	int lev; // default class
	int silver; // recruiting the silver COINS
	int exp; // default experience
	int order; // used to name the mercenaries are in order
	std::string requirement; // requirements
	std::vector < int > skill1; // working skills
	int skill2; // the upanishads skills
	std::vector<int> recommend; // recommend order
	std::vector<int> selected; // checked
	bool spiritAwoke;

public:
	FigureCfgBaseVo()
	{
		mercId= 0;
		isRole = false;
		sex = 0;
		careerId = 0;
		color = 0;
		strength = 0;
		intellect = 0;
		hitRate = 0;
		agility = 0;
		crit = 0;
		stamina = 0;
		needPop = 0;
		cloth = 0;
		maxHp = 15;
		lev = 1;
		silver = 0;
		exp = 0;
		order = 0;
		skill2 = 0;
		score = 0;
		spiritAwoke = false;
	}
};
#endif