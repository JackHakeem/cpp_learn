#include "ChildExitContainer.h"

ChildExitContainer::ChildExitContainer()
{
	radius1 = 50;
	radius2 = 36;
	//startAngle;
	//spaceAngle;

	_itemWidth = 315.0f * 3.14159/ 180.0f;
	_itemVal = 2* asin(radius2 / (radius1+radius2));
	_itemWidth = 70;
	_itemVal = 2;
}

void ChildExitContainer::data(std::vector<WorldExitData>& data)
{
	_data = data;
	layout();
}

std::vector<WorldExitData>* ChildExitContainer::data()
{
	return &_data;
}

void ChildExitContainer::layout()
{
	clear();
	std::vector<WorldExitData>::iterator iter = _data.begin();
	for(int i = 0; iter != _data.end(); ++iter, ++i)
	{
		addChildExit(i, *iter);
	}
}

void ChildExitContainer::addChildExit(int num, WorldExitData& data)
{
	ChildExit* child = new ChildExit();
	child->data(data);
	//setPosition1(child, num);
	if(child->getParent() == NULL)
		addChild(child);
}

void ChildExitContainer::setPosition1(ChildExit* child, int num)
{
	if(!child)
		return;

	int sum = _data.size();
	int subWidth = (_itemWidth * sum + _itemVal * (sum - 1)) / 2;
	int startx = - subWidth;

	CCPoint pos = getPosition();
	float x = startx + num * (_itemWidth + _itemVal) + 36;
	float y = pos.y < 120 ? 70 :-80;

	child->setPosition(x, y);
	//TweenLite.from(child, 0.3, {x:0 , y:0, alpha:0, onComplete:TweenLiteComplete, onCompleteParams:[child]});

	child->areaLev(num + 1);
}

void ChildExitContainer::clear()
{

	CCArray * pArray = getChildren();
	CCObject* pObject = NULL;
	ChildExit* child = NULL;
	CCARRAY_FOREACH(pArray, pObject)
	{
		if(pObject == NULL)
			continue;

		child = (ChildExit*)pObject;
		removeChild(child, true);
	}
}

void ChildExitContainer::dispose()
{

}