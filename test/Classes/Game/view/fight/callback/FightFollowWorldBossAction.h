#ifndef _FIGHT_FOLLOW_WORLDBOSSACTION_H_
#define _FIGHT_FOLLOW_WORLDBOSSACTION_H_
#include "../interfaces/BaseAction.h"

USING_NS_CC;

class FightFollowWorldBossAction : public BaseAction
{
public:
	FightFollowWorldBossAction();
	virtual ~FightFollowWorldBossAction(){}

	virtual void doAction();
	virtual void delAction(IAction* action);

public:
};

#endif