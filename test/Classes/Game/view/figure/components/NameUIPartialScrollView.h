#ifndef _NAMEUIPARTIALSCROLLVIEW_H_
#define _NAMEUIPARTIALSCROLLVIEW_H_

#include "CCUIPartialScrollView.h"

USING_NS_CC;

class NameUIPartialScrollView : public CCUIPartialScrollView
{
public:
	virtual ~NameUIPartialScrollView();
	CCLayer* addLayerByTag(int tag);
	void moveToCenter(CCPoint pos);
	void moveToBoundary(CCPoint pos);
	void moveToPos(CCPoint pos);
public:

	CCPoint _preTouchPos;
	CCPoint _curTouchPos;
	int _nState;
	int _merchNum;
	CCRect rect;
	CCSize visibleSize;

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	NameUIPartialScrollView(const CCRect & ccRect);
	static NameUIPartialScrollView * nameScrollViewWithCCRect(const CCRect & ccRect);
};

extern NameUIPartialScrollView * g_pNameScrollView;

#endif