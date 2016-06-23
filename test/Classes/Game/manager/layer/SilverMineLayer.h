#pragma once

#include "BaseType.h"
#include "FocusNode.h"
USING_NS_CC;
class SilverMineLayer:public LayerNode
{
public:
	SilverMineLayer();
	~SilverMineLayer();
public:
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
public:
	CCPoint preTouchPoint;
	CCPoint currentTouchPoint;

	CC_PROPERTY(int32, _lastItemGID, LastItemGID)
};