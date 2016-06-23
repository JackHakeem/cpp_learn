#pragma once

#include "BaseType.h"
#include "view/fight/interfaces/BaseAction.h"
#include "utils/flash/CCIEventDispatcher.h"

class ArenaUI;
class GameDispatcher;
class ArenaCallbackAction:public BaseAction, public CCIEventDispatcher
{
public:
	ArenaCallbackAction();
	~ArenaCallbackAction();

	bool init(ArenaUI* arenaUI);

	virtual void doAction();
	
	virtual	void addAction(IAction* action){};
		
	virtual	void delAction(IAction* action){};


public:
	GameDispatcher* _dispatcher;

	ArenaUI* _arenaUI;
};