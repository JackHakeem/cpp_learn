#ifndef HLQS_StoryVo_H_
#define HLQS_StoryVo_H_
#include "StoryElement.h"
#include "StoryScript.h"

USING_NS_CC;

class StoryVo
{
public:
	int id;
	std::vector<StoryElement> elemenet;
	std::vector<StoryScript> script;
	int x;
	int y;
	int arrt;
public:
	StoryVo()
	{
		id = 0;
		x = 0;
		y = 0;
		arrt = 0;
	}
};

#endif