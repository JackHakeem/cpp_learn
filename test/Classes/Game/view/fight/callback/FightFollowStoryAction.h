#ifndef _FIGHT_FOLLOW_STORYACTION_H_
#define _FIGHT_FOLLOW_STORYACTION_H_
#include "../interfaces/BaseAction.h"

USING_NS_CC;

class FightFollowStoryAction : public BaseAction
{
public:
	FightFollowStoryAction(int storyID);
	virtual ~FightFollowStoryAction(){}

	virtual void doAction();
	virtual void delAction(IAction* action);

public:
	int _nStoryID;
};

#endif