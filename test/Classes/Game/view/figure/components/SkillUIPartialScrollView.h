#ifndef _SKILLUIPARTIALSCROLLVIEW_H_
#define _SKILLUIPARTIALSCROLLVIEW_H_

#include "CCUIPartialScrollView.h"

USING_NS_CC;

#define SKILL_ROW (3)
#define SKILL_COL (3)

class SkillUIPartialScrollView : public CCUIPartialScrollView
{
public:
	virtual ~SkillUIPartialScrollView();
public:

	//	CCPoint _SkillPOS[SKILL_ROW*SKILL_COL];
	int _curTouchPos;
	int _nState;

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	CCNode* getTouchPosIndex( CCPoint point, int* posIndex );
	SkillUIPartialScrollView(const CCRect & ccRect);
	static SkillUIPartialScrollView * skillScrollViewWithCCRect(const CCRect & ccRect);
};

extern SkillUIPartialScrollView * g_pSkillScrollView;

#endif