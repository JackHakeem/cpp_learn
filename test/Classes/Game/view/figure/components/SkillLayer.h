#ifndef HLQS_SkillLayer_H_
#define HLQS_SkillLayer_H_
#include "LayerNode.h"
#include "utils/ScaleUtil.h"

#define CCSIZE_SKILL_SCROLLVIEW CCSizeMake(POSX(380),POSX(390))

USING_NS_CC;

class SkillView;

class SkillLayer : public LayerNode
{
public:
	SkillLayer();
	~SkillLayer();

	CCSize _sz;
	SkillView * _skillView;
	enum
	{
		TAG_DIR_LEFT = 301,
		TAG_DIR_RIGHT = 302,
		TAG_DIR_TXT = 303,
		TAG_HIGH_LIGHT = 500,
	};

public:
	virtual bool init();
	void addHighLight();
	void addSkillScrollView();
	void loadSkillItems();
	void loadDirections();
	void updateDirections();

	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);


    CCPoint preTouchPoint;
    CCPoint currentTouchPoint;
};

#endif
