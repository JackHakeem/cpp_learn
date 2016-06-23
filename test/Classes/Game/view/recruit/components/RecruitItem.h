#ifndef __RecruitItem_H_
#define __RecruitItem_H_

#include "cocos2d.h"
#include "model/recruit/vo/RecruitInfo.h"
using namespace cocos2d;

class RecruitItem : public CCLayer
{
public:
	RecruitItem( const CCRect& rect);
	~RecruitItem();

	enum TOUCHSTATE
	{
		STATE_TOUCH_0 = 0,
		STATE_TOUCH_1,
		STATE_TOUCH_2,
		STATE_TOUCH_3
	};

	CC_SYNTHESIZE(TOUCHSTATE,_touchState,TouchStat);

public:
	static RecruitItem* RecruitItemWithRect( const CCRect& rect );
	void initRecruitInfo( RecruitInfo recruitInfo, int id );
	CCRect rect();

	//virtual void onEnter();
	virtual void onExit();
	bool containsTouchLocation(CCTouch* touch);
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

// 	virtual void touchDelegateRetain();
// 	virtual void touchDelegateRelease();
	int id();
	RecruitInfo* info();
	static ccColor3B setTextColor( uint id );
	CCRect m_rect;
	int m_ItemIndex;

	CCLabelTTF* _name;
	CCLabelTTF* _level;
	CCSprite* _pic;

	RecruitInfo _info;

	CCPoint mTouchBeganPoint;
};

#endif
