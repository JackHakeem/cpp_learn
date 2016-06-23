#pragma once

#include "view/fight/interfaces/BaseAction.h"
#include "model/newhand/vo/StepVo.h"

class fightCallBackTipsAction:public BaseAction
{
public:
	fightCallBackTipsAction(StepVo *pStep);
	virtual ~fightCallBackTipsAction(){	};

	virtual void doAction();
	
	virtual	void addAction(IAction* action){};
		
	virtual	void delAction(IAction* action);


public:
	StepVo _pStep;
};