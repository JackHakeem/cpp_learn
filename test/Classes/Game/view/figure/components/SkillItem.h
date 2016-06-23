#ifndef HLQS_SkillItem_H_
#define HLQS_SkillItem_H_
#include "LayerNode.h"
#include "model/skill/vo/UpGradeInfo.h"
#include "utils/TipBase.h"

USING_NS_CC;

class TipHelps;
class SkillItem: public LayerNode, public TipBase
{
public:
	SkillItem();
	SkillItem(int sitNum, UpGradeInfo* info, int style=2);
	~SkillItem();
	bool init();
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	//	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	//	virtual bool ccTouchEnded(CCTouch* touch, CCEvent* event);
	void updateInfo(UpGradeInfo* info);
	void clear();
	void handleEquip(CCObject* pSender);
public:
	int _mySitNum;
	TipHelps* myTip;
	int32 _posIndex;
	enum
	{
		RENDERZ_skill = 0,
	};
};
#endif