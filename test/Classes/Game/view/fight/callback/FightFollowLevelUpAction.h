#ifndef _FIGHT_FOLLOW_LEVELUP_H_
#define _FIGHT_FOLLOW_LEVELUP_H_
#include "../interfaces/BaseAction.h"

USING_NS_CC;

class FightFollowLevelUpAction : public BaseAction
{
public:
	FightFollowLevelUpAction();
	virtual ~FightFollowLevelUpAction(){}

	virtual void doAction();
	virtual void delAction(IAction* action);

public:
};

#endif