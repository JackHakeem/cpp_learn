#ifndef HLQS_StoryModelVo_H_
#define HLQS_StoryModelVo_H_

USING_NS_CC;

class StoryModelVo
{
public:
	int id;			//Type 1 0 his monster 2 plot NPC / / new 3 items
	int resid;				// His other for 0 for corresponding Numbers
	std::string name;

public:
	StoryModelVo()
	{
		id = 0;
		resid = 0;
		name = "";
	}
};

#endif