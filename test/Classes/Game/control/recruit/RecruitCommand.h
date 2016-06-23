#ifndef _RecruitCommand_H_
#define _RecruitCommand_H_

#include "mvc/SimpleCommand.h"
#include "model/recruit/RecruitProxy.h"
#include "model/skill/SkillProxy.h"
#include "model/player/RoleManage.h"

class RecruitCommand:public SimpleCommand
{
public:
	enum 
	{
		INIT_ROOKIE_LIST,
		INIT_DISMISS_LIST,
		RECRUIT_MERC,
		DISMISS_MERC,
	};

public:
	RecruitCommand();
	~RecruitCommand();
	virtual void execute(int32 command, char* data);
	void initRookieList( char* obj );
	void initDismissList( char* obj );
	void recruitMerc( char* obj );
	void dismissMerc( char* obj );

	int _skillChangedMercId;
private:
	RecruitProxy* _recruitProxy;
	SkillProxy* _skillProxy;
	RoleManage* _roleManage;
};

#endif