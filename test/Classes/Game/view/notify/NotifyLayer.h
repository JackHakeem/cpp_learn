#pragma once
#include "../../../UIComponent/LayerNode.h"
#include "CCLayer.h"
class ViewManager;

class NotifyLayer : public CCLayerColor
{
public:
	
public:
	NotifyLayer();
	virtual ~NotifyLayer();
	virtual bool init();

	void loadItem();

	void resetNotices();

	int getTypeByTouchPos(CCPoint pos);

	void doFollowEvent(int type);

public:
	CCSize _winSize;
	ViewManager * pViewMgrInstance;
public:

public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void removeLayer( int type );
public:
	
};