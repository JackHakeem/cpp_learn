#ifndef HLQS_SkillInfo_H_
#define HLQS_SkillInfo_H_

class SkillInfo
{
public:

	int id;
	int lev;
	bool active;

public:
	SkillInfo()
	{
		id = 0;
		lev = 0;
		active = false;
	}
};

#endif