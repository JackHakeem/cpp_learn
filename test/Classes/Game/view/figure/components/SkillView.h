#ifndef HLQS_SkillView_H_
#define HLQS_SkillView_H_
#include "PopContainer.h"
#include "FocusNode.h"

USING_NS_CC;

#define MAX_SKILL_NUM (128)

class SkillLayer;

class SkillView:public PopContainer
{
public:
	SkillView();
	bool init();
	void moveBy(CCPoint pos);
	void addSkillCellAndItem();
	void showSkillTips(int nCurTouchSkill);
	void showSkillSelectPanel(int stateSkill);

	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);


public:
	enum
	{
		RENDERZ_SkillContainer = 0,
	};

	CCSize m_viewSize;
	LayerNode * _skillLayer;
	LayerNode * _tipLayer;
	SkillLayer * _skillPopLayer;
	int _nCurTouchSkill;
	CCLabelTTF * _nameText;
	CCLabelTTF * _nameTextEx;
	CCLabelTTF * _desText;
	CCLabelTTF * _desTextEx;
	int _stateSkill;
	int SkillID[MAX_SKILL_NUM];
	int _nLen;
};

#endif