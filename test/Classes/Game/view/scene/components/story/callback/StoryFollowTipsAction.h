#ifndef _STORY_FOLLOW_TIPS_H_
#define _STORY_FOLLOW_TIPS_H_
#include "view/fight/interfaces/BaseAction.h"

using namespace cocos2d;

class IAction;
class StepVo;

class StoryFollowTipsAction : public BaseAction
{
public:
	StoryFollowTipsAction(StepVo *pStep);
	virtual ~StoryFollowTipsAction(){}

	virtual void doAction();
	virtual void delAction(IAction* action);

public:
	StepVo * _pStep;
};

#endif