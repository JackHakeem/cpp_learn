#pragma once

#include "IAction.h"

class BaseAction: public IAction
{
public:
	BaseAction(){};
	virtual ~BaseAction(){};

	virtual void doAction(){};
	
	virtual	void addAction(IAction* action){};
		
	virtual	void delAction(IAction* action){};
};