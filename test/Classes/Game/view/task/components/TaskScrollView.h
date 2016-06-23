#ifndef _TASK_SCROLLVIEW_H_
#define _TASK_SCROLLVIEW_H_

#include "cocos2d.h"
#include "CCUIPartialScrollView.h"
#include "BaseType.h"

USING_NS_CC;

class TaskScrollView : public CCUIPartialScrollView
{
public:
	TaskScrollView(CCRect rect);
	~TaskScrollView();
	static TaskScrollView *scrollViewWithRect(CCRect rect);
	virtual void moveToPageImmediately(int page);

	virtual void moveToNextPage();
	virtual void moveToPreviousPage();

public:
	enum
	{
		stat_0,
		stat_1,
		stat_2,
	};
	CC_SYNTHESIZE(int , _state , State);

	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	CCPoint _beginPos;
	CCPoint _movePos;
};
#endif