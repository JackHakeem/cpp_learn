#pragma once

#include "BaseType.h"

class IAction: public CCObject
{
public:
	IAction(){};
	virtual ~IAction(){};

	virtual void doAction(){};
	
	virtual	void addAction(IAction* action){};
		
	virtual	void delAction(IAction* action){};
};