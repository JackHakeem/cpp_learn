#ifndef _UPSKILLCREATE_H_
#define _UPSKILLCREATE_H_

#include "CCUIPartialScrollView.h"
#include "CCPlatformMacros.h"

USING_NS_CC;

class UPSkillCreate : public CCUIPartialScrollView 
{
public:
	UPSkillCreate();
	UPSkillCreate(const CCRect& mRect);
	static UPSkillCreate * UPSkillScrollViewWithCCRect(const CCRect& mRect);

	void setHightLight(bool bVar);

public:
	int _curLightIndex;
	CCPoint _curLightPos;
	CCSprite * spriteLight;

	enum TOUCHSTATE
	{
		STATE_TOUCH_0 = 0,
		STATE_TOUCH_1,
		STATE_TOUCH_2,
		STATE_TOUCH_3
	};
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	CC_SYNTHESIZE(TOUCHSTATE,_touchState,TouchStat);

	CCPoint mTouchBeganPoint;
};

extern UPSkillCreate * g_pPassiveSkillScrollView;
extern UPSkillCreate * g_pFormationScrollView;
extern UPSkillCreate * g_pTalentScrollView;

#endif
