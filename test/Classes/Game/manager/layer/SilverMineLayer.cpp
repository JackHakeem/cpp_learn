#include "SilverMineLayer.h"
#include "manager/OverPanelManage.h"
#include "manager/PopEventName.h"
#include "manager/TouchLayerEnum.h"

USING_NS_CC;

SilverMineLayer::SilverMineLayer()
{
	this->setIsTouchEnabled(true);

	setLastItemGID(NONEINT);
}

SilverMineLayer::~SilverMineLayer()
{}

//CC_PROPERTY(int32, _lastItemGID, LastItemGID)
int32 SilverMineLayer::getLastItemGID()
{
	return _lastItemGID;
}

void SilverMineLayer::setLastItemGID(int32 var)
{
	_lastItemGID = var;
}

//begin

void SilverMineLayer::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::SilverMineLayer, true);
}

bool SilverMineLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	return false;
}

void SilverMineLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{	

}

void SilverMineLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{

} 
