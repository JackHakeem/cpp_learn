#pragma once

#include "view/fight/interfaces/BaseAction.h"

class ShowNewHandHelpAction:public BaseAction
{
public:
	ShowNewHandHelpAction(int level);
	virtual ~ShowNewHandHelpAction(){};

	virtual void doAction();
	
	virtual	void addAction(IAction* action){};
		
	virtual	void delAction(IAction* action);


public:
	int _level;
};