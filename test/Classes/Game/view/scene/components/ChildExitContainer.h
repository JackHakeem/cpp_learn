#ifndef HLQS_ChildExitContainer_H_
#define HLQS_ChildExitContainer_H_
#include "ChildExit.h"
USING_NS_CC;

class ChildExitContainer: public CCLayer
{
public:
	float radius1;
	float radius2;
	float startAngle;
	float spaceAngle;
	std::vector<WorldExitData> _data;
	std::map<int, ChildExit> childExitDic;
	float _itemWidth;
	float _itemVal;
public:
	ChildExitContainer();
	void data(std::vector<WorldExitData>&);
	std::vector<WorldExitData>* data();
	void layout();
	void addChildExit(int num, WorldExitData& data);
	void setPosition1(ChildExit* child, int num);
	void clear();
	void dispose();
};

#endif