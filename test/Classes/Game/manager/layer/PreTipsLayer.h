#ifndef _PreTipsLayer_H_
#define _PreTipsLayer_H_

#include "BaseType.h"
#include "FocusNode.h"
USING_NS_CC;
class PreTipsLayer:public LayerNode
{
public:
	enum
	{
		PreTipsLayerZ_eggWashConfirm = 100,
		PreTipsLayerZ_ce,

	};
	enum
	{
		PreTipsLayerTAG_eggWashConfirm,
		PreTipsLayerTAG_ce,

	};

	PreTipsLayer();
	~PreTipsLayer();
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