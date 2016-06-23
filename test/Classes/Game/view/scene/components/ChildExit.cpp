#include "ChildExit.h"

ChildExit::ChildExit()
{
	sp = CCSprite::spriteWithSpriteFrameName("map/child_exit.png");
	if(sp)
	{
		addChild(sp);
		sp->setIsVisible(false);
	}
}

void ChildExit::layout()
{

}
void ChildExit::areaLev(int value)
{
	if(value >= 1 && value <= 4)
	{
		//(__skin["_fmNumber"] as MovieClip).gotoAndStop(value);
	}
}
void ChildExit::areaStar(int value)
{
	if(!sp)
		return;

	if(value >= 1 && value <= 3)
	{
		if(sp->getIsVisible())
			sp->setIsVisible(false);
		else
			sp->setIsVisible(true);

		//__skin["_fmStar"].gotoAndStop(value+1);
	}
	else
	{
		if(sp->getIsVisible())
			sp->setIsVisible(false);
		else
			sp->setIsVisible(true);

		//__skin["_fmStar"].gotoAndStop(1);
	}
}
void ChildExit::data(WorldExitData data)
{
	_data = data;
	_id = _data.id;
	areaStar(_data.areaStar);
}
WorldExitData ChildExit::data()
{
	return _data;
}
void ChildExit::dispose()
{

}

int ChildExit::id()
{
	return _id;
}

void ChildExit::id(int value)
{
	_id = value;
}