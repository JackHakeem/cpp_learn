#include "PreTipsLayer.h"
#include "manager/TouchLayerEnum.h"
//#include "NewEAlert.h"

USING_NS_CC;



PreTipsLayer::PreTipsLayer()
{
	//使可被触控
	this->setIsTouchEnabled(true);

	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::PreTipsLayer, true);
	setLastItemGID(NONEINT);
}

PreTipsLayer::~PreTipsLayer()
{}

//CC_PROPERTY(int32, _lastItemGID, LastItemGID)
int32 PreTipsLayer::getLastItemGID()
{
	return _lastItemGID;
}

void PreTipsLayer::setLastItemGID(int32 var)
{
	_lastItemGID = var;
}

//begin

void PreTipsLayer::registerWithTouchDispatcher()
{
	this->setIsTouchEnabled (true);
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::PreTipsLayer, true);
}

bool PreTipsLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	//CCLog("TLE::PreTipsLayer");
	//
	//setTouchState(TouchState_0);
	//
	bool rnt = false;

	CCPoint locationInView = touch->locationInView(touch->view());
    preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
	//
	//{
	//	CCNode* p_tec = (CCNode*)this->getChildByTag(PreTipsLayerTAG_eqdrop);
	//	if (p_tec)
	//	{
	//		CCRect contentLayerRect = CCRectZero;
	//		contentLayerRect.origin = p_tec->getPosition();
	//		contentLayerRect.size = p_tec->getContentSize();

	//		if (CCRect::CCRectContainsPoint(contentLayerRect, preTouchPoint))
	//		{
	//			rnt = true;
	//		}
	//		else
	//		{//删除道具TIPS显示
	//			this->removeChildByTag(PreTipsLayer::PreTipsLayerTAG_eqdrop, true);
	//		}
	//	}
	//}
	{
		CCNode* p_tec = (CCNode*)this->getChildByTag(PreTipsLayerTAG_eggWashConfirm);
		if (p_tec)
		{
			rnt = true;
		}
	}
	

	return rnt;
}

void PreTipsLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{	

}

void PreTipsLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{

} 
