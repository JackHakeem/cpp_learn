#pragma once
#include "CCUIPartialScrollView.h"

class MailScrollView : public CCUIPartialScrollView
{
public:
	virtual ~MailScrollView();

	MailScrollView(const CCRect & ccRect);

	static MailScrollView * scrollViewWithCCRect(const CCRect & ccRect);

	CCNode* getTouchItemAndIndexByPos( CCPoint point, int* posIndex );

public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

public:
	enum
	{
		touch_state_0,
		touch_state_1,
		touch_state_2,
		touch_state_3,
		touch_state_4,
		touch_state_5,
	};

	CC_SYNTHESIZE(int,_touchState,TouchState);
	CC_SYNTHESIZE(int,_curScreen,CurScreen);

protected:
private:
	CCPoint mTouchBeganPoint;
};
