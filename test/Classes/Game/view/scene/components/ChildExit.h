#ifndef HLQS_ChildExit_H_
#define HLQS_ChildExit_H_
#include "cocos2d.h"
USING_NS_CC;

struct WorldExitData
{
	int id;
	std::string name;
	int areaStar;
	int state;
	WorldExitData()
	{
		id = 0;
		areaStar = 0;
		state = 0;
	}
};

class ChildExit: public CCLayer
{
public:
	CCSprite* sp;
	WorldExitData _data;
	int _id;

public:
	ChildExit();
	void layout();
	void areaLev(int value);
	void areaStar(int value);
	void data(WorldExitData);
	WorldExitData data();
	void dispose();
	int id();
	void id(int value);
};

#endif