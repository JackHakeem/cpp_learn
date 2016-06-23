#include "SceneUILayer.h"
#include "manager/TouchLayerEnum.h"

bool SceneUILayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}

	this->setIsTouchEnabled (true);
	return true;
}

void SceneUILayer::registerWithTouchDispatcher()
{
	this->setIsTouchEnabled (true);
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::SceneUILayer, true);
}

bool SceneUILayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	//CCLog("TLE::SceneUILayer");
	return false;
}