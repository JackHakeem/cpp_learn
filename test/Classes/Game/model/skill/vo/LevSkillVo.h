#ifndef HLQS_LevSkillVo_H_
#define HLQS_LevSkillVo_H_

class LevSkillVo
{
public:
	int id;
	int lev;
	std::string des;
	int silver;
	int roleLevel;
	int skillEXP;
	int cdTime;
	std::vector<int> arrParam;
	int prevSkillID;
	int prevSkillLevel;

public:
	LevSkillVo()
	{
		id = 0;
		lev = 0;
		silver = 0;
		roleLevel = 0;
		skillEXP = 0;
		cdTime = 0;
		prevSkillID = 0;
		prevSkillLevel = 0;
	}
};

#endif