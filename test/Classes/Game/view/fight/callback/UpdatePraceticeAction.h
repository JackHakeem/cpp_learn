#pragma once

#include "BaseType.h"
#include "view/fight/interfaces/BaseAction.h"
#include "utils/flash/CCIEventDispatcher.h"
#include "socket/command/s18/SCMD18E.h"

class RoleManage;
class RoleUI;
class GameDispatcher;
class UpdatePraceticeAction:public BaseAction, public CCIEventDispatcher
{
public:
	UpdatePraceticeAction();
	~UpdatePraceticeAction();

	bool init(char* param,RoleUI* roleUI);

	virtual void doAction();
	
	virtual	void addAction(IAction* action){};
		
	virtual	void delAction(IAction* action){};


public:
	GameDispatcher* _dispatcher;
//	SCMDInfo _param;
	RoleUI* _roleUI;
	RoleManage* _roleManage;

	int32 a_newvalue;
	int32 b_diffvalue;
	uint8 c_isShow;
};