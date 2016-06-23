#pragma once

#include "view/fight/interfaces/BaseAction.h"

class ShowAttrChangeAction:public BaseAction
{
public:
	ShowAttrChangeAction(std::string content , ccColor3B color = ccc3(12,233,25), float delay = 1.0f);
	virtual ~ShowAttrChangeAction(){};

	virtual void doAction();
	
	virtual	void addAction(IAction* action){};
		
	virtual	void delAction(IAction* action);


private:
	std::string _content;
	ccColor3B _color;
	float _delay;
};