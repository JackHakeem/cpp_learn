#ifndef HLQS_StoryElement_H_
#define HLQS_StoryElement_H_
#include "cocos2d.h"

USING_NS_CC;

class StoryElement
{
public:

	int type; // types 0 1 2 plot their monster NPC // new 3 items
	int id; // themselves as 0 other for corresponding Numbers
	int vis; // 0 don't display 1 for display
	int x; // when the initial coordinates X
	int y; // when the initial coordinates Y
	int dir; // direction
public:
	StoryElement()
	{
		type = 0;
		id = 0;
		vis = 0;
		x = 0;
		y = 0;
		dir = 0;
	}
};

#endif