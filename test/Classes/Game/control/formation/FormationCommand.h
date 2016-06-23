#ifndef _FORMATIONCOMMAND_H_
#define _FORMATIONCOMMAND_H_
#include "mvc/SimpleCommand.h"

class FormationCommand : public SimpleCommand
{
public:

	enum 
	{
		FORMATION_ACTIVATE,
		MEMBER_CHANGE,
		INIT_FORMATION,
		INIT_TEAM_MEMBERS,
		UPDATE_TEAM_MEMBER,
		CHANGE_TEAM_MEMBER_SIT,
		DISMISS_FIGURE
	};


public:
	FormationCommand();
	~FormationCommand();
	virtual void execute(int32 command, char* data);
	void initFormationDic(char* data);
	void memChange(char* data);
	void formationActivate(char* data);
};



#endif