#ifndef HLQS_StoryScript_H_
#define HLQS_StoryScript_H_

USING_NS_CC;

class StoryScript
{
public:

	int index; // elements order 0. 0 are generally themselves
	int id;
	std::string type; // element type
	int isNew; // whether new
	int tox; // move to x
	int toy; // move to y
	int dialog; // dialogue Numbers > 0 have dialog = 0 no dialogue = 1 disappear
	int dir; // dialogue display position 0 means left 1 said right
	int _tox; // move to x
	int _toy; // move to y
	bool move;
	int duration; // whether there is a timing trigger the next unit: milliseconds
	int resid;		// 
public:
	StoryScript()
	{
		index = 0; // elements order 0. 0 are generally themselves
		id = 0;
		isNew = 0; // whether new
		tox = 0; // move to x
		toy = 0; // move to y
		dialog = 0; // dialogue Numbers > 0 have dialog = 0 no dialogue = 1 disappear
		dir = 0; // dialogue display position 0 means left 1 said right
		_tox = 0; // move to x
		_toy = 0; // move to y
		move = false;
		duration = 0; // whether there is a timing trigger the next unit: milliseconds
		resid = 0;
	}
};

#endif