#include "ArenaUILayer.h"
#include "manager/OverPanelManage.h"
#include "manager/PopEventName.h"

USING_NS_CC;

ArenaUILayer::ArenaUILayer()
{
	this->setIsTouchEnabled(true);

	setLastItemGID(NONEINT);
}

ArenaUILayer::~ArenaUILayer()
{}

//CC_PROPERTY(int32, _lastItemGID, LastItemGID)
int32 ArenaUILayer::getLastItemGID()
{
	return _lastItemGID;
}

void ArenaUILayer::setLastItemGID(int32 var)
{
	_lastItemGID = var;
}

//begin

void ArenaUILayer::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, -1, true);
}

bool ArenaUILayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	return false;
}

void ArenaUILayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{	

}

void ArenaUILayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{

} 
