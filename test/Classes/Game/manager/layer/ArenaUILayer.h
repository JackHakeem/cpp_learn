#ifndef _ARENAUILAYER_H_
#define _ARENAUILAYER_H_

#include "BaseType.h"
#include "FocusNode.h"
USING_NS_CC;
class ArenaUILayer:public LayerNode
{
public:
	ArenaUILayer();
	~ArenaUILayer();
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

#endif