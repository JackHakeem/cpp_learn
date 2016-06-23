#pragma once

#include "view/fight/interfaces/BaseAction.h"

class ShowNotificationAction:public BaseAction
{
public:
	ShowNotificationAction(int type);
	virtual ~ShowNotificationAction(){};

	virtual void doAction();
	
	virtual	void addAction(IAction* action){};
		
	virtual	void delAction(IAction* action);


public:
	int _type;
};